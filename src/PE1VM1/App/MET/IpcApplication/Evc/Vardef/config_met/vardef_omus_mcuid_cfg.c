/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Variation Defines / Organized Master Unified System Vehicle Information                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_OMUS_MCUID_CFG_C_MAJOR                 (1)
#define VARDEF_OMUS_MCUID_CFG_C_MINOR                 (0)
#define VARDEF_OMUS_MCUID_CFG_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_omus_cfg_private.h"
#include "vardef_omus_channel.h"
#include "rim_ctl.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_OMUS_MCUID_CFG_C_MAJOR != VARDEF_OMUS_CFG_H_MAJOR) || \
     (VARDEF_OMUS_MCUID_CFG_C_MINOR != VARDEF_OMUS_CFG_H_MINOR) || \
     (VARDEF_OMUS_MCUID_CFG_C_PATCH != VARDEF_OMUS_CFG_H_PATCH))
#error "vardef_omus_mcuid_cfg.c and vardef_omus_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_OMUS_MCUID_CFG_C_MAJOR != VARDEF_OMUS_CHANNEL_H_MAJOR) || \
     (VARDEF_OMUS_MCUID_CFG_C_MINOR != VARDEF_OMUS_CHANNEL_H_MINOR) || \
     (VARDEF_OMUS_MCUID_CFG_C_PATCH != VARDEF_OMUS_CHANNEL_H_PATCH))
#error "vardef_omus_mcuid_cfg.c and vardef_omus_channel.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_OMUS_MCUID_CFG_C_MAJOR != VARDEF_OMUS_CAN_CFG_PRIV_H_MAJOR) || \
     (VARDEF_OMUS_MCUID_CFG_C_MINOR != VARDEF_OMUS_CAN_CFG_PRIV_H_MINOR) || \
     (VARDEF_OMUS_MCUID_CFG_C_PATCH != VARDEF_OMUS_CAN_CFG_PRIV_H_PATCH))
#error "vardef_omus_mcuid_cfg.c and vardef_omus_can_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_OMUS_MCUID0798_NUM          (CALIB_MCUID0798_NUM)
#define VDF_OMUS_MCUID0209_NUM          (CALIB_MCUID0209_NUM)
#define VDF_OMUS_MCUID0210_NUM          (CALIB_MCUID0210_NUM)
#define VDF_OMUS_MCUID0211_NUM          (CALIB_MCUID0211_NUM)
#define VDF_OMUS_MCUID0212_NUM          (CALIB_MCUID0212_NUM)
#define VDF_OMUS_MCUID0213_NUM          (CALIB_MCUID0213_NUM)
#define VDF_OMUS_MCUID0214_NUM          (CALIB_MCUID0214_NUM)
#define VDF_OMUS_MCUID0215_NUM          (CALIB_MCUID0215_NUM)
#define VDF_OMUS_MCUID0233_NUM          (CALIB_MCUID0233_NUM)
#define VDF_OMUS_MCUID0224_NUM          (CALIB_MCUID0224_NUM)
#define VDF_OMUS_MCUID0225_NUM          (CALIB_MCUID0225_NUM)
#define VDF_OMUS_MCUID0226_NUM          (CALIB_MCUID0226_NUM)
#define VDF_OMUS_MCUID0227_NUM          (CALIB_MCUID0227_NUM)
#define VDF_OMUS_MCUID0228_NUM          (CALIB_MCUID0228_NUM)
#define VDF_OMUS_MCUID0229_NUM          (CALIB_MCUID0229_NUM)
#define VDF_OMUS_MCUID0230_NUM          (CALIB_MCUID0230_NUM)
#define VDF_OMUS_MCUID0231_NUM          (CALIB_MCUID0231_NUM)
#define VDF_OMUS_MCUID0232_NUM          (CALIB_MCUID0232_NUM)
#define VDF_OMUS_MCUID0234_NUM          (CALIB_MCUID0234_NUM)
#define VDF_OMUS_MCUID1138_NUM          (CALIB_MCUID1138_NUM)
#define VDF_OMUS_MCUID0590_NUM          (CALIB_MCUID0590_NUM)
#define VDF_OMUS_MCUID0268_NUM          (CALIB_MCUID0268_NUM)
#define VDF_OMUS_MCUID0262_NUM          (CALIB_MCUID0262_NUM)
#define VDF_OMUS_MCUID0263_NUM          (CALIB_MCUID0263_NUM)
#define VDF_OMUS_MCUID0264_NUM          (CALIB_MCUID0264_NUM)
#define VDF_OMUS_MCUID0341_NUM          (CALIB_MCUID0341_NUM)
#define VDF_OMUS_MCUID1135_NUM          (CALIB_MCUID1135_NUM)
#define VDF_OMUS_MCUID1136_NUM          (CALIB_MCUID1136_NUM)
#define VDF_OMUS_MCUID0604_NUM          (CALIB_MCUID0604_NUM)
#define VDF_OMUS_MCUID0605_NUM          (CALIB_MCUID0605_NUM)
#define VDF_OMUS_MCUID0606_NUM          (CALIB_MCUID0606_NUM)
#define VDF_OMUS_MCUID0607_NUM          (CALIB_MCUID0607_NUM)
#define VDF_OMUS_MCUID0809_NUM          (CALIB_MCUID0809_NUM)
#define VDF_OMUS_MCUID0810_NUM          (CALIB_MCUID0810_NUM)
#define VDF_OMUS_MCUID3020_NUM          (CALIB_MCUID3020_NUM)
#define VDF_OMUS_MCUID0024_NUM          (2U)
#define VDF_OMUS_MCUID0025_NUM          (CALIB_MCUID0025_NUM)
#define VDF_OMUS_MCUID0235_NUM          (CALIB_MCUID0235_NUM)
#define VDF_OMUS_MCUID0250_NUM          (CALIB_MCUID0250_NUM)
#define VDF_OMUS_MCUID0251_NUM          (CALIB_MCUID0251_NUM)
#define VDF_OMUS_MCUID0252_NUM          (CALIB_MCUID0252_NUM)
#define VDF_OMUS_MCUID0253_NUM          (CALIB_MCUID0253_NUM)
#define VDF_OMUS_MCUID0254_NUM          (CALIB_MCUID0254_NUM)
#define VDF_OMUS_MCUID0255_NUM          (CALIB_MCUID0255_NUM)
#define VDF_OMUS_MCUID3025_NUM          (CALIB_MCUID3025_NUM)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1    u1_s_vdf_omus_mcuid0798;
static U1    u1_s_vdf_omus_mcuid0209;
static U1    u1_s_vdf_omus_mcuid0210;
static U1    u1_s_vdf_omus_mcuid0211;
static U1    u1_s_vdf_omus_mcuid0212;
static U1    u1_s_vdf_omus_mcuid0213;
static U1    u1_s_vdf_omus_mcuid0214;
static U1    u1_s_vdf_omus_mcuid0215;
static U1    u1_s_vdf_omus_mcuid0233;
static U1    u1_s_vdf_omus_mcuid0224;
static U1    u1_s_vdf_omus_mcuid0225;
static U1    u1_s_vdf_omus_mcuid0226;
static U1    u1_s_vdf_omus_mcuid0227;
static U1    u1_s_vdf_omus_mcuid0228;
static U1    u1_s_vdf_omus_mcuid0229;
static U1    u1_s_vdf_omus_mcuid0230;
static U1    u1_s_vdf_omus_mcuid0231;
static U1    u1_s_vdf_omus_mcuid0232;
static U1    u1_s_vdf_omus_mcuid0234;
static U1    u1_s_vdf_omus_mcuid1138;
static U1    u1_s_vdf_omus_mcuid0590;
static U1    u1_s_vdf_omus_mcuid0268;
static U2    u2_s_vdf_omus_mcuid0262;
static U2    u2_s_vdf_omus_mcuid0263;
static U1    u1_s_vdf_omus_mcuid0264;
static U1    u1_s_vdf_omus_mcuid0341;
static U1    u1_s_vdf_omus_mcuid1135;
static U1    u1_s_vdf_omus_mcuid1136;
static U1    u1_s_vdf_omus_mcuid0604;
static U1    u1_s_vdf_omus_mcuid0605;
static U1    u1_s_vdf_omus_mcuid0606;
static U1    u1_s_vdf_omus_mcuid0607;
static U1    u1_s_vdf_omus_mcuid0809;
static U1    u1_s_vdf_omus_mcuid0810;
static U1    u1_s_vdf_omus_mcuid3020;
static U1    u1_s_vdf_omus_mcuid0024;
static U1    u1_s_vdf_omus_mcuid0025;
static U1    u1_s_vdf_omus_mcuid0235;
static U1    u1_s_vdf_omus_mcuid0250;
static U1    u1_s_vdf_omus_mcuid0251;
static U1    u1_s_vdf_omus_mcuid0252;
static U1    u1_s_vdf_omus_mcuid0253;
static U1    u1_s_vdf_omus_mcuid0254;
static U1    u1_s_vdf_omus_mcuid0255;
static U1    u1_s_vdf_omus_mcuid3025;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void         vd_s_VardefOmusCfgWriteU1(const U1 u1_a_WRITEDATA, U1 * u1_ap_mcuiddata, const U2 u2_a_RIMID);
static void         vd_s_VardefOmusCfgWriteU2(const U2 u2_a_WRITEDATA, U2 * u2_ap_mcuiddata, const U2 u2_a_RIMID);
static void         vd_s_VardefOmusCfgRimReadU1(const U1 u1_a_DEF, U1 * u1_ap_mcuiddata, const U2 u2_a_RIMID);
static void         vd_s_VardefOmusCfgRimReadU2(const U2 u2_a_DEF, U2 * u2_ap_mcuiddata, const U2 u2_a_RIMID);
static inline U1    u1_s_VardefOmusCfgCalibNumChk(const U1 u1_a_MCUIDDATA, const U1 u1_a_NUM, const U1 u1_a_DEF);
static inline U1    u1_s_VardefOmusCfgCalibMinMaxChk(const U1 u1_a_MCUIDDATA, const U1 u1_a_MIN, const U1 u1_a_MAX, const U1 u1_a_DEF);
static inline U1    u1_s_VardefOmusCfgCalibMCUID0235Chk(const U1 u1_a_MCUIDDATA, const U1 u1_a_DEF);

static void         vd_s_VardefOmusCfgMCUID0798Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0209Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0210Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0211Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0212Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0213Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0214Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0215Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0233Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0224Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0225Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0226Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0227Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0228Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0229Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0230Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0231Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0232Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0234Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID1138Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0590Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0268Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0262Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0263Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0264Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0341Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID1135Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID1136Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0604Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0605Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0606Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0607Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0809Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0810Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID3020Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0024Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0025Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0235Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0250Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0251Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0252Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0253Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0254Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID0255Jdg(const U1 u1_a_CANVAL);
static void         vd_s_VardefOmusCfgMCUID3025Jdg(const U1 u1_a_CANVAL);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgWriteU1(const U1 u1_a_WRITEDATA, U1 * u1_ap_mcuiddata, const U2 u2_a_RIMID)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgWriteU1(const U1 u1_a_WRITEDATA, U1 * u1_ap_mcuiddata, const U2 u2_a_RIMID)
{
    (*u1_ap_mcuiddata) = u1_a_WRITEDATA;
    vd_g_Rim_WriteU1(u2_a_RIMID, u1_a_WRITEDATA);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgWriteU2(const U2 u2_a_WRITEDATA, U2 * u2_ap_mcuiddata, const U2 u2_a_RIMID)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgWriteU2(const U2 u2_a_WRITEDATA, U2 * u2_ap_mcuiddata, const U2 u2_a_RIMID)
{
    (*u2_ap_mcuiddata) = u2_a_WRITEDATA;
    vd_g_Rim_WriteU2(u2_a_RIMID, u2_a_WRITEDATA);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgRimReadU1(const U1 u1_a_DEF, U1 * u1_ap_mcuiddata, const U2 u2_a_RIMID)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgRimReadU1(const U1 u1_a_DEF, U1 * u1_ap_mcuiddata, const U2 u2_a_RIMID)
{
    U1                           u1_t_rim_chk;
    U1                           u1_t_rim_rx;

    u1_t_rim_chk  = u1_g_Rim_ReadU1withStatus(u2_a_RIMID, &u1_t_rim_rx) & (U1)RIM_RESULT_KIND_MASK;
    if(u1_t_rim_chk == (U1)RIM_RESULT_KIND_OK ){
        (*u1_ap_mcuiddata) = u1_t_rim_rx;
    }
    else {
        vd_s_VardefOmusCfgWriteU1(u1_a_DEF, u1_ap_mcuiddata, u2_a_RIMID);
    }
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgRimReadU2(const U2 u2_a_DEF, U2 * u2_ap_mcuiddata, const U2 u2_a_RIMID)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgRimReadU2(const U2 u2_a_DEF, U2 * u2_ap_mcuiddata, const U2 u2_a_RIMID)
{
    U1                           u1_t_rim_chk;
    U2                           u2_t_rim_rx;

    u1_t_rim_chk  = u1_g_Rim_ReadU2withStatus(u2_a_RIMID, &u2_t_rim_rx) & (U1)RIM_RESULT_KIND_MASK;
    if(u1_t_rim_chk == (U1)RIM_RESULT_KIND_OK ){
        (*u2_ap_mcuiddata) = u2_t_rim_rx;
    }
    else {
        vd_s_VardefOmusCfgWriteU2(u2_a_DEF, u2_ap_mcuiddata, u2_a_RIMID);
    }
}

/*===================================================================================================================================*/
/*  static  inline  U1  u1_s_VardefOmusCfgCalibNumChk(const U1 u1_a_MCUIDDATA, const U1 u1_a_NUM, const U1 u1_a_DEF)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1    u1_s_VardefOmusCfgCalibNumChk(const U1 u1_a_MCUIDDATA, const U1 u1_a_NUM, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_MCUIDDATA;
    if(u1_t_ret >= u1_a_NUM){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static  inline  U1  u1_s_VardefOmusCfgCalibNumChk(const U1 u1_a_MCUIDDATA, const U1 u1_a_NUM, const U1 u1_a_DEF)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  inline  U1  u1_s_VardefOmusCfgCalibMinMaxChk(const U1 u1_a_MCUIDDATA, const U1 u1_a_MIN, const U1 u1_a_MAX, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_MCUIDDATA;
    if((u1_t_ret < u1_a_MIN) ||
       (u1_t_ret > u1_a_MAX)){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static  inline  U1  u1_s_VardefOmusCfgCalibMCUID0235Chk(const U1 u1_a_MCUIDDATA, const U1 u1_a_DEF)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  inline  U1  u1_s_VardefOmusCfgCalibMCUID0235Chk(const U1 u1_a_MCUIDDATA, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_DEF;
    if((u1_t_ret == (U1)CALIB_MCUID0235_OTHER) ||
       (u1_t_ret == (U1)CALIB_MCUID0235_PICKUP_TRUCK)){
        u1_t_ret = u1_a_MCUIDDATA;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_VardefOmusCfgMCUIDBonInt(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefOmusCfgMCUIDBonInt(void)
{
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0798_TRNLMPCLR    , &u1_s_vdf_omus_mcuid0798, (U2)RIMID_U1_VDF_MCUID0798);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0209_RRCYM        , &u1_s_vdf_omus_mcuid0209, (U2)RIMID_U1_VDF_MCUID0209);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0210_RLCYM        , &u1_s_vdf_omus_mcuid0210, (U2)RIMID_U1_VDF_MCUID0210);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0211_BCTYM        , &u1_s_vdf_omus_mcuid0211, (U2)RIMID_U1_VDF_MCUID0211);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0212_LGCYM        , &u1_s_vdf_omus_mcuid0212, (U2)RIMID_U1_VDF_MCUID0212);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0213_HDCY_BDBM    , &u1_s_vdf_omus_mcuid0213, (U2)RIMID_U1_VDF_MCUID0213);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0214_RPSDWARNM    , &u1_s_vdf_omus_mcuid0214, (U2)RIMID_U1_VDF_MCUID0214);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0215_LPSDWARNM    , &u1_s_vdf_omus_mcuid0215, (U2)RIMID_U1_VDF_MCUID0215);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0233_RDOOR        , &u1_s_vdf_omus_mcuid0233, (U2)RIMID_U1_VDF_MCUID0233);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0224_RR_SEATSW    , &u1_s_vdf_omus_mcuid0224, (U2)RIMID_U1_VDF_MCUID0224);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0225_RC_SEATSW    , &u1_s_vdf_omus_mcuid0225, (U2)RIMID_U1_VDF_MCUID0225);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0226_RL_SEATSW    , &u1_s_vdf_omus_mcuid0226, (U2)RIMID_U1_VDF_MCUID0226);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0227_RR2_SEATSW   , &u1_s_vdf_omus_mcuid0227, (U2)RIMID_U1_VDF_MCUID0227);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0228_RC2_SEATSW   , &u1_s_vdf_omus_mcuid0228, (U2)RIMID_U1_VDF_MCUID0228);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0229_RL2_SEATSW   , &u1_s_vdf_omus_mcuid0229, (U2)RIMID_U1_VDF_MCUID0229);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0230_RR3_SEATSW   , &u1_s_vdf_omus_mcuid0230, (U2)RIMID_U1_VDF_MCUID0230);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0231_RC3_SEATSW   , &u1_s_vdf_omus_mcuid0231, (U2)RIMID_U1_VDF_MCUID0231);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0232_RL3_SEATSW   , &u1_s_vdf_omus_mcuid0232, (U2)RIMID_U1_VDF_MCUID0232);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0234_WALKTHROUGH  , &u1_s_vdf_omus_mcuid0234, (U2)RIMID_U1_VDF_MCUID0234);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID1138_SBR_TT_TYPE  , &u1_s_vdf_omus_mcuid1138, (U2)RIMID_U1_VDF_MCUID1138);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0590_SOC_PORTPOS  , &u1_s_vdf_omus_mcuid0590, (U2)RIMID_U1_VDF_MCUID0590);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0268_SWNUM        , &u1_s_vdf_omus_mcuid0268, (U2)RIMID_U1_VDF_MCUID0268);
    vd_s_VardefOmusCfgWriteU2(u2_CALIB_MCUID0262_MAXSPEED_KM  , &u2_s_vdf_omus_mcuid0262, (U2)RIMID_U2_VDF_MCUID0262);
    vd_s_VardefOmusCfgWriteU2(u2_CALIB_MCUID0263_MAXSPEED_MPH , &u2_s_vdf_omus_mcuid0263, (U2)RIMID_U2_VDF_MCUID0263);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0264_FSPO         , &u1_s_vdf_omus_mcuid0264, (U2)RIMID_U1_VDF_MCUID0264);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0341_TAIL         , &u1_s_vdf_omus_mcuid0341, (U2)RIMID_U1_VDF_MCUID0341);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID1135_SBELT_USA    , &u1_s_vdf_omus_mcuid1135, (U2)RIMID_U1_VDF_MCUID1135);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID1136_SBELT_CAN    , &u1_s_vdf_omus_mcuid1136, (U2)RIMID_U1_VDF_MCUID1136);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0604_SBELT_MEXICO , &u1_s_vdf_omus_mcuid0604, (U2)RIMID_U1_VDF_MCUID0604);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0605_SBELT_EU     , &u1_s_vdf_omus_mcuid0605, (U2)RIMID_U1_VDF_MCUID0605);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0606_SBELT_KOREA  , &u1_s_vdf_omus_mcuid0606, (U2)RIMID_U1_VDF_MCUID0606);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0607_SBELT_CHINA  , &u1_s_vdf_omus_mcuid0607, (U2)RIMID_U1_VDF_MCUID0607);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0809_MEXICO_LOW   , &u1_s_vdf_omus_mcuid0809, (U2)RIMID_U1_VDF_MCUID0809);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0810_KOREA_LOW    , &u1_s_vdf_omus_mcuid0810, (U2)RIMID_U1_VDF_MCUID0810);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID3020_GEN_LOW      , &u1_s_vdf_omus_mcuid3020, (U2)RIMID_U1_VDF_MCUID3020);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0024_BRAND        , &u1_s_vdf_omus_mcuid0024, (U2)RIMID_U1_VDF_MCUID0024);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0025_SPORTS       , &u1_s_vdf_omus_mcuid0025, (U2)RIMID_U1_VDF_MCUID0025);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0235_BODYSHAPE    , &u1_s_vdf_omus_mcuid0235, (U2)RIMID_U1_VDF_MCUID0235);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0250_FE_CONV      , &u1_s_vdf_omus_mcuid0250, (U2)RIMID_U1_VDF_MCUID0250);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0251_FE_HV        , &u1_s_vdf_omus_mcuid0251, (U2)RIMID_U1_VDF_MCUID0251);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0252_FE_PHV       , &u1_s_vdf_omus_mcuid0252, (U2)RIMID_U1_VDF_MCUID0252);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0253_FE_FC        , &u1_s_vdf_omus_mcuid0253, (U2)RIMID_U1_VDF_MCUID0253);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0254_PE_PHV       , &u1_s_vdf_omus_mcuid0254, (U2)RIMID_U1_VDF_MCUID0254);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID0255_PE_EV        , &u1_s_vdf_omus_mcuid0255, (U2)RIMID_U1_VDF_MCUID0255);
    vd_s_VardefOmusCfgWriteU1(u1_CALIB_MCUID3025_COMB_SW_POS  , &u1_s_vdf_omus_mcuid3025, (U2)RIMID_U1_VDF_MCUID3025);
}

/*===================================================================================================================================*/
/*  void    vd_g_VardefOmusCfgMCUIDRstwkInt(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefOmusCfgMCUIDRstwkInt(void)
{
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0798_TRNLMPCLR    , &u1_s_vdf_omus_mcuid0798, (U2)RIMID_U1_VDF_MCUID0798);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0209_RRCYM        , &u1_s_vdf_omus_mcuid0209, (U2)RIMID_U1_VDF_MCUID0209);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0210_RLCYM        , &u1_s_vdf_omus_mcuid0210, (U2)RIMID_U1_VDF_MCUID0210);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0211_BCTYM        , &u1_s_vdf_omus_mcuid0211, (U2)RIMID_U1_VDF_MCUID0211);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0212_LGCYM        , &u1_s_vdf_omus_mcuid0212, (U2)RIMID_U1_VDF_MCUID0212);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0213_HDCY_BDBM    , &u1_s_vdf_omus_mcuid0213, (U2)RIMID_U1_VDF_MCUID0213);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0214_RPSDWARNM    , &u1_s_vdf_omus_mcuid0214, (U2)RIMID_U1_VDF_MCUID0214);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0215_LPSDWARNM    , &u1_s_vdf_omus_mcuid0215, (U2)RIMID_U1_VDF_MCUID0215);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0233_RDOOR        , &u1_s_vdf_omus_mcuid0233, (U2)RIMID_U1_VDF_MCUID0233);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0224_RR_SEATSW    , &u1_s_vdf_omus_mcuid0224, (U2)RIMID_U1_VDF_MCUID0224);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0225_RC_SEATSW    , &u1_s_vdf_omus_mcuid0225, (U2)RIMID_U1_VDF_MCUID0225);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0226_RL_SEATSW    , &u1_s_vdf_omus_mcuid0226, (U2)RIMID_U1_VDF_MCUID0226);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0227_RR2_SEATSW   , &u1_s_vdf_omus_mcuid0227, (U2)RIMID_U1_VDF_MCUID0227);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0228_RC2_SEATSW   , &u1_s_vdf_omus_mcuid0228, (U2)RIMID_U1_VDF_MCUID0228);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0229_RL2_SEATSW   , &u1_s_vdf_omus_mcuid0229, (U2)RIMID_U1_VDF_MCUID0229);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0230_RR3_SEATSW   , &u1_s_vdf_omus_mcuid0230, (U2)RIMID_U1_VDF_MCUID0230);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0231_RC3_SEATSW   , &u1_s_vdf_omus_mcuid0231, (U2)RIMID_U1_VDF_MCUID0231);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0232_RL3_SEATSW   , &u1_s_vdf_omus_mcuid0232, (U2)RIMID_U1_VDF_MCUID0232);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0234_WALKTHROUGH  , &u1_s_vdf_omus_mcuid0234, (U2)RIMID_U1_VDF_MCUID0234);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID1138_SBR_TT_TYPE  , &u1_s_vdf_omus_mcuid1138, (U2)RIMID_U1_VDF_MCUID1138);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0590_SOC_PORTPOS  , &u1_s_vdf_omus_mcuid0590, (U2)RIMID_U1_VDF_MCUID0590);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0268_SWNUM        , &u1_s_vdf_omus_mcuid0268, (U2)RIMID_U1_VDF_MCUID0268);
    vd_s_VardefOmusCfgRimReadU2(u2_CALIB_MCUID0262_MAXSPEED_KM  , &u2_s_vdf_omus_mcuid0262, (U2)RIMID_U2_VDF_MCUID0262);
    vd_s_VardefOmusCfgRimReadU2(u2_CALIB_MCUID0263_MAXSPEED_MPH , &u2_s_vdf_omus_mcuid0263, (U2)RIMID_U2_VDF_MCUID0263);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0264_FSPO         , &u1_s_vdf_omus_mcuid0264, (U2)RIMID_U1_VDF_MCUID0264);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0341_TAIL         , &u1_s_vdf_omus_mcuid0341, (U2)RIMID_U1_VDF_MCUID0341);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID1135_SBELT_USA    , &u1_s_vdf_omus_mcuid1135, (U2)RIMID_U1_VDF_MCUID1135);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID1136_SBELT_CAN    , &u1_s_vdf_omus_mcuid1136, (U2)RIMID_U1_VDF_MCUID1136);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0604_SBELT_MEXICO , &u1_s_vdf_omus_mcuid0604, (U2)RIMID_U1_VDF_MCUID0604);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0605_SBELT_EU     , &u1_s_vdf_omus_mcuid0605, (U2)RIMID_U1_VDF_MCUID0605);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0606_SBELT_KOREA  , &u1_s_vdf_omus_mcuid0606, (U2)RIMID_U1_VDF_MCUID0606);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0607_SBELT_CHINA  , &u1_s_vdf_omus_mcuid0607, (U2)RIMID_U1_VDF_MCUID0607);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0809_MEXICO_LOW   , &u1_s_vdf_omus_mcuid0809, (U2)RIMID_U1_VDF_MCUID0809);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0810_KOREA_LOW    , &u1_s_vdf_omus_mcuid0810, (U2)RIMID_U1_VDF_MCUID0810);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID3020_GEN_LOW      , &u1_s_vdf_omus_mcuid3020, (U2)RIMID_U1_VDF_MCUID3020);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0024_BRAND        , &u1_s_vdf_omus_mcuid0024, (U2)RIMID_U1_VDF_MCUID0024);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0025_SPORTS       , &u1_s_vdf_omus_mcuid0025, (U2)RIMID_U1_VDF_MCUID0025);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0235_BODYSHAPE    , &u1_s_vdf_omus_mcuid0235, (U2)RIMID_U1_VDF_MCUID0235);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0250_FE_CONV      , &u1_s_vdf_omus_mcuid0250, (U2)RIMID_U1_VDF_MCUID0250);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0251_FE_HV        , &u1_s_vdf_omus_mcuid0251, (U2)RIMID_U1_VDF_MCUID0251);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0252_FE_PHV       , &u1_s_vdf_omus_mcuid0252, (U2)RIMID_U1_VDF_MCUID0252);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0253_FE_FC        , &u1_s_vdf_omus_mcuid0253, (U2)RIMID_U1_VDF_MCUID0253);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0254_PE_PHV       , &u1_s_vdf_omus_mcuid0254, (U2)RIMID_U1_VDF_MCUID0254);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID0255_PE_EV        , &u1_s_vdf_omus_mcuid0255, (U2)RIMID_U1_VDF_MCUID0255);
    vd_s_VardefOmusCfgRimReadU1(u1_CALIB_MCUID3025_COMB_SW_POS  , &u1_s_vdf_omus_mcuid3025, (U2)RIMID_U1_VDF_MCUID3025);
}

/*===================================================================================================================================*/
/*  void    vd_g_VardefOmusCfgMCUIDJDG(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefOmusCfgMCUIDJDG(const U1* u1_ap_can_pck)
{
    vd_s_VardefOmusCfgMCUID0798Jdg(u1_ap_can_pck[VDF_OMUS_CAN_TSLCLR_B]);
    vd_s_VardefOmusCfgMCUID0209Jdg(u1_ap_can_pck[VDF_OMUS_CAN_RRCT_B]);
    vd_s_VardefOmusCfgMCUID0210Jdg(u1_ap_can_pck[VDF_OMUS_CAN_RLCT_B]);
    vd_s_VardefOmusCfgMCUID0211Jdg(u1_ap_can_pck[VDF_OMUS_CAN_LGTR_B]);
    vd_s_VardefOmusCfgMCUID0212Jdg(u1_ap_can_pck[VDF_OMUS_CAN_LGTR_B]);
    vd_s_VardefOmusCfgMCUID0213Jdg(u1_ap_can_pck[VDF_OMUS_CAN_HDCT_B]);
    vd_s_VardefOmusCfgMCUID0214Jdg(u1_ap_can_pck[VDF_OMUS_CAN_RPSD_B]);
    vd_s_VardefOmusCfgMCUID0215Jdg(u1_ap_can_pck[VDF_OMUS_CAN_LPSD_B]);
    vd_s_VardefOmusCfgMCUID0233Jdg(u1_ap_can_pck[VDF_OMUS_CAN_RRDR_B]);
    vd_s_VardefOmusCfgMCUID0224Jdg(u1_ap_can_pck[VDF_OMUS_CAN_RRODS_B]);
    vd_s_VardefOmusCfgMCUID0225Jdg(u1_ap_can_pck[VDF_OMUS_CAN_RCODS_B]);
    vd_s_VardefOmusCfgMCUID0226Jdg(u1_ap_can_pck[VDF_OMUS_CAN_RLODS_B]);
    vd_s_VardefOmusCfgMCUID0227Jdg(u1_ap_can_pck[VDF_OMUS_CAN_R2RODS_B]);
    vd_s_VardefOmusCfgMCUID0228Jdg(u1_ap_can_pck[VDF_OMUS_CAN_R2CODS_B]);
    vd_s_VardefOmusCfgMCUID0229Jdg(u1_ap_can_pck[VDF_OMUS_CAN_R2LODS_B]);
    vd_s_VardefOmusCfgMCUID0230Jdg(u1_ap_can_pck[VDF_OMUS_CAN_R3RODS_B]);
    vd_s_VardefOmusCfgMCUID0231Jdg(u1_ap_can_pck[VDF_OMUS_CAN_R3CODS_B]);
    vd_s_VardefOmusCfgMCUID0232Jdg(u1_ap_can_pck[VDF_OMUS_CAN_R3LODS_B]);
    vd_s_VardefOmusCfgMCUID0234Jdg(u1_ap_can_pck[VDF_OMUS_CAN_FBWTH_B]);
    vd_s_VardefOmusCfgMCUID1138Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METSRT_B]);
    vd_s_VardefOmusCfgMCUID0590Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCPD_B]);
    vd_s_VardefOmusCfgMCUID0268Jdg(u1_ap_can_pck[VDF_OMUS_CAN_OMBINF_B]);
    vd_s_VardefOmusCfgMCUID0262Jdg(u1_ap_can_pck[VDF_OMUS_CAN_SPMKM_B]);
    vd_s_VardefOmusCfgMCUID0263Jdg(u1_ap_can_pck[VDF_OMUS_CAN_SPMMPH_B]);
    vd_s_VardefOmusCfgMCUID0264Jdg(u1_ap_can_pck[VDF_OMUS_CAN_SPMFSP_B]);
    vd_s_VardefOmusCfgMCUID0341Jdg(u1_ap_can_pck[VDF_OMUS_CAN_DIMFTL_B]);
    vd_s_VardefOmusCfgMCUID1135Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCSR_B]);
    vd_s_VardefOmusCfgMCUID1136Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCSR_B]);
    vd_s_VardefOmusCfgMCUID0604Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCSR_B]);
    vd_s_VardefOmusCfgMCUID0605Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCSR_B]);
    vd_s_VardefOmusCfgMCUID0606Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCSR_B]);
    vd_s_VardefOmusCfgMCUID0607Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCSR_B]);
    vd_s_VardefOmusCfgMCUID0809Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCTT_B]);
    vd_s_VardefOmusCfgMCUID0810Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCTT_B]);
    vd_s_VardefOmusCfgMCUID3020Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METCTT_B]);
    vd_s_VardefOmusCfgMCUID0024Jdg(u1_ap_can_pck[VDF_OMUS_CAN_BRAND_B]);
    vd_s_VardefOmusCfgMCUID0025Jdg(u1_ap_can_pck[VDF_OMUS_CAN_METSPO_B]);
    vd_s_VardefOmusCfgMCUID0235Jdg(u1_ap_can_pck[VDF_OMUS_CAN_BDSTL_B]);
    vd_s_VardefOmusCfgMCUID0250Jdg(u1_ap_can_pck[VDF_OMUS_CAN_FC_SCL_B]);
    vd_s_VardefOmusCfgMCUID0251Jdg(u1_ap_can_pck[VDF_OMUS_CAN_FC_SCL_B]);
    vd_s_VardefOmusCfgMCUID0252Jdg(u1_ap_can_pck[VDF_OMUS_CAN_FC_SCL_B]);
    vd_s_VardefOmusCfgMCUID0253Jdg(u1_ap_can_pck[VDF_OMUS_CAN_FC_SCL_B]);
    vd_s_VardefOmusCfgMCUID0254Jdg(u1_ap_can_pck[VDF_OMUS_CAN_EC_SCL_B]);
    vd_s_VardefOmusCfgMCUID0255Jdg(u1_ap_can_pck[VDF_OMUS_CAN_EC_SCL_B]);
    vd_s_VardefOmusCfgMCUID3025Jdg(u1_ap_can_pck[VDF_OMUS_CAN_CSWPOS_B]);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0798Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0798Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_TSLCLR_B_YL:
            u1_t_val = (U1)CALIB_MCUID0798_YL;
            break;
        case (U1)VDF_OMUS_TSLCLR_B_RD:
            u1_t_val = (U1)CALIB_MCUID0798_RD;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0798, (U1)VDF_OMUS_MCUID0798_NUM, u1_CALIB_MCUID0798_TRNLMPCLR);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0798, (U2)RIMID_U1_VDF_MCUID0798);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0798(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0798(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0798, (U1)VDF_OMUS_MCUID0798_NUM, u1_CALIB_MCUID0798_TRNLMPCLR);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0209Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0209Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_RRCT_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0209_OFF;
            break;
        case (U1)VDF_OMUS_RRCT_B_ON:
            u1_t_val = (U1)CALIB_MCUID0209_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0209, (U1)VDF_OMUS_MCUID0209_NUM, u1_CALIB_MCUID0209_RRCYM);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0209, (U2)RIMID_U1_VDF_MCUID0209);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0209(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0209(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0209, (U1)VDF_OMUS_MCUID0209_NUM, u1_CALIB_MCUID0209_RRCYM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0210Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0210Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_RLCT_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0210_OFF;
            break;
        case (U1)VDF_OMUS_RLCT_B_ON:
            u1_t_val = (U1)CALIB_MCUID0210_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0210, (U1)VDF_OMUS_MCUID0210_NUM, u1_CALIB_MCUID0210_RLCYM);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0210, (U2)RIMID_U1_VDF_MCUID0210);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0210(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0210(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0210, (U1)VDF_OMUS_MCUID0210_NUM, u1_CALIB_MCUID0210_RLCYM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0211Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0211Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_LGTR_B_TR:
            u1_t_val = (U1)CALIB_MCUID0211_OFF;
            break;
        case (U1)VDF_OMUS_LGTR_B_BD:
            u1_t_val = (U1)CALIB_MCUID0211_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0211, (U1)VDF_OMUS_MCUID0211_NUM, u1_CALIB_MCUID0211_BCTYM);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0211, (U2)RIMID_U1_VDF_MCUID0211);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0211(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0211(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0211, (U1)VDF_OMUS_MCUID0211_NUM, u1_CALIB_MCUID0211_BCTYM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0212Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0212Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_LGTR_B_TR:
            u1_t_val = (U1)CALIB_MCUID0212_ON;
            break;
        case (U1)VDF_OMUS_LGTR_B_BD:
            u1_t_val = (U1)CALIB_MCUID0212_OFF;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0212, (U1)VDF_OMUS_MCUID0212_NUM, u1_CALIB_MCUID0212_LGCYM);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0212, (U2)RIMID_U1_VDF_MCUID0212);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0212(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0212(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0212, (U1)VDF_OMUS_MCUID0212_NUM, u1_CALIB_MCUID0212_LGCYM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0213Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0213Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_HDCT_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0213_OFF;
            break;
        case (U1)VDF_OMUS_HDCT_B_ON:
            u1_t_val = (U1)CALIB_MCUID0213_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0213, (U1)VDF_OMUS_MCUID0213_NUM, u1_CALIB_MCUID0213_HDCY_BDBM);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0213, (U2)RIMID_U1_VDF_MCUID0213);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0213(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0213(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0213, (U1)VDF_OMUS_MCUID0213_NUM, u1_CALIB_MCUID0213_HDCY_BDBM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0214Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0214Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_RPSD_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0214_OFF;
            break;
        case (U1)VDF_OMUS_RPSD_B_ON:
            u1_t_val = (U1)CALIB_MCUID0214_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0214, (U1)VDF_OMUS_MCUID0214_NUM, u1_CALIB_MCUID0214_RPSDWARNM);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0214, (U2)RIMID_U1_VDF_MCUID0214);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0214(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0214(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0214, (U1)VDF_OMUS_MCUID0214_NUM, u1_CALIB_MCUID0214_RPSDWARNM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0215Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0215Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_LPSD_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0215_OFF;
            break;
        case (U1)VDF_OMUS_LPSD_B_ON:
            u1_t_val = (U1)CALIB_MCUID0215_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0215, (U1)VDF_OMUS_MCUID0215_NUM, u1_CALIB_MCUID0215_LPSDWARNM);
            break;
        }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0215, (U2)RIMID_U1_VDF_MCUID0215);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0215(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0215(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0215, (U1)VDF_OMUS_MCUID0215_NUM, u1_CALIB_MCUID0215_LPSDWARNM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0233Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0233Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_RRDR_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0233_OFF;
            break;
        case (U1)VDF_OMUS_RRDR_B_ON:
            u1_t_val = (U1)CALIB_MCUID0233_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0233, (U1)VDF_OMUS_MCUID0233_NUM, u1_CALIB_MCUID0233_RDOOR);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0233, (U2)RIMID_U1_VDF_MCUID0233);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0233(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0233(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0233, (U1)VDF_OMUS_MCUID0233_NUM, u1_CALIB_MCUID0233_RDOOR);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0224Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0224Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_RRODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0224_OFF;
            break;
        case (U1)VDF_OMUS_RRODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0224_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0224, (U1)VDF_OMUS_MCUID0224_NUM, u1_CALIB_MCUID0224_RR_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0224, (U2)RIMID_U1_VDF_MCUID0224);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0224(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0224(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0224, (U1)VDF_OMUS_MCUID0224_NUM, u1_CALIB_MCUID0224_RR_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0225Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0225Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_RCODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0225_OFF;
            break;
        case (U1)VDF_OMUS_RCODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0225_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0225, (U1)VDF_OMUS_MCUID0225_NUM, u1_CALIB_MCUID0225_RC_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0225, (U2)RIMID_U1_VDF_MCUID0225);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0225(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0225(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0225, (U1)VDF_OMUS_MCUID0225_NUM, u1_CALIB_MCUID0225_RC_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0226Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0226Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_RLODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0226_OFF;
            break;
        case (U1)VDF_OMUS_RLODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0226_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0226, (U1)VDF_OMUS_MCUID0226_NUM, u1_CALIB_MCUID0226_RL_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0226, (U2)RIMID_U1_VDF_MCUID0226);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0226(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0226(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0226, (U1)VDF_OMUS_MCUID0226_NUM, u1_CALIB_MCUID0226_RL_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0227Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0227Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_R2RODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0227_OFF;
            break;
        case (U1)VDF_OMUS_R2RODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0227_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0227, (U1)VDF_OMUS_MCUID0227_NUM, u1_CALIB_MCUID0227_RR2_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0227, (U2)RIMID_U1_VDF_MCUID0227);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0227(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0227(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0227, (U1)VDF_OMUS_MCUID0227_NUM, u1_CALIB_MCUID0227_RR2_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0228Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0228Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_R2CODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0228_OFF;
            break;
        case (U1)VDF_OMUS_R2CODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0228_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0228, (U1)VDF_OMUS_MCUID0228_NUM, u1_CALIB_MCUID0228_RC2_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0228, (U2)RIMID_U1_VDF_MCUID0228);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0228(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0228(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0228, (U1)VDF_OMUS_MCUID0228_NUM, u1_CALIB_MCUID0228_RC2_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0229Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0229Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_R2LODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0229_OFF;
            break;
        case (U1)VDF_OMUS_R2LODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0229_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0229, (U1)VDF_OMUS_MCUID0229_NUM, u1_CALIB_MCUID0229_RL2_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0229, (U2)RIMID_U1_VDF_MCUID0229);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0229(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0229(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0229, (U1)VDF_OMUS_MCUID0229_NUM, u1_CALIB_MCUID0229_RL2_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0230Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0230Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_R3RODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0230_OFF;
            break;
        case (U1)VDF_OMUS_R3RODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0230_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0230, (U1)VDF_OMUS_MCUID0230_NUM, u1_CALIB_MCUID0230_RR3_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0230, (U2)RIMID_U1_VDF_MCUID0230);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0230(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0230(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0230, (U1)VDF_OMUS_MCUID0230_NUM, u1_CALIB_MCUID0230_RR3_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0231Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0231Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_R3CODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0231_OFF;
            break;
        case (U1)VDF_OMUS_R3CODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0231_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0231, (U1)VDF_OMUS_MCUID0231_NUM, u1_CALIB_MCUID0231_RC3_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0231, (U2)RIMID_U1_VDF_MCUID0231);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0231(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0231(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0231, (U1)VDF_OMUS_MCUID0231_NUM, u1_CALIB_MCUID0231_RC3_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0232Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0232Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_R3LODS_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0232_OFF;
            break;
        case (U1)VDF_OMUS_R3LODS_B_ON:
            u1_t_val = (U1)CALIB_MCUID0232_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0232, (U1)VDF_OMUS_MCUID0232_NUM, u1_CALIB_MCUID0232_RL3_SEATSW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0232, (U2)RIMID_U1_VDF_MCUID0232);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0232(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0232(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0232, (U1)VDF_OMUS_MCUID0232_NUM, u1_CALIB_MCUID0232_RL3_SEATSW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0234Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0234Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_FBWTH_B_OFF:
            u1_t_val = (U1)CALIB_MCUID0234_OFF;
            break;
        case (U1)VDF_OMUS_FBWTH_B_ON:
            u1_t_val = (U1)CALIB_MCUID0234_ON;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0234, (U1)VDF_OMUS_MCUID0234_NUM, u1_CALIB_MCUID0234_WALKTHROUGH);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0234, (U2)RIMID_U1_VDF_MCUID0234);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0234(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0234(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0234, (U1)VDF_OMUS_MCUID0234_NUM, u1_CALIB_MCUID0234_WALKTHROUGH);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID1138Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID1138Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METSRT_B_1RRSEAT:
            u1_t_val = (U1)CALIB_MCUID1138_FMVSS_2R;
            break;
        case (U1)VDF_OMUS_METSRT_B_1RRSEAT_CTRSEAT:
            u1_t_val = (U1)CALIB_MCUID1138_FMVSS_2RC;
            break;
        case (U1)VDF_OMUS_METSRT_B_2RRSEAT:
            u1_t_val = (U1)CALIB_MCUID1138_FMVSS_3R;
            break;
        case (U1)VDF_OMUS_METSRT_B_NORSEAT:
            u1_t_val = (U1)CALIB_MCUID1138_FMVSS_1R;
            break;
        default: /* 4h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid1138, (U1)VDF_OMUS_MCUID1138_NUM, u1_CALIB_MCUID1138_SBR_TT_TYPE);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid1138, (U2)RIMID_U1_VDF_MCUID1138);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID1138(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID1138(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid1138, (U1)VDF_OMUS_MCUID1138_NUM, u1_CALIB_MCUID1138_SBR_TT_TYPE);
    return(u1_t_mcuiddata);
}


/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0590Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0590Jdg(const U1 u1_a_CANVAL)
{
    U1     u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCPD_B_NON:
            u1_t_val = (U1)CALIB_MCUID0590_NON;
            break;
        case (U1)VDF_OMUS_METCPD_B_RIGHT:
            u1_t_val = (U1)CALIB_MCUID0590_RIGHT;
            break;
        case (U1)VDF_OMUS_METCPD_B_LEFT:
            u1_t_val = (U1)CALIB_MCUID0590_LEFT;
            break;
        default: /* 3h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0590, (U1)VDF_OMUS_MCUID0590_NUM, u1_CALIB_MCUID0590_SOC_PORTPOS);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0590, (U2)RIMID_U1_VDF_MCUID0590);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0590(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0590(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0590, (U1)VDF_OMUS_MCUID0590_NUM, u1_CALIB_MCUID0590_SOC_PORTPOS);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0268Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0268Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_OMBINF_B_BUTTON_NON:
            u1_t_val = (U1)CALIB_MCUID0268_BUTTON_NON;
            break;
        case (U1)VDF_OMUS_OMBINF_B_BUTTON_1:
            u1_t_val = (U1)CALIB_MCUID0268_BUTTON_1;
            break;
        default: /* 2h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0268, (U1)VDF_OMUS_MCUID0268_NUM, u1_CALIB_MCUID0268_SWNUM);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0268, (U2)RIMID_U1_VDF_MCUID0268);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0268(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0268(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0268, (U1)VDF_OMUS_MCUID0268_NUM, u1_CALIB_MCUID0268_SWNUM);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0262Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0262Jdg(const U1 u1_a_CANVAL)
{
    U2 u2_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_SPMKM_B_120:
            u2_t_val = (U2)CALIB_MCUID0262_120KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_140:
            u2_t_val = (U2)CALIB_MCUID0262_140KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_160:
            u2_t_val = (U2)CALIB_MCUID0262_160KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_170:
            u2_t_val = (U2)CALIB_MCUID0262_170KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_180:
            u2_t_val = (U2)CALIB_MCUID0262_180KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_200:
            u2_t_val = (U2)CALIB_MCUID0262_200KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_220:
            u2_t_val = (U2)CALIB_MCUID0262_220KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_240:
            u2_t_val = (U2)CALIB_MCUID0262_240KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_260:
            u2_t_val = (U2)CALIB_MCUID0262_260KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_280:
            u2_t_val = (U2)CALIB_MCUID0262_280KM;
            break;
        case (U1)VDF_OMUS_SPMKM_B_360:
            u2_t_val = (U2)CALIB_MCUID0262_360KM;
            break;
        default: /* Ch~Eh:Reserved, Fh:Invalid */
            u2_t_val = u2_s_vdf_omus_mcuid0262;
            break;
    }
    vd_s_VardefOmusCfgWriteU2(u2_t_val, &u2_s_vdf_omus_mcuid0262, (U2)RIMID_U2_VDF_MCUID0262);
}

/*===================================================================================================================================*/
/*  U2      u2_g_VardefOmusMCUID0262(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_VardefOmusMCUID0262(void)
{
    return(u2_s_vdf_omus_mcuid0262);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0263Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0263Jdg(const U1 u1_a_CANVAL)
{
    U2 u2_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_SPMKM_B_120:
            u2_t_val = (U2)CALIB_MCUID0263_120MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_140:
            u2_t_val = (U2)CALIB_MCUID0263_140MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_160:
            u2_t_val = (U2)CALIB_MCUID0263_160MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_170:
            u2_t_val = (U2)CALIB_MCUID0263_170MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_180:
            u2_t_val = (U2)CALIB_MCUID0263_180MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_200:
            u2_t_val = (U2)CALIB_MCUID0263_200MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_220:
            u2_t_val = (U2)CALIB_MCUID0263_220MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_240:
            u2_t_val = (U2)CALIB_MCUID0263_240MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_260:
            u2_t_val = (U2)CALIB_MCUID0263_260MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_280:
            u2_t_val = (U2)CALIB_MCUID0263_280MPH;
            break;
        case (U1)VDF_OMUS_SPMKM_B_360:
            u2_t_val = (U2)CALIB_MCUID0263_360MPH;
            break;
        default: /* Ch~Eh:Reserved, Fh:Invalid */
            u2_t_val = u2_s_vdf_omus_mcuid0263;
            break;
    }
    vd_s_VardefOmusCfgWriteU2(u2_t_val, &u2_s_vdf_omus_mcuid0263, (U2)RIMID_U2_VDF_MCUID0263);
}

/*===================================================================================================================================*/
/*  U2      u2_g_VardefOmusMCUID0263(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_VardefOmusMCUID0263(void)
{
    return(u2_s_vdf_omus_mcuid0263);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0264Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0264Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_SPMFSP_B_NORMAL:
            u1_t_val = (U1)CALIB_MCUID0264_NORMAL;
            break;
        case (U1)VDF_OMUS_SPMFSP_B_FSPORT:
            u1_t_val = (U1)CALIB_MCUID0264_FSPORT;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0264, (U1)VDF_OMUS_MCUID0264_NUM, u1_CALIB_MCUID0264_FSPO);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0264, (U2)RIMID_U1_VDF_MCUID0264);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0264(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0264(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0264, (U1)VDF_OMUS_MCUID0264_NUM, u1_CALIB_MCUID0264_FSPO);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0341Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0341Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_DIMFTL_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID0341_ON;
            break;
        case (U1)VDF_OMUS_DIMFTL_B_OTHER:
            u1_t_val = (U1)CALIB_MCUID0341_OFF;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0341, (U1)VDF_OMUS_MCUID0341_NUM, u1_CALIB_MCUID0341_TAIL);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0341, (U2)RIMID_U1_VDF_MCUID0341);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0341(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0341(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0341, (U1)VDF_OMUS_MCUID0341_NUM, u1_CALIB_MCUID0341_TAIL);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID1135Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID1135Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCSR_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID1135_FMVSS;
            break;
        case (U1)VDF_OMUS_METCSR_B_UNR:
            u1_t_val = (U1)CALIB_MCUID1135_UNR;
            break;
        case (U1)VDF_OMUS_METCSR_B_CHN:
            u1_t_val = (U1)CALIB_MCUID1135_CHN;
            break;
        default: /* 3h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid1135, (U1)VDF_OMUS_MCUID1135_NUM, u1_CALIB_MCUID1135_SBELT_USA);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid1135, (U2)RIMID_U1_VDF_MCUID1135);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID1135(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID1135(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid1135, (U1)VDF_OMUS_MCUID1135_NUM, u1_CALIB_MCUID1135_SBELT_USA);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID1136Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID1136Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCSR_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID1136_FMVSS;
            break;
        case (U1)VDF_OMUS_METCSR_B_UNR:
            u1_t_val = (U1)CALIB_MCUID1136_UNR;
            break;
        case (U1)VDF_OMUS_METCSR_B_CHN:
            u1_t_val = (U1)CALIB_MCUID1136_CHN;
            break;
        default: /* 3h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid1136, (U1)VDF_OMUS_MCUID1136_NUM, u1_CALIB_MCUID1136_SBELT_CAN);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid1136, (U2)RIMID_U1_VDF_MCUID1136);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID1136(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID1136(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid1136, (U1)VDF_OMUS_MCUID1136_NUM, u1_CALIB_MCUID1136_SBELT_CAN);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0604Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0604Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCSR_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID0604_FMVSS;
            break;
        case (U1)VDF_OMUS_METCSR_B_UNR:
            u1_t_val = (U1)CALIB_MCUID0604_UNR;
            break;
        case (U1)VDF_OMUS_METCSR_B_CHN:
            u1_t_val = (U1)CALIB_MCUID0604_CHN;
            break;
        default: /* 3h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0604, (U1)VDF_OMUS_MCUID0604_NUM, u1_CALIB_MCUID0604_SBELT_MEXICO);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0604, (U2)RIMID_U1_VDF_MCUID0604);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0604(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0604(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0604, (U1)VDF_OMUS_MCUID0604_NUM, u1_CALIB_MCUID0604_SBELT_MEXICO);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0605Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0605Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCSR_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID0605_FMVSS;
            break;
        case (U1)VDF_OMUS_METCSR_B_UNR:
            u1_t_val = (U1)CALIB_MCUID0605_UNR;
            break;
        case (U1)VDF_OMUS_METCSR_B_CHN:
            u1_t_val = (U1)CALIB_MCUID0605_CHN;
            break;
        default: /* 3h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0605, (U1)VDF_OMUS_MCUID0605_NUM, u1_CALIB_MCUID0605_SBELT_EU);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0605, (U2)RIMID_U1_VDF_MCUID0605);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0605(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0605(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0605, (U1)VDF_OMUS_MCUID0605_NUM, u1_CALIB_MCUID0605_SBELT_EU);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0606Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0606Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCSR_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID0606_FMVSS;
            break;
        case (U1)VDF_OMUS_METCSR_B_UNR:
            u1_t_val = (U1)CALIB_MCUID0606_UNR;
            break;
        case (U1)VDF_OMUS_METCSR_B_CHN:
            u1_t_val = (U1)CALIB_MCUID0606_CHN;
            break;
        default: /* 3h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0606, (U1)VDF_OMUS_MCUID0606_NUM, u1_CALIB_MCUID0606_SBELT_KOREA);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0606, (U2)RIMID_U1_VDF_MCUID0606);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0606(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0606(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0606, (U1)VDF_OMUS_MCUID0606_NUM, u1_CALIB_MCUID0606_SBELT_KOREA);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0607Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0607Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCSR_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID0607_FMVSS;
            break;
        case (U1)VDF_OMUS_METCSR_B_UNR:
            u1_t_val = (U1)CALIB_MCUID0607_UNR;
            break;
        case (U1)VDF_OMUS_METCSR_B_CHN:
            u1_t_val = (U1)CALIB_MCUID0607_CHN;
            break;
        default: /* 3h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0607, (U1)VDF_OMUS_MCUID0607_NUM, u1_CALIB_MCUID0607_SBELT_CHINA);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0607, (U2)RIMID_U1_VDF_MCUID0607);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0607(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0607(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0607, (U1)VDF_OMUS_MCUID0607_NUM, u1_CALIB_MCUID0607_SBELT_CHINA);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0809Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0809Jdg(const U1 u1_a_CANVAL)
{
    
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCTT_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID0809_FMVSS;
            break;
        case (U1)VDF_OMUS_METCTT_B_UNR:
            u1_t_val = (U1)CALIB_MCUID0809_UNR;
            break;
        default: /* 2h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0809, (U1)VDF_OMUS_MCUID0809_NUM, u1_CALIB_MCUID0809_MEXICO_LOW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0809, (U2)RIMID_U1_VDF_MCUID0809);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0809(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0809(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0809, (U1)VDF_OMUS_MCUID0809_NUM, u1_CALIB_MCUID0809_MEXICO_LOW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0810Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0810Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCTT_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID0810_FMVSS;
            break;
        case (U1)VDF_OMUS_METCTT_B_UNR:
            u1_t_val = (U1)CALIB_MCUID0810_UNR;
            break;
        default: /* 2h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0810, (U1)VDF_OMUS_MCUID0810_NUM, u1_CALIB_MCUID0810_KOREA_LOW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0810, (U2)RIMID_U1_VDF_MCUID0810);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0810(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0810(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0810, (U1)VDF_OMUS_MCUID0810_NUM, u1_CALIB_MCUID0810_KOREA_LOW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID3020Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID3020Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METCTT_B_FMVSS:
            u1_t_val = (U1)CALIB_MCUID3020_FMVSS;
            break;
        case (U1)VDF_OMUS_METCTT_B_UNR:
            u1_t_val = (U1)CALIB_MCUID3020_UNR;
            break;
        default: /* 2h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid3020, (U1)VDF_OMUS_MCUID3020_NUM, u1_CALIB_MCUID3020_GEN_LOW);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid3020, (U2)RIMID_U1_VDF_MCUID3020);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID3020(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID3020(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid3020, (U1)VDF_OMUS_MCUID3020_NUM, u1_CALIB_MCUID3020_GEN_LOW);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0024Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0024Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_BRAND_B_TOYOTA:
        case (U1)VDF_OMUS_BRAND_B_GR:
            u1_t_val = (U1)CALIB_MCUID0024_TOYOTA;
            break;
        case (U1)VDF_OMUS_BRAND_B_LEXUS:
            u1_t_val = (U1)CALIB_MCUID0024_LEXUS;
            break;
        default: /* 7h(SUBARU), 4h~6h,8h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0024, (U1)VDF_OMUS_MCUID0024_NUM, u1_CALIB_MCUID0024_BRAND);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0024, (U2)RIMID_U1_VDF_MCUID0024);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0024(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0024(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0024, (U1)VDF_OMUS_MCUID0024_NUM, u1_CALIB_MCUID0024_BRAND);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0025Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0025Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_METSPO_B_NON:
            u1_t_val = (U1)CALIB_MCUID0025_NON;
            break;
        case (U1)VDF_OMUS_METSPO_B_GRS:
            u1_t_val = (U1)CALIB_MCUID0025_GRS;
            break;
        case (U1) VDF_OMUS_METSPO_B_GR:
            u1_t_val = (U1)CALIB_MCUID0025_GR;
            break;
        case (U1)VDF_OMUS_METSPO_B_GRMN:
            u1_t_val = (U1)CALIB_MCUID0025_GRMN;
            break;
        case (U1)VDF_OMUS_METSPO_B_FSPORT:
            u1_t_val = (U1)CALIB_MCUID0025_FSPORT;
            break;
        case (U1)VDF_OMUS_METSPO_B_F:
            u1_t_val = (U1)CALIB_MCUID0025_F;
            break;
        default: /* 7h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0025, (U1)VDF_OMUS_MCUID0025_NUM, u1_CALIB_MCUID0025_SPORTS);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0025, (U2)RIMID_U1_VDF_MCUID0025);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0025(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0025(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid0025, (U1)VDF_OMUS_MCUID0025_NUM, u1_CALIB_MCUID0025_SPORTS);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0235Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0235Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_BDSTL_B_OTHER:
            u1_t_val = (U1)CALIB_MCUID0235_OTHER;
            break;
        case (U1)VDF_OMUS_BDSTL_B_PICKUP_TRUCK:
            u1_t_val = (U1)CALIB_MCUID0235_PICKUP_TRUCK;
            break;
        default: /* 2h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibMCUID0235Chk(u1_s_vdf_omus_mcuid0235, u1_CALIB_MCUID0235_BODYSHAPE);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0235, (U2)RIMID_U1_VDF_MCUID0235);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0235(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0235(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibMCUID0235Chk(u1_s_vdf_omus_mcuid0235, u1_CALIB_MCUID0235_BODYSHAPE);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0250Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0250Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_FC_SCL_B_NO_1:
            u1_t_val = (U1)CALIB_MCUID0250_NO_1;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_2:
            u1_t_val = (U1)CALIB_MCUID0250_NO_2;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_3:
            u1_t_val = (U1)CALIB_MCUID0250_NO_3;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_4:
            u1_t_val = (U1)CALIB_MCUID0250_NO_4;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_5:
            u1_t_val = (U1)CALIB_MCUID0250_NO_5;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_6:
            u1_t_val = (U1)CALIB_MCUID0250_NO_6;
            break;
        default: /* 7h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0250, (U1)CALIB_MCUID0250_MIN, (U1)CALIB_MCUID0250_MAX, u1_CALIB_MCUID0250_FE_CONV);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0250, (U2)RIMID_U1_VDF_MCUID0250);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0250(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0250(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0250, (U1)CALIB_MCUID0250_MIN, (U1)CALIB_MCUID0250_MAX, u1_CALIB_MCUID0250_FE_CONV);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0251Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0251Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_FC_SCL_B_NO_1:
            u1_t_val = (U1)CALIB_MCUID0251_NO_1;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_2:
            u1_t_val = (U1)CALIB_MCUID0251_NO_2;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_3:
            u1_t_val = (U1)CALIB_MCUID0251_NO_3;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_4:
            u1_t_val = (U1)CALIB_MCUID0251_NO_4;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_5:
            u1_t_val = (U1)CALIB_MCUID0251_NO_5;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_6:
            u1_t_val = (U1)CALIB_MCUID0251_NO_6;
            break;
        default: /* 7h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0251, (U1)CALIB_MCUID0251_MIN, (U1)CALIB_MCUID0251_MAX, u1_CALIB_MCUID0251_FE_HV);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0251, (U2)RIMID_U1_VDF_MCUID0251);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0251(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0251(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0251, (U1)CALIB_MCUID0251_MIN, (U1)CALIB_MCUID0251_MAX, u1_CALIB_MCUID0251_FE_HV);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0252Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0252Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_FC_SCL_B_NO_1:
            u1_t_val = (U1)CALIB_MCUID0252_NO_1;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_2:
            u1_t_val = (U1)CALIB_MCUID0252_NO_2;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_3:
            u1_t_val = (U1)CALIB_MCUID0252_NO_3;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_4:
            u1_t_val = (U1)CALIB_MCUID0252_NO_4;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_5:
            u1_t_val = (U1)CALIB_MCUID0252_NO_5;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_6:
            u1_t_val = (U1)CALIB_MCUID0252_NO_6;
            break;
        default: /* 7h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0252, (U1)CALIB_MCUID0252_MIN, (U1)CALIB_MCUID0252_MAX, u1_CALIB_MCUID0252_FE_PHV);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0252, (U2)RIMID_U1_VDF_MCUID0252);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0252(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0252(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0252, (U1)CALIB_MCUID0252_MIN, (U1)CALIB_MCUID0252_MAX, u1_CALIB_MCUID0252_FE_PHV);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0253Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0253Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_FC_SCL_B_NO_1:
            u1_t_val = (U1)CALIB_MCUID0253_NO_1;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_2:
            u1_t_val = (U1)CALIB_MCUID0253_NO_2;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_3:
            u1_t_val = (U1)CALIB_MCUID0253_NO_3;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_4:
            u1_t_val = (U1)CALIB_MCUID0253_NO_4;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_5:
            u1_t_val = (U1)CALIB_MCUID0253_NO_5;
            break;
        case (U1)VDF_OMUS_FC_SCL_B_NO_6:
            u1_t_val = (U1)CALIB_MCUID0253_NO_6;
            break;
        default: /* 7h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0253, (U1)CALIB_MCUID0253_MIN, (U1)CALIB_MCUID0253_MAX, u1_CALIB_MCUID0253_FE_FC);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0253, (U2)RIMID_U1_VDF_MCUID0253);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0253(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0253(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0253, (U1)CALIB_MCUID0253_MIN, (U1)CALIB_MCUID0253_MAX, u1_CALIB_MCUID0253_FE_FC);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0254Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0254Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;
    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_EC_SCL_B_NO_1:
            u1_t_val = (U1)CALIB_MCUID0254_NO_1;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_2:
            u1_t_val = (U1)CALIB_MCUID0254_NO_2;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_3:
            u1_t_val = (U1)CALIB_MCUID0254_NO_3;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_4:
            u1_t_val = (U1)CALIB_MCUID0254_NO_4;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_5:
            u1_t_val = (U1)CALIB_MCUID0254_NO_5;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_6:
            u1_t_val = (U1)CALIB_MCUID0254_NO_6;
            break;
        default: /* 7h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0254, (U1)CALIB_MCUID0254_MIN, (U1)CALIB_MCUID0254_MAX, u1_CALIB_MCUID0254_PE_PHV);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0254, (U2)RIMID_U1_VDF_MCUID0254);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0254(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0254(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0254, (U1)CALIB_MCUID0254_MIN, (U1)CALIB_MCUID0254_MAX, u1_CALIB_MCUID0254_PE_PHV);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID0255Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID0255Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_EC_SCL_B_NO_1:
            u1_t_val = (U1)CALIB_MCUID0255_NO_1;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_2:
            u1_t_val = (U1)CALIB_MCUID0255_NO_2;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_3:
            u1_t_val = (U1)CALIB_MCUID0255_NO_3;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_4:
            u1_t_val = (U1)CALIB_MCUID0255_NO_4;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_5:
            u1_t_val = (U1)CALIB_MCUID0255_NO_5;
            break;
        case (U1)VDF_OMUS_EC_SCL_B_NO_6:
            u1_t_val = (U1)CALIB_MCUID0255_NO_6;
            break;
        default: /* 7h~Eh:Reserved, Fh:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0255, (U1)CALIB_MCUID0255_MIN, (U1)CALIB_MCUID0255_MAX, u1_CALIB_MCUID0255_PE_EV);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid0255, (U2)RIMID_U1_VDF_MCUID0255);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID0255(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID0255(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibMinMaxChk(u1_s_vdf_omus_mcuid0255, (U1)CALIB_MCUID0255_MIN, (U1)CALIB_MCUID0255_MAX, u1_CALIB_MCUID0255_PE_EV);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*  static void         vd_s_VardefOmusCfgMCUID3025Jdg(const U1 u1_a_CANVAL)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_VardefOmusCfgMCUID3025Jdg(const U1 u1_a_CANVAL)
{
    U1 u1_t_val;

    switch (u1_a_CANVAL){
        case (U1)VDF_OMUS_CSWPOS_B_R_LIT_L_WIP:
            u1_t_val = (U1)CALIB_MCUID3025_R_LIT_L_WIP;
            break;
        case (U1)VDF_OMUS_CSWPOS_B_R_WIP_L_LIT:
            u1_t_val = (U1)CALIB_MCUID3025_R_WIP_L_LIT;
            break;
        default: /* 10b:Reserved, 11b:Invalid */
            u1_t_val = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid3025, (U1)VDF_OMUS_MCUID3025_NUM, u1_CALIB_MCUID3025_COMB_SW_POS);
            break;
    }
    vd_s_VardefOmusCfgWriteU1(u1_t_val, &u1_s_vdf_omus_mcuid3025, (U2)RIMID_U1_VDF_MCUID3025);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefOmusMCUID3025(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefOmusMCUID3025(void)
{
    U1 u1_t_mcuiddata;

    u1_t_mcuiddata = u1_s_VardefOmusCfgCalibNumChk(u1_s_vdf_omus_mcuid3025, (U1)VDF_OMUS_MCUID3025_NUM, u1_CALIB_MCUID3025_COMB_SW_POS);
    return(u1_t_mcuiddata);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/22/2026  SH       New.                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1     1/22/2026  SH       New.                                                                                               */
/*                                                                                                                                   */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
