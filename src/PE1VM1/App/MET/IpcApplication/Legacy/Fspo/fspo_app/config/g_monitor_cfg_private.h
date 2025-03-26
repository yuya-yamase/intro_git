/* 3.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  F-Spo G Monitor                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
#ifndef GMNTR_CFG_H
#define GMNTR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GMNTR_CFG_H_MAJOR                        (3)
#define GMNTR_CFG_H_MINOR                        (0)
#define GMNTR_CFG_H_PATCH                        (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

#include "calibration.h"
#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

#include "fspomgr.h"
#include "fsposnsr.h"
#include "vehspd_kmph.h"
#include "vardef.h"

#include "g_monitor.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* For communication data between CPUs */
#define GMNTR_FRNT                               (0U)                            /* direction of gravity acceleration :front         */
#define GMNTR_BACK                               (1U)                            /* direction of gravity acceleration :back          */
#define GMNTR_LEFT                               (1U)                            /* direction of gravity acceleration :left          */
#define GMNTR_RGHT                               (0U)                            /* direction of gravity acceleration :right         */

#define GMNTR_FB_DRC_FAIL                        (GMNTR_FRNT)                    /* direction of gravity acceleration :fornt and back :abnormal case */
#define GMNTR_LR_DRC_FAIL                        (GMNTR_RGHT)                    /* direction of gravity acceleration :left and right :abnormal case */
#define GMNTR_VAL_FAIL                           (0x00U)                         /* gravitational acceleration :fail value           */
#define GMNTR_POS_FAIL                           (0x0000U)                       /* gravity acceleration coordinate :fail value      */

#define GMNTR_G_VSBL_VALID                       (1U)                            /* gravity acceleration display status valid        */
#define GMNTR_G_VSBL_INIT_FAIL                   (0U)                            /* gravity acceleration display status invalid      */
#define GMNTR_GBALL_MULU                         (10U)                            /* LSB:0.01 for multiplication                      */
#define GMNTR_POS_MAX                            (u1_CALIB_MCUID0219_G_GAUGE_MAX * (U1)GMNTR_GBALL_MULU)
                                                                                 /* coordinates :Max value                           */
#define GMNTR_BALLVAL_MAX                        (u1_CALIB_MCUID0221_G_DISP_MAX) /* Numeric     :Max value                           */

#define GMNTR_ANGLDRC_FAIL                       (GMNTR_RGHT)                    /* steering angle direction :abnormal case          */
#define GMNTR_ANGL_FAIL                          (0x00U)                         /* steering angle :fail value                       */
#define GMNTR_ANGL_VSBL_VALID                    (0U)                            /* steerung angle display status valid              */
#define GMNTR_ANGL_VSBL_LIGHT                    (1U)                            /* steerung angle display status MAX Over           */
#define GMNTR_ANGL_VSBL_INIT_FAIL                (2U)                            /* steerung angle display status invalid            */
#define GMNTR_ANGL_MAX                           (u1_CALIB_MCUID0217_STR_ANG)    /* steering angle :tip lighting value               */

#define GMNTR_BRKPRS_FAIL                        (0x00U)                         /* brake pressure :fail value                       */
#define GMNTR_BRKPRS_VSBL_VALID                  (0U)                            /* brake pressure display status valid              */
#define GMNTR_BRKPRS_VSBL_INIT_FAIL              (1U)                            /* brake pressure display status invalid            */
#define GMNTR_BRKPRS_MAX                         (u1_CALIB_MCUID0218_ACCELERATOR) /* Max value                                       */

#define GMNTR_ACCEL_FAIL                         (0x00U)                         /* accelerator opening :fail value                  */
#define GMNTR_ACCEL_VSBL_VALID                   (0U)                            /* accelerator opening display status valid         */
#define GMNTR_ACCEL_VSBL_INIT_FAIL               (1U)                            /* accelerator opening display status invalid       */
#define GMNTR_ACCEL_MAX                          (u1_CALIB_MCUID0218_ACCELERATOR) /* Max value                                       */

/* Arithmetic Value for G-Ball */
#define GMNTR_GRVTY_AVENUM                       (8U)                            /* moving average number                            */

#define GMNTR_POS_CENTER                         (0x0000)                        /* G ball center value                              */

#define GMNTR_GRVTY_THRESH                       (33)                            /* gravitational threshold [LSB:0.001]              */

#define GMNTR_BALLVAL_LSB                        (100U)                          /* coefficient for calculation [LSB:0.1]            */
#define GMNTR_POS_LSB                            (10U)                           /* coefficient for calculation [pixel]              */
#define GMNTR_VAL_RNDOFSET                       (GMNTR_BALLVAL_LSB / 2U)        /* rounding off                                     */
#define GMNTR_RNDOFSET                           (5U)                            /* rounding off(Angle,BrakePress,AccelOpen)         */

#define GMNTR_SPSTOP                             (175U)                          /* Stop decision threshold [LSB:0.01[km/h]          */
#define GMNTR_PKHLD_THRESH                       (5U)

/* For steering angle calculation */

#define GMNTR_ANGL_LSB                           (15)                            /* coefficient for the calculated steering angle value [LSB:0.1] */
#define GMNTR_ANGL_MAXVAL                        (1800U)                         /* Max Value [LSB:0.1]                              */
#define GMNTR_ANGL_COEFF                         (10U)                           /* Convert [LSB:0.1]　to [LSB:1]                     */
#define GMNTR_ANGL_NUM_A                         (2)                             /* Weighted average constant A                      */
#define GMNTR_ANGL_NUM_B                         (10)                            /* Weighted average constant B                      */
#define GMNTR_ANGL_NUM_C                         (GMNTR_ANGL_NUM_A + GMNTR_ANGL_NUM_B)/* Weighted average constant C                 */

/* For brake oil pressure calculation */
#define GMNTR_BRKPRS_BRK_ACCL_VALID              (1U)                            /* Valid value of brake pedal acceleration flag     */
#define GMNTR_BRKPRS_BRK_ACCL_LOW_LMT            (-90)                           /* Lower limit of brake pedal acceleration          */
#define GMNTR_BRKPRS_BRK_ACCL_MAX                (1000U)                         /* Maximum value of brake pedal acceleration        */
#define GMNTR_BRKPRS_ROUND_VAL                   (500U)                          /* Number for rounding                              */

/* For calculation of accelerator opening */
#define GMNTR_ACCEL_LSB                          (5U)                            /* Factor for the operation ACCEL opening value [LSB:0.1] */
#define GMNTR_ACCEL_MAXVAL                       (1000U)                         /* Max Value[LSB:0.1 %]                             */
#define GMNTR_ACCEL_COEFF                        (100U)                          /* coefficient for the calculated accel opening     */

/* Time Determination */
#define GMNTR_FAILTIM_MS                         (3600U)                         /* abnormal condition determination time[LSB:ms]    */
#define GMNTR_UPDTTIM_MS                         (100U)                          /* display update timing[LSB：ms]                   */
#define GMNTR_GBALL_FAILTIM                      (GMNTR_FAILTIM_MS / FSPOSNSR_TASK_CYCLE)   /* G Ball fail time                      */
#define GMNTR_ANGL_FAILTIM                       (GMNTR_FAILTIM_MS / FSPOMGR_TASK_CYCLE)    /* Angle fail time                       */
#define GMNTR_BRKPRS_FAILTIM                     (GMNTR_FAILTIM_MS / FSPOSNSR_TASK_CYCLE)   /* Brake pressure fail time              */
#define GMNTR_UPDTTIM                            (GMNTR_UPDTTIM_MS / FSPOMGR_TASK_CYCLE)    /* Update fail time                      */
#define GMNTR_PKHLD_TIM_MS                       (2000U)
#define GMNTR_PKHLD_TIM                          (GMNTR_PKHLD_TIM_MS / GMNTR_UPDTTIM_MS)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV BSW provisionally */
#define u1_GMNTR_RXMSG_STR1S01STS()              ((U1)Com_GetIPDUStatus(MSG_STR1S01_RXCH0))
#else
#define u1_GMNTR_RXMSG_STR1S01STS()              ((U1)COM_NO_RX)
#endif
#define vd_GMNTR_RXMSG_STS1(sgnl)                ((void)Com_ReceiveSignal(ComConf_ComSignal_STS1, (sgnl)))
#define vd_GMNTR_RXMSG_SSA(sgnl)                 ((void)Com_ReceiveSignal(ComConf_ComSignal_SSA,  (sgnl)))
#define u1_GMNTR_RXMSG_EPS1S11STS()              ((U1)Com_GetIPDUStatus(MSG_EPS1S11_RXCH0))
#define vd_GMNTR_RXMSG_EPSTS1(sgnl)              ((void)Com_ReceiveSignal(ComConf_ComSignal_EPSTS1, (sgnl)))
#define vd_GMNTR_RXMSG_EPSSA(sgnl)               ((void)Com_ReceiveSignal(ComConf_ComSignal_EPSSA,  (sgnl)))

#define u1_GMNTR_RXMSG_ENG1G03STS()              ((U1)Com_GetIPDUStatus(MSG_ENG1G03_RXCH0))
#define vd_GMNTR_RXMSG_EACCP_D(sgnl)             ((void)Com_ReceiveSignal(ComConf_ComSignal_EACCP_D, (sgnl)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_GMNTR_IG_ISON()                       (u1_g_VehopemdIgnOn())

/* G-Ball */
#define GMNTR_IGON_EVT                           (FSPOMGR_IGON_EVT)              /* IGON event                                       */
#define GMNTR_GBALL_FAILCHK                      (FSPOSNSR_SET_VSC1G12FAIL)
                                                                                 /* G ball fail decision value                       */
#define GMNTR_GBALL_RCVDCHK                      (FSPOSNSR_SET_VSC1G12RCVD)      /* G ball receive check                             */

/* Brake pressure  */
#define GMNTR_OILPRSS_FAILCHK                    (FSPOSNSR_SET_VSC1G30FAIL)      /* Brake pressure fail decision value               */
#define GMNTR_OILPRSS_RCVDCHK                    (FSPOSNSR_SET_VSC1G30RCVD)      /* Brake pressure receive check                     */

#define GMNTR_COM_TIMEOUT                        (COM_TIMEOUT)                   /* communication disruption                         */
#define GMNTR_COM_NO_RX                          (COM_NO_RX)                     /* Not Received                                     */

/* SensorStatusBit */
#define GMNTR_SNSRSTSBIT_ANGLE_90                (0x00U)
#define GMNTR_SNSRSTSBIT_ANGLE_45                (0x02U)

#define GMNTR_SNSRSTSBIT_DRCT_FRONT              (0x00U)
#define GMNTR_SNSRSTSBIT_DRCT_BACK               (0x01U)

/* Table Array Num */
#define GMNTR_SNSRTYP_NUM                        (4U)
#define GMNTR_SIGNNUM                            (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_GMNTR_GET_SIGSTS()                    (u2_g_FsposnsrGetSigSts())      /* Signal Status                                    */
#define u1_GMNTR_EPSSA_SUP()                     (u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_EPSSA))      /* EPSSA Option Result         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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


/* Direction for Front/Back */
static const U1 u1_sp_GMNTR_SNSRTYP_FB_TBL[GMNTR_SNSRTYP_NUM][GMNTR_SIGNNUM] = {
    {   (U1)GMNTR_FRNT, (U1)GMNTR_BACK  },      /* Angle : 90°/ Direction : Front */
    {   (U1)GMNTR_BACK, (U1)GMNTR_FRNT  },      /* Angle : 90°/ Direction : Back  */
    {   (U1)GMNTR_FRNT, (U1)GMNTR_BACK  },      /* Angle : 45°/ Direction : Front */
    {   (U1)GMNTR_BACK, (U1)GMNTR_FRNT  }       /* Angle : 45°/ Direction : Back  */
};

/* Direction for Left/Right */
static const U1 u1_sp_GMNTR_SNSRTYP_LR_TBL[GMNTR_SNSRTYP_NUM][GMNTR_SIGNNUM] = {
    {   (U1)GMNTR_LEFT, (U1)GMNTR_RGHT  },      /* Angle : 90°/ Direction : Front */
    {   (U1)GMNTR_RGHT, (U1)GMNTR_LEFT  },      /* Angle : 90°/ Direction : Back  */
    {   (U1)GMNTR_LEFT, (U1)GMNTR_RGHT  },      /* Angle : 45°/ Direction : Front */
    {   (U1)GMNTR_RGHT, (U1)GMNTR_LEFT  }       /* Angle : 45°/ Direction : Back  */
};

#endif      /* GMNTR_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  g_monitor.c                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
