/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HMI communication I/F control G monitor peak hold processing                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef HMIGMON_CFG_H
#define HMIGMON_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIGMON_CFG_H_MAJOR                      (1)
#define HMIGMON_CFG_H_MINOR                      (0)
#define HMIGMON_CFG_H_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "calibration.h"
#include "veh_opemd.h"

#include "g_monitor.h"

#include "hmigmon.h"

#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIGMON_LSBCHNG_CANTOTFT                 (1U)                    /* Coefficient for converting CAN data LSB to coordinates    */
                                                                        /* (1LSB : 1dot)                                             */

#define HMIGMON_PEAKHOLD_DIST_DEF                (0U)                   /* gravity acceleration distance value :initial value        */

#define HMIGMON_PEAKHOLD_RESET_HOLD              (0U)                   /* peak hold reset request :retention                        */
#define HMIGMON_PEAKHOLD_RESET_RESET             (1U)                   /* peak hold reset request :reset                            */

#define HMIGMON_TAN_NON                          (0U)                   /* TANGENT value :initial value                              */

#define HMIGMON_MOVE_NUM                         (2U)                   /* number of directions of gravity acceleration movement     */

#define HMIGMON_MOVE_FRONT                       (0U)                   /* direction of gravity acceleration movement :front         */
#define HMIGMON_MOVE_BACK                        (1U)                   /* direction of gravity acceleration movement :back          */

#define HMIGMON_MOVE_RIGHT                       (0U)                   /* direction of gravity acceleration movement :right         */
#define HMIGMON_MOVE_LEFT                        (1U)                   /* direction of gravity acceleration movement :left          */

#define HMIGMON_GCDN_MULU                        (10U)                  /* LSB conversion                                            */
#define HMIGMON_GCDN_MAX                         (u1_CALIB_MCUID0219_G_GAUGE_MAX * HMIGMON_GCDN_MULU)
                                                                        /* gravitational acceleration[coordinates] Max Value         */
#define HMIGMON_GCDN_DIST_MAX                    (HMIGMON_GCDN_MAX * HMIGMON_GCDN_MAX) /* Distance to circle perimeter               */
#define HMIGMON_VAL_MAX                          (u1_CALIB_MCUID0221_G_DISP_MAX)
                                                                        /* gravitational acceleration Max Value                       */

#define HMIGMON_TANSEAECH_NUM                    (3U)                   /* TANGENT Number of angles for retrieval                    */

#define HMIGMON_VISIBLE_FALSE                    (0U)                   /* G Monitor Hide                                            */
#define HMIGMON_VISIBLE_TRUE                     (1U)                   /* G Monitor View                                            */

/* Total Area is defined in hmigmon.h. */
#define HMIGMON_TAN_ANGLE_0                      (0U)                   /* Area number at position   0 degrees (total number of areas * (0/4))  */
#define HMIGMON_TAN_ANGLE_90                     (3U)                   /* Area number at position  90 degrees (total number of areas * (1/4))  */
#define HMIGMON_TAN_ANGLE_180                    (6U)                   /* Area number at position 180 degrees (total number of areas * (2/4))  */
#define HMIGMON_TAN_ANGLE_270                    (9U)                   /* Area number at position 270 degrees (total number of areas * (3/4))  */
#define HMIGMON_TAN_ANGLE_360                    (12U)                  /* Area number at position 360 degrees (total number of areas * (4/4))  */

#define HMIGMON_MINQUADRANT                      (0U)                   /* minimum quadrant  0 degrees or 180 degrees                */

#define HMIGMON_MOVE_1ST                         (0U)                   /* Direction:Right Front (  0- 88 degrees)                   */
#define HMIGMON_MOVE_2ND                         (1U)                   /* Direction:Left  Front ( 92-180 degrees)                   */
#define HMIGMON_MOVE_3RD                         (2U)                   /* Direction:Left  Back  (184-268 degrees)                   */
#define HMIGMON_MOVE_4TH                         (3U)                   /* Direction:Right Back  (272-356 degrees)                   */

#define HMIGMON_TAN_ACCURACY                     (100U)                 /* TANGENT calculation accuracy  :Convert to 100 x           */
#define HMIGMON_DIS_ACCURACY                     (100U)                 /* distance calculation accuracy :Convert to 100 x           */

/* Gravitational acceleration     */
#define HMIGMON_VAL_FRTBK_MAX                   ((S2)HMIGMON_VAL_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT)                   /* vertical value(Before or After Value)Max Value      */
#define HMIGMON_VAL_FRTBK_MIN                   (((S2)HMIGMON_VAL_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT) * ((S2)(-1)))    /* vertical value(Before or After Value)Minimum value  */
#define HMIGMON_VAL_RGTLFT_MAX                  ((S2)HMIGMON_VAL_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT)                   /* horizontal value(Left or Right Value)Max Value      */
#define HMIGMON_VAL_RGTLFT_MIN                  (((S2)HMIGMON_VAL_MAX * (S2)HMIGMON_LSBCHNG_CANTOTFT) * ((S2)(-1)))    /* horizontal value(Left or Right Value)Minimum value  */

#define HMIGMON_GCDN_NUM                         (2U)                   /* coordinate Num X,Y                                        */
#define HMIGMON_GCDN_Y                           (0U)                   /* Y-coordinate ID                                           */
#define HMIGMON_GCDN_X                           (1U)                   /* X-coordinate ID                                           */

#define HMIGMON_R_SIN0_180                       (0)                    /* Sin0_180 coefficient                                      */
#define HMIGMON_R_SIN30_150                      (50)                   /* Sin30_150 coefficient                                     */
#define HMIGMON_R_SIN60_120                      (86)                   /* Sin60_120 coefficient                                     */
#define HMIGMON_R_SIN90                          (100)                  /* Sin90 coefficient                                         */
#define HMIGMON_R_SIN210_330                     (-50)                  /* Sin210_330 coefficient                                    */
#define HMIGMON_R_SIN240_300                     (-86)                  /* Sin240_300 coefficient                                    */
#define HMIGMON_R_SIN270                         (-100)                 /* Sin270 coefficient                                        */
#define HMIGMON_R_COS0                           (100)                  /* Cos0 coefficient                                          */
#define HMIGMON_R_COS30_330                      (86)                   /* Cos30-330 coefficient                                     */
#define HMIGMON_R_COS60_300                      (50)                   /* Cos60-300 coefficient                                     */
#define HMIGMON_R_COS90_270                      (0)                    /* Cos90-270 coefficient                                     */
#define HMIGMON_R_COS120_240                     (-50)                  /* Cos120-240 coefficient                                    */
#define HMIGMON_R_COS150_210                     (-86)                  /* Cos150-210 coefficient                                    */
#define HMIGMON_R_COS180                         (-100)                 /* Cos180 coefficient                                        */
#define HMIGMON_MAXGUARD_DIV                     (100)                  /* MAX Guard arithmetic accuracy coefficient                 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_HMIGMON_IG_ISON()                     (u1_g_VehopemdIgnOn())

#define u1_HMIGMON_MOVE_FRTBK()                  (u1_g_GmntrGetdrc((U1)GMNTR_FB_INF))/* gravitational acceleration(front and back)direction of movement */
#define u1_HMIGMON_MOVE_RGTLFT()                 (u1_g_GmntrGetdrc((U1)GMNTR_LR_INF))/* gravitational acceleration(right and left)direction of movement */
#define u1_HMIGMON_MOVE_VAL_FRTBK()              (u1_g_GmntrGetvaldrc((U1)GMNTR_FB_INF))
#define u1_HMIGMON_MOVE_VAL_RGTLFT()             (u1_g_GmntrGetvaldrc((U1)GMNTR_LR_INF))
#define u2_HMIGMON_GCDN_FRTBK()                  (u2_g_GmntrGetPos((U1)GMNTR_FB_INF))/* gravitational acceleration(front and back)[coordinates]         */
#define u2_HMIGMON_GCDN_RGTLFT()                 (u2_g_GmntrGetPos((U1)GMNTR_LR_INF))/* gravitational acceleration(right and left)[coordinates]         */
#define u1_HMIGMON_VAL_FRTBK()                   (u1_g_GmntrGetVal((U1)GMNTR_FB_INF))/* gravitational acceleration(front and back)                      */
#define u1_HMIGMON_VAL_RGTLFT()                  (u1_g_GmntrGetVal((U1)GMNTR_LR_INF))/* gravitational acceleration(right and left)                      */

#define vd_HMIGMON_GMONHISWRT_U1(x)              (vd_g_Rim_WriteU1((U2)RIMID_U1_FSPO_GRAV_HIS_ONOFF, (x)))
#define u1_HMIGMON_GMONHISREAD(x)                (u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_FSPO_GRAV_HIS_ONOFF, (x)))

#define vd_HMIGMON_GMONGCDN_HIS_WRITE(id,data)   (vd_g_Rim_WriteU2((id), (data)))
#define u1_HMIGMON_GMONGCDN_HIS_READ(id, data)   (u1_g_Rim_ReadU2withStatus((id), (data)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type definition                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* PeakHold reference point information */
typedef struct{
    S2 s2_x;                                                            /* X-coordinate                                              */
    S2 s2_y;                                                            /* Y-coordinate                                              */
    S2 s2_x_offset;                                                     /* X-coordinate correction factor                            */
    S2 s2_y_offset;                                                     /* Y-coordinate correction factor                            */
    U2 u2_point;                                                        /* correction point to the next reference point              */
}ST_PEAKINFO;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*   Gravity information in hidden settings                                   */
/*----------------------------------------------------------------------------*/
static const ST_GMONINFO st_HMIGMON_INVISIBLE_GMONINFO = {
    (S2)0, (S2)0, (U1)FALSE
};

/*----------------------------------------------------------------------------*/
/*   MAX Guard Retraction Location Lookup Table                               */
/*----------------------------------------------------------------------------*/
static const ST_GMONINFO st_HMIGMON_MAXGUARD[HMIGMON_NUM_ANGLE] = {
    {(S2)HMIGMON_R_SIN0_180,   (S2)HMIGMON_R_COS0,  (U1)TRUE},
                                           /*   0 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN30_150,  (S2)HMIGMON_R_COS30_330,  (U1)TRUE},
                                           /*  30 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN60_120,  (S2)HMIGMON_R_COS60_300,  (U1)TRUE},
                                           /*  60 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN90,      (S2)HMIGMON_R_COS90_270,   (U1)TRUE},
                                           /*  90 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN60_120,  (S2)HMIGMON_R_COS120_240, (U1)TRUE},
                                           /* 120 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN30_150,  (S2)HMIGMON_R_COS150_210, (U1)TRUE},
                                           /* 150 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN0_180,   (S2)HMIGMON_R_COS180,     (U1)TRUE},
                                           /* 180 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN210_330, (S2)HMIGMON_R_COS150_210, (U1)TRUE},
                                           /* 210 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN240_300, (S2)HMIGMON_R_COS120_240, (U1)TRUE},
                                           /* 240 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN270,     (S2)HMIGMON_R_COS90_270,   (U1)TRUE},
                                           /* 270 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN240_300, (S2)HMIGMON_R_COS60_300,  (U1)TRUE},
                                           /* 300 degrees point on the circumference                    */
    {(S2)HMIGMON_R_SIN210_330, (S2)HMIGMON_R_COS30_330,  (U1)TRUE}
                                           /* 330 degrees point on the circumference                    */
};
/*----------------------------------------------------------------------------*/
/*   Tangent Value Conversion Table                                           */
/*----------------------------------------------------------------------------*/
static const U2 u2_HMIGMON_TANGENT_TBL[HMIGMON_TANSEAECH_NUM] = {       /* 30 degrees increment                                      */
/* 1/100 */
    (U2)27U,                                                            /*   0-15 degrees                                            */
    (U2)100U,                                                           /*  15-45 degrees                                            */
    (U2)373U                                                            /*  45-75 degrees                                            */
                                                                        /*  If the table is not applicable 75-90 degrees             */
};

/*----------------------------------------------------------------------------*/
/* Current direction of gravity movement                                      */
/*----------------------------------------------------------------------------*/
static const U1 u1_HMIGMON_MOVEGET[HMIGMON_MOVE_NUM][HMIGMON_MOVE_NUM] = {
    {
        (U1)HMIGMON_MOVE_1ST,                                           /* Right Front                                               */
        (U1)HMIGMON_MOVE_2ND                                            /* Left Front                                                */
    },
    {
        (U1)HMIGMON_MOVE_4TH,                                           /* Right Back                                                */
        (U1)HMIGMON_MOVE_3RD                                            /* Left Back                                                 */
    }
};

/*----------------------------------------------------------------------------*/
/* RIMID of PeakHold reference                                                */
/*----------------------------------------------------------------------------*/
static const U2 u2_HMIGMON_MAXHIST_RIM[HMIGMON_NUM_ANGLE][HMIGMON_GCDN_NUM] = {
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST1_POS_Y,                         /* Max hist1 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST1_POS_X                          /* Max hist1 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST2_POS_Y,                         /* Max hist2 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST2_POS_X                          /* Max hist2 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST3_POS_Y,                         /* Max hist3 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST3_POS_X                          /* Max hist3 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST4_POS_Y,                         /* Max hist4 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST4_POS_X                          /* Max hist4 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST5_POS_Y,                         /* Max hist5 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST5_POS_X                          /* Max hist5 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST6_POS_Y,                         /* Max hist6 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST6_POS_X                          /* Max hist6 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST7_POS_Y,                         /* Max hist7 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST7_POS_X                          /* Max hist7 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST8_POS_Y,                         /* Max hist8 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST8_POS_X                          /* Max hist8 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST9_POS_Y,                         /* Max hist9 y Rim id                                        */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST9_POS_X                          /* Max hist9 x Rim id                                        */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST10_POS_Y,                        /* Max hist10 y Rim id                                       */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST10_POS_X                         /* Max hist10 x Rim id                                       */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST11_POS_Y,                        /* Max hist11 y Rim id                                       */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST11_POS_X                         /* Max hist11 x Rim id                                       */
    },
    {
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST12_POS_Y,                        /* Max hist12 y Rim id                                       */
        (U2)RIMID_U2_FSPO_GMONI_MAXHIST12_POS_X                         /* Max hist12 x Rim id                                       */
    }
};

#endif      /* HMIGMON_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  hmigmon.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
