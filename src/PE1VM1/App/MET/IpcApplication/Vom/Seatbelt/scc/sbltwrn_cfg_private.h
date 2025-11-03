/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SBLTWRN_CFG_PRIVATE_H
#define SBLTWRN_CFG_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_CFG_PRIVATE_H_MAJOR             (2)
#define SBLTWRN_CFG_PRIVATE_H_MINOR             (2)
#define SBLTWRN_CFG_PRIVATE_H_PATCH             (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "sbltwrn.h"
#include "sblt_vclsts.h"
#include "sblt_seat.h"
#include "veh_opemd.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_STSBIT_VALID                    (0x00U)
#define SBLTWRN_STSBIT_UNKNOWN                  (0x01U)     /* Unknown                 */
#define SBLTWRN_STSBIT_INVALID                  (0x02U)     /* Invalid                 */

#define SBLTWRN_NUM_MSG                         (7U)    /* A number of frames           */
#define SBLTWRN_MSG_BDB1S01                     (0U)    /* A frame state idx of BDB1S01 */
#define SBLTWRN_MSG_ECT1G01                     (1U)    /* A frame state idx of ECT1G01 */
#define SBLTWRN_MSG_ABG1S01                     (2U)    /* A frame state idx of ABG1S01 */
#define SBLTWRN_MSG_VSC1G13                     (3U)    /* A frame state idx of VSC1G13 */
#define SBLTWRN_MSG_PDC1G02                     (4U)    /* A frame state idx of PDC1G02 */
#define SBLTWRN_MSG_ZN11S19                     (5U)    /* A frame state idx of ZN11S19 */
#define SBLTWRN_MSG_ZN11S26                     (6U)    /* A frame state idx of ZN11S26 */

#define SBLTWRN_VALID                           (0x00U)
#define SBLTWRN_INVALID                         (0x01U)
#define SBLTWRN_UNKNOWN                         (0x02U)

#define SBLTWRN_TICK                            (50U)

#define SBLTWRN_MSGCOND_BATT                    (0U)
#define SBLTWRN_MSGCOND_IGON                    (1U)

#define SBLTWRN_SEAT_NOTUSED                    (0xFFU)

#define SBLTWRN_NUM_SEAT_FUNC                   (7U)    /* A number of seat-status func         */
#define SBLTWRN_SEAT_DS                         (0U)    /* Driver seat                          */
#define SBLTWRN_SEAT_PS                         (1U)    /* Passenger seat                       */
#define SBLTWRN_SEAT_FC                         (2U)    /* Front Center seat                    */
#define SBLTWRN_SEAT_RS_RXBKLPDC                (3U)    /* Rear seat(1st) (w/o  seatsnsr)       */
#define SBLTWRN_SEAT_RS_RXBKLPDC_RXOSW          (4U)    /* Rear seat(1st) (with seatsnsr)       */
#define SBLTWRN_SEAT_RS_XRXBKL                  (5U)    /* Rear seat(2nd-) (w/o  seatsnsr)      */
#define SBLTWRN_SEAT_RS_XRXBKL_RXXOSW           (6U)    /* Rear seat(2nd-) (with seatsnsr)      */

#define SBLTWRN_NUM_DEST                        (9U)    /* A number of destination */
#define SBLTWRN_DEST_US_SB                      (0U)    /* DEST: USA/GCC,       Sound: Subaru-Sound */
#define SBLTWRN_DEST_EU_SB                      (1U)    /* DEST: EU/AUS/JPN,    Sound: Subaru-Sound */
#define SBLTWRN_DEST_CN_SB                      (2U)    /* DEST: CHINA,         Sound: Subaru-Sound */
#define SBLTWRN_DEST_US_LS                      (3U)    /* DEST: USA/GCC,       Sound: Lexus-Sound */
#define SBLTWRN_DEST_EU_LS                      (4U)    /* DEST: EU/AUS/JPN,    Sound: Lexus-Sound */
#define SBLTWRN_DEST_CN_LS                      (5U)    /* DEST: CHINA,         Sound: Lexus-Sound */
#define SBLTWRN_DEST_US_TS                      (6U)    /* DEST: USA/GCC,       Sound: Toyota-Sound */
#define SBLTWRN_DEST_EU_TS                      (7U)    /* DEST: EU/AUS/JPN,    Sound: Toyota-Sound */
#define SBLTWRN_DEST_CN_TS                      (8U)    /* DEST: CHINA,         Sound: Toyota-Sound */

#define SBLTWRN_IGTIM_OVER500JDG                (500U/SBLTWRN_TICK)

#define SBLTWRN_NUM_SPD                         (5U)
#define SBLTWRN_SPD_RSM                         (0U)
#define SBLTWRN_SPD_RUN                         (1U)
#define SBLTWRN_SPD_STP                         (2U)
#define SBLTWRN_SPD_LOW                         (3U)
#define SBLTWRN_SPD_HIGH                        (4U)

#define SBLTWRN_BKLSTS_BCKL                     (0x00U)
#define SBLTWRN_BKLSTS_UNBCKLFLG                (0x01U)
#define SBLTWRN_BKLSTS_UNBCKL                   (0x02U)
#define SBLTWRN_BKLSTS_UNBCKLEDG                (0x04U)
#define SBLTWRN_BKLSTS_COMFAIL                  (0x08U)
#define SBLTWRN_BKLSTS_FIXUNBKL                 (0x10U)
#define SBLTWRN_BKLSTS_BCKLEDG                  (0x20U)
#define SBLTWRN_BKLSTS_FAILRSTEDG               (0x40U)         /* Turned from COMFAIL to NORMAL edge*/

#define SBLTWRN_VCLSTS_PARK                     (0x00000001U)
#define SBLTWRN_VCLSTS_SHIFT_R                  (0x00000002U)
#define SBLTWRN_VCLSTS_D_DR_OP                  (0x00000004U)
#define SBLTWRN_VCLSTS_P_DR_OP                  (0x00000008U)
#define SBLTWRN_VCLSTS_R_DR_OP                  (0x00000010U)
#define SBLTWRN_VCLSTS_B_DR_OP                  (0x00000020U)
#define SBLTWRN_VCLSTS_RB_DR_OP                 (0x00000040U)
#define SBLTWRN_VCLSTS_DP_DR_OP                 (0x00000080U)
#define SBLTWRN_VCLSTS_DPB_DR_OP                (0x00000100U)
#define SBLTWRN_VCLSTS_PRB_DR_OP                (0x00000200U)
#define SBLTWRN_VCLSTS_SPD_RSM                  (0x00000400U)
#define SBLTWRN_VCLSTS_SPD_RUN                  (0x00000800U)
#define SBLTWRN_VCLSTS_SPD_STP                  (0x00001000U)
#define SBLTWRN_VCLSTS_SPD_LOW                  (0x00002000U)
#define SBLTWRN_VCLSTS_SPD_HIGH                 (0x00004000U)

#define SBLTWRN_VCLSTS_IG_ONSTS                 (0x00008000U)
#define SBLTWRN_VCLSTS_PARKEDG                  (0x00010000U)
#define SBLTWRN_VCLSTS_UNPARKEDG                (0x00020000U)
#define SBLTWRN_VCLSTS_IGTIM_OVER500            (0x00040000U)   /* 500ms elapsed after IG-ON */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_SEATBELT_CALIB_RR_SEATSW             (u1_CALIB_MCUID0224_RR_SEATSW)
#define u1_SEATBELT_CALIB_RC_SEATSW             (u1_CALIB_MCUID0225_RC_SEATSW)
#define u1_SEATBELT_CALIB_RL_SEATSW             (u1_CALIB_MCUID0226_RL_SEATSW)
#define u1_SEATBELT_CALIB_RR2_SEATSW            (u1_CALIB_MCUID0227_RR2_SEATSW)
#define u1_SEATBELT_CALIB_RC2_SEATSW            (u1_CALIB_MCUID0228_RC2_SEATSW)
#define u1_SEATBELT_CALIB_RL2_SEATSW            (u1_CALIB_MCUID0229_RL2_SEATSW)
#define u1_SEATBELT_CALIB_RR3_SEATSW            (u1_CALIB_MCUID0230_RR3_SEATSW)
#define u1_SEATBELT_CALIB_RC3_SEATSW            (u1_CALIB_MCUID0231_RC3_SEATSW)
#define u1_SEATBELT_CALIB_RL3_SEATSW            (u1_CALIB_MCUID0232_RL3_SEATSW)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1          u1_msgcond;
    U2          u2_msgid;
} ST_SBLTWRN_MSGCFG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1              u1_g_SbltwrnDestCfg(void);
U1              u1_g_SbltwrnCanMsgstsCfg(const U2 u2_a_MSGSTS);
/* U1           u1_g_SbltwrnIgnOn(void);                                                                                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern  const   ST_SBLTWRN_MSGCFG               st_gp_SBLTWRN_MSGCOND_CFG[];

#endif /* SBLTWRN_CFG_PRIVATE_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  sbltwrn_cfg.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
