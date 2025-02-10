/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Gauge Low Fuel Warning (MET-M_FUEL-CSTD-3-XX-X-C1)                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_LOWFUEL_C_MAJOR                   (1)
#define GAGDST_LOWFUEL_C_MINOR                   (1)
#define GAGDST_LOWFUEL_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gagdst_lowfuel_cfg_private.h"

#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GAGDST_LOWFUEL_C_MAJOR != GAGDST_LOWFUEL_H_MAJOR) || \
     (GAGDST_LOWFUEL_C_MINOR != GAGDST_LOWFUEL_H_MINOR) || \
     (GAGDST_LOWFUEL_C_PATCH != GAGDST_LOWFUEL_H_PATCH))
#error "gagdst_lowfuel.c and gagdst_lowfuel.h : source and header files are inconsistent!"
#endif

#if ((GAGDST_LOWFUEL_C_MAJOR != GAGDST_LOWFUEL_CFG_H_MAJOR) || \
     (GAGDST_LOWFUEL_C_MINOR != GAGDST_LOWFUEL_CFG_H_MINOR) || \
     (GAGDST_LOWFUEL_C_PATCH != GAGDST_LOWFUEL_CFG_H_PATCH))
#error "gagdst_lowfuel.c and gagdst_lowfuel_cfg_private.h.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_LOWFUEL_SEG_ME                    (0U)                           /* Segment of the Meter Empty judgment               */
#define GAGDST_LOWFUEL_SEG_LFW                   (1U)                           /* Segment of the LFW judgment                       */

#define GAGDST_LOWFUEL_STSBIT_LFW                (0x01U)                        /* Status bit:Request of Fuel Low Warning            */
#define GAGDST_LOWFUEL_STSBIT_BLK                (0x02U)                        /* Status bit:Request of Blinking                    */
#define GAGDST_LOWFUEL_STSBIT_BL2                (0x04U)                        /* Status bit:Request of Blinking 2                  */
#define GAGDST_LOWFUEL_STSBIT_MSK                (0x07U)                        /* Status bit:Mask                                   */

#define GAGDST_LOWFUEL_NUM_ACT                   (8U)                           /* Number of Low Fuel Warning actions                */

#define GAGDST_LOWFUEL_INCREMENT_VALUE           (1U)                           /* Increment value                                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                     u1_s_gagdst_lowfuel_lfw;                          /* Low Fuel Warning condition                        */
static U1                     u1_s_gagdst_lowfuel_stsbit;                       /* Low Fuel Warning control state bit                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1     u1_s_GagdstLowFuelCal(const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG, const U2 u2_a_TRGT);
static U1     u1_s_GagdstLowFuelAbn(const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG, const U2 u2_a_SRC_CHK);
static void   vd_s_GagdstLowFuelTh(ST_GAGDST_LOWFUEL_CFG * stp_a_lowfuel_cfg);

/*===================================================================================================================================*/
/*  void    vd_g_GagdstLowFuelBonInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstLowFuelBonInit(void)
{
    u1_s_gagdst_lowfuel_lfw    = (U1)FALSE;
    u1_s_gagdst_lowfuel_stsbit = (U1)0x00U;

    vd_g_GagdstLowFuelCfgBonInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstLowRstwkFuelInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstLowFuelRstwkInit(void)
{
    u1_s_gagdst_lowfuel_lfw    = (U1)FALSE;
    u1_s_gagdst_lowfuel_stsbit = (U1)0x00U;

    vd_g_GagdstLowFuelCfgRstwkInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstLowFuelOpemdEvhk(const U4 u4_a_EVTBIT)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U4 u4_a_EVTBIT                                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstLowFuelOpemdEvhk(const U4 u4_a_EVTBIT)
{
    U4                             u4_t_ign_chk;                                /* Ignition check                                    */
#if 0   /* BEV BSW provisionally */
    u4_t_ign_chk = u4_a_EVTBIT & ((U4)VEH_OPEMD_EVTBIT_IGN_TO_ON  |
                                  (U4)VEH_OPEMD_EVTBIT_IGN_TO_OFF);
#else
    u4_t_ign_chk = u4_a_EVTBIT & ((U4)0x00002020U);
#endif
    if(u4_t_ign_chk != (U4)0U){
        u1_s_gagdst_lowfuel_lfw    = (U1)FALSE;
        u1_s_gagdst_lowfuel_stsbit = (U1)0x00U;
    }

    vd_g_GagdstLowFuelCfgOpemdEvhk(u4_a_EVTBIT);
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstLowFuelUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U2 u2_a_SRC_CHK                                                                                            */
/*                  const U2 u2_a_TRGT                                                                                               */
/*                  const U2 u2_a_OW                                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstLowFuelUpdt(const U2 u2_a_SRC_CHK, const U2 u2_a_TRGT, const U2 u2_a_OW, const U1 u1_a_ESI)
{
    U2                             u2_t_src_act;                                /* Active State                                      */
    U2                             u2_t_src_ign;                                /* Ignition is On                                    */
    U1                             u1_t_stsbit;                                 /* Status bit                                        */
    ST_GAGDST_LOWFUEL_CFG          st_t_cfg;                                    /* Low Fuel Waning information                       */

    u1_t_stsbit             = (U1)0x00U;
    st_t_cfg.u1_wrnlamp     = st_g_GAGDST_LOWFUEL_INIT.u1_wrnlamp;
    st_t_cfg.u2_lit_wrnoff  = st_g_GAGDST_LOWFUEL_INIT.u2_lit_wrnoff;
    st_t_cfg.u2_lit_wrnon   = st_g_GAGDST_LOWFUEL_INIT.u2_lit_wrnon;

    u2_t_src_ign = u2_a_SRC_CHK & u2_g_GAGDST_LOWFUEL_SRC_IGN;
    if(u2_t_src_ign != (U2)0U){
        vd_s_GagdstLowFuelTh(&st_t_cfg);
        u2_t_src_act = u2_a_SRC_CHK & (u2_g_GAGDST_LOWFUEL_SRC_UNK  |
                                       u2_g_GAGDST_LOWFUEL_SRC_AVG_I);
        if(u2_t_src_act == u2_g_GAGDST_LOWFUEL_SRC_AVG_I){
            u1_t_stsbit |= u1_s_GagdstLowFuelCal(&st_t_cfg, u2_a_TRGT);
        }
        else{
            u1_s_gagdst_lowfuel_lfw = (U1)FALSE;
        }
        u1_t_stsbit |= u1_s_GagdstLowFuelAbn(&st_t_cfg, u2_a_SRC_CHK);
    }
    else{
        u1_s_gagdst_lowfuel_lfw = (U1)FALSE;
    }

    u1_s_gagdst_lowfuel_stsbit = u1_t_stsbit;

    vd_g_GagdstLowFuelCfgMainFinish(u2_a_SRC_CHK);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_GagdstLowFuelCal(const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG, const U2 u2_a_TRGT)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG                                                                    */
/*                  const U2                            u2_a_TRGT                                                                    */
/*  Return:         U1                                  u1_t_stsbit                                                                  */
/*===================================================================================================================================*/
static U1      u1_s_GagdstLowFuelCal(const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG, const U2 u2_a_TRGT)
{
    U1                             u1_t_seg;                                    /* Segment Display Value                             */
    U1                             u1_t_stsbit;                                 /* Status bit                                        */

    u1_t_stsbit = (U1)0x00U;
    if(stp_a_CFG->u1_wrnlamp == (U1)GAGDST_LOWFUEL_WRNLAMP_SEG){
        u1_t_seg = u1_g_GagdstLowFuelCfgSeg();
        if(u1_t_seg != (U1)GAGDST_LOWFUEL_FUELSEG_UNK){
            if((u2_a_TRGT <= stp_a_CFG->u2_lit_wrnon   ) &&
               (u1_t_seg  <= (U1)GAGDST_LOWFUEL_SEG_LFW)){
                u1_s_gagdst_lowfuel_lfw = (U1)TRUE;
            }
            if((u2_a_TRGT >= stp_a_CFG->u2_lit_wrnoff  ) &&
               (u1_t_seg  >= (U1)GAGDST_LOWFUEL_SEG_LFW)){
                u1_s_gagdst_lowfuel_lfw = (U1)FALSE;
            }

            u1_t_stsbit |= (U1)GAGDST_LOWFUEL_STSBIT_BLK;
            if(u1_t_seg == (U1)GAGDST_LOWFUEL_SEG_ME){
                u1_t_stsbit |= (U1)GAGDST_LOWFUEL_STSBIT_BL2;
            }
        }
        else{
            u1_s_gagdst_lowfuel_lfw = (U1)FALSE;
        }
    }
    else{
        if(u2_a_TRGT <= stp_a_CFG->u2_lit_wrnon){
            u1_s_gagdst_lowfuel_lfw = (U1)TRUE;
        }
        else{
            u1_s_gagdst_lowfuel_lfw = (U1)FALSE;
        }
    }
    if(u1_s_gagdst_lowfuel_lfw == (U1)TRUE){
        u1_t_stsbit |= (U1)GAGDST_LOWFUEL_STSBIT_LFW;
    }
    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_GagdstLowFuelAbn(const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG, const U2 u2_a_SRC_CHK)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG                                                                    */
/*                  const U2                            u2_a_SRC_CHK                                                                 */
/*  Return:         U1                                  u1_t_stsbit                                                                  */
/*===================================================================================================================================*/
static U1      u1_s_GagdstLowFuelAbn(const ST_GAGDST_LOWFUEL_CFG * const stp_a_CFG, const U2 u2_a_SRC_CHK)
{
    U1                             u1_t_stsbit;                                 /* Status bit                                        */
    U1                             u1_t_pt_cal;                                 /* Determination state of the indicated correction constant */
    U2                             u2_t_src_os;                                 /* Open/Short is On                                  */

    u1_t_pt_cal = u1_g_GagdstLowFuelCfgPtCal();
    u2_t_src_os = u2_a_SRC_CHK & u2_g_GAGDST_LOWFUEL_SRC_OS;
    if(u1_t_pt_cal != (U1)TRUE){
        u1_s_gagdst_lowfuel_lfw = (U1)FALSE;
        u1_t_stsbit             = (U1)GAGDST_LOWFUEL_STSBIT_LFW;
    }
    else if(u2_t_src_os != (U2)0U){
        u1_t_stsbit             = (U1)GAGDST_LOWFUEL_STSBIT_LFW;
    }
    else{
        u1_t_stsbit             = (U1)0x00U;
    }
    if((u1_t_stsbit           == (U1)GAGDST_LOWFUEL_STSBIT_LFW ) &&
       (stp_a_CFG->u1_wrnlamp == (U1)GAGDST_LOWFUEL_WRNLAMP_SEG)){
        u1_t_stsbit |= ((U1)GAGDST_LOWFUEL_STSBIT_BLK | 
                        (U1)GAGDST_LOWFUEL_STSBIT_BL2);
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_GagdstLowFuel(const U1 u1_a_OUT)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_OUT                                                                                                */
/*  Return:         U1       u1_t_lfw_act                                                                                            */
/*===================================================================================================================================*/
U1      u1_g_GagdstLowFuel(const U1 u1_a_OUT)
{
    static const U1 u1_tp_GAGDST_LOWFUEL_ACT[GAGDST_LOWFUEL_NUM_ACT] = {        /* Low Fuel Warning Action Table                     */
                                                                                /* bit2:BL2, bit1:BLK, bit0:LFW                      */
        (U1)GAGDST_LOWFUEL_OFF,                                                 /*    0         0         0                          */
        (U1)GAGDST_LOWFUEL_ON ,                                                 /*    0         0         1                          */
        (U1)GAGDST_LOWFUEL_OFF,                                                 /*    0         1         0                          */
        (U1)GAGDST_LOWFUEL_BLINK1,                                              /*    0         1         1                          */
        (U1)GAGDST_LOWFUEL_OFF,                                                 /*    1         0         0                          */
        (U1)GAGDST_LOWFUEL_ON ,                                                 /*    1         0         1                          */
        (U1)GAGDST_LOWFUEL_OFF,                                                 /*    1         1         0                          */
        (U1)GAGDST_LOWFUEL_BLINK2                                               /*    1         1         1                          */
    };

    U1                             u1_t_lfw_act;                                /* Low Fuel Warning Active                           */
    U1                             u1_t_stsbit;                                 /* Status bit                                        */

    if(u1_a_OUT == (U1)TRUE){
        u1_t_stsbit  = u1_s_gagdst_lowfuel_stsbit & (U1)GAGDST_LOWFUEL_STSBIT_MSK;
        u1_t_lfw_act = u1_tp_GAGDST_LOWFUEL_ACT[u1_t_stsbit];
    }
    else{
        u1_t_lfw_act = u1_s_gagdst_lowfuel_lfw;
    }

    return(u1_t_lfw_act);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GagdstLowFuelTh(ST_GAGDST_LOWFUEL_CFG * stp_a_lowfuel_cfg)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     ST_GAGDST_LOWFUEL_CFG * stp_a_lowfuel_cfg                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GagdstLowFuelTh(ST_GAGDST_LOWFUEL_CFG * stp_a_lowfuel_cfg)
{
    U2                             u2_t_lit_wrnon;

    u2_t_lit_wrnon = u2_g_GagdstLowFuelLitWng();
    stp_a_lowfuel_cfg->u1_wrnlamp   = (U1)GAGDST_LOWFUEL_WRNLAMP_LMP;
    stp_a_lowfuel_cfg->u2_lit_wrnon = u2_t_lit_wrnon;

    if(u2_t_lit_wrnon <= ((U2)U2_MAX - (U2)GAGDST_LOWFUEL_INCREMENT_VALUE)){
        stp_a_lowfuel_cfg->u2_lit_wrnoff = u2_t_lit_wrnon + (U2)GAGDST_LOWFUEL_INCREMENT_VALUE;
    }
    else{
        stp_a_lowfuel_cfg->u2_lit_wrnoff = (U2)U2_MAX;
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
/*  1.0.0    03/30/2020  AM       New.                                                                                               */
/*  1.0.1    07/09/2020  AM       Add Comment.                                                                                       */
/*                                Function Header Comment Change.                                                                    */
/*  1.1.0    08/10/2020  AM       Changes to the initialization process and the addition of interfaces to add functionality.         */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  09/21/2023  SN       Add vd_s_GagdstLowFuelTh                                                                           */
/* 19PFv3-2  02/29/2024  SH       Change to get WNG lit from Fuelvol                                                                 */
/* 19PFv3-3  04/16/2024  SM       Delete Low Fuel Waning input bit for "volume estimated is unknown"                                 */
/*                                                                                                                                   */
/*  * AM   = Atsushi Mizutani, DENSO TECHNO                                                                                          */
/*  * SN   = Shimon Nambu, DENSO TECHNO                                                                                              */
/*  * SH   = Sae Hirose, DENSO TECHNO                                                                                                */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
