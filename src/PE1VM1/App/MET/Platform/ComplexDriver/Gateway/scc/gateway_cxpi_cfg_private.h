/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota CXPI Gateway                                                                                                              */
/*===================================================================================================================================*/

#ifndef GATEWAY_CXPI_CFG_PRIVATE_H
#define GATEWAY_CXPI_CFG_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GATEWAY_CXPI_CFG_PRIVATE_H_MAJOR                    (1)
#define GATEWAY_CXPI_CFG_PRIVATE_H_MINOR                    (0)
#define GATEWAY_CXPI_CFG_PRIVATE_H_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif
#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

#ifdef CXPICDD_H
#include "CxpiCdd_App.h"
#endif /* #ifdef CXPICDD_H */
#include "gateway_cxpi_cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GWCXCFG_PWRSTS_B_BITPOS                                (0x01U)                        /*  Power Status B                 */
#define GWCXCFG_PWRSTS_BA_BITPOS                               (0x02U)                        /*  Power Status BA                */
#define GWCXCFG_PWRSTS_ACC_BITPOS                              (0x04U)                        /*  Power Status ACC               */
#define GWCXCFG_PWRSTS_IGR_BITPOS                              (0x08U)                        /*  Power Status IGR               */
#define GWCXCFG_PWRSTS_IGP_BITPOS                              (0x10U)                        /*  Power Status IGP               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GWCXCFG_WRITE_INIT                        (0U)        /* Write Init    */
#define GWCXCFG_WRITE_EVENT_TX                    (1U)        /* Write Event   */
#define GWCXCFG_WRITE_ROUTINE                     (2U)        /* Write Routine */

#define GWCXCFG_CYC_INIT                          (0U)        /* TimeOut Counter Init */
#define GWCXCFG_CYC_CNT                           (1000U/GATEWAY_CXPICFG_APP_TASK) /* All GWCXCFG frames have same transmit cycles of 1sec */

#define GWCXCFG_NOTUPDATED                        (0U)        /* Send Signal Not Update */
#define GWCXCFG_UPDATED                           (1U)        /* Send Signal Update     */

#define GWCXCFG_EXIST_COUNT                       (2U)        /* When MET receives 3 times of signals, function is available */

/** PNC check **/
#define OXCAN_SYS_PNC_ALL                        (OXCAN_SYS_PNC_16 | OXCAN_SYS_PNC_40 | OXCAN_SYS_PNC_43 | OXCAN_SYS_PNC_44)

/** CXMET1S02 **/
#define GWCXCFG_CXPIJDG_UNDET                     (0U)        /* also used by MET1S41, MET1S43, MET1S44, CMB1S05, and CMB1S06 */
#define GWCXCFG_CXPIJDG_EXIST                     (1U)        /* also used by MET1S41, MET1S43, MET1S44, CMB1S05, and CMB1S06 */
#define GWCXCFG_CXPIJDG_NOTEXIST                  (2U)        /* also used by MET1S41, MET1S43, MET1S44, CMB1S05, and CMB1S06 */
#define GWCXCFG_CXPIJDG_UNDEF                     (3U)        /* also used by MET1S41, MET1S43, MET1S44, CMB1S05, and CMB1S06 */

/** CXMET1S03 **/
#define GWCXCFG_STGVIB_MOTOR_OFF_UNUSED_0         (0U)        /* Not Used               */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p1s             (1U)        /* Motor OFF Time is 0.1s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p2s             (2U)        /* Motor OFF Time is 0.2s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p3s             (3U)        /* Motor OFF Time is 0.3s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p4s             (4U)        /* Motor OFF Time is 0.4s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p5s             (5U)        /* Motor OFF Time is 0.5s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p6s             (6U)        /* Motor OFF Time is 0.6s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p7s             (7U)        /* Motor OFF Time is 0.7s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p8s             (8U)        /* Motor OFF Time is 0.8s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p9s             (9U)        /* Motor OFF Time is 0.9s */
#define GWCXCFG_STGVIB_MOTOR_OFF_1p0s             (10U)       /* Motor OFF Time is 1.0s */
#define GWCXCFG_STGVIB_MOTOR_OFF_1p1s             (11U)       /* Motor OFF Time is 1.1s */
#define GWCXCFG_STGVIB_MOTOR_OFF_1p2s             (12U)       /* Motor OFF Time is 1.2s */
#define GWCXCFG_STGVIB_MOTOR_OFF_1p3s             (13U)       /* Motor OFF Time is 1.3s */
#define GWCXCFG_STGVIB_MOTOR_OFF_0p0s             (14U)       /* Motor OFF Time is 0.0s */
#define GWCXCFG_STGVIB_MOTOR_OFF_UNUSED_15        (15U)       /* Not Used               */

#define GWCXCFG_STGVIB_VIBSTR_UNUSED_0            (0U)        /* Not Used                   */
#define GWCXCFG_STGVIB_VIBSTR_LVL1                (1U)        /* Vibration strength level1  */
#define GWCXCFG_STGVIB_VIBSTR_LVL2                (2U)        /* Vibration strength level2  */
#define GWCXCFG_STGVIB_VIBSTR_LVL3                (3U)        /* Vibration strength level3  */
#define GWCXCFG_STGVIB_VIBSTR_LVL4                (4U)        /* Vibration strength level4  */
#define GWCXCFG_STGVIB_VIBSTR_LVL5                (5U)        /* Vibration strength level5  */
#define GWCXCFG_STGVIB_VIBSTR_LVL6                (6U)        /* Vibration strength level6  */
#define GWCXCFG_STGVIB_VIBSTR_LVL7                (7U)        /* Vibration strength level7  */
#define GWCXCFG_STGVIB_VIBSTR_LVL8                (8U)        /* Vibration strength level8  */
#define GWCXCFG_STGVIB_VIBSTR_LVL9                (9U)        /* Vibration strength level9  */
#define GWCXCFG_STGVIB_VIBSTR_LVL10               (10U)       /* Vibration strength level10 */
#define GWCXCFG_STGVIB_VIBSTR_UNUSED_11           (11U)       /* Not Used                   */
#define GWCXCFG_STGVIB_VIBSTR_UNUSED_12           (12U)       /* Not Used                   */
#define GWCXCFG_STGVIB_VIBSTR_UNUSED_13           (13U)       /* Not Used                   */
#define GWCXCFG_STGVIB_VIBSTR_UNUSED_14           (14U)       /* Not Used                   */
#define GWCXCFG_STGVIB_VIBSTR_UNUSED_15           (15U)       /* Not Used                   */

#define GWCXCFG_STGVIB_MOTOR_ON_UNUSED_0          (0U)        /* Not Used               */
#define GWCXCFG_STGVIB_MOTOR_ON_0p1s              (1U)        /* Motor OFF Time is 0.1s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p2s              (2U)        /* Motor OFF Time is 0.2s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p3s              (3U)        /* Motor OFF Time is 0.3s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p4s              (4U)        /* Motor OFF Time is 0.4s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p5s              (5U)        /* Motor OFF Time is 0.5s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p6s              (6U)        /* Motor OFF Time is 0.6s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p7s              (7U)        /* Motor OFF Time is 0.7s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p8s              (8U)        /* Motor OFF Time is 0.8s */
#define GWCXCFG_STGVIB_MOTOR_ON_0p9s              (9U)        /* Motor OFF Time is 0.9s */
#define GWCXCFG_STGVIB_MOTOR_ON_1p0s              (10U)       /* Motor OFF Time is 1.0s */
#define GWCXCFG_STGVIB_MOTOR_ON_1p1s              (11U)       /* Motor OFF Time is 1.1s */
#define GWCXCFG_STGVIB_MOTOR_ON_1p2s              (12U)       /* Motor OFF Time is 1.2s */
#define GWCXCFG_STGVIB_MOTOR_ON_1p3s              (13U)       /* Motor OFF Time is 1.3s */
#define GWCXCFG_STGVIB_MOTOR_ON_UNUSED_14         (14U)       /* Not Used               */
#define GWCXCFG_STGVIB_MOTOR_ON_UNUSED_15         (15U)       /* Not Used               */

/** CXMET1S04 **/
#define GWCXCFG_STGHTR_OFF                        (0U)        /* Steering Heter OFF */
#define GWCXCFG_STGHTR_LO                         (1U)        /* Lo                 */
#define GWCXCFG_STGHTR_HI                         (2U)        /* Hi                 */
#define GWCXCFG_STGHTR_RESERVED                   (3U)        /* Reserved           */

/** CXMET1S05 **/
#define GWCXCFG_T_LOGI_NOLOGIC                    (0U)        /* Normal             */
#define GWCXCFG_T_LOGI_HILOGIC                    (1U)        /* Hi                 */
#define GWCXCFG_T_LOGI_OFF                        (2U)        /* OFF                */
#define GWCXCFG_T_LOGI_MAX                        (GWCXCFG_T_LOGI_OFF) /* T_LOGI Max Value */
#define GWCXCFG_EL_SENS_NORMAL                    (3U)        /* Reception Level3   */

/** CXMET1S06 **/
#define GWCXCFG_ADIM_UNDET                        (0U)        /* Not Determined     */
#define GWCXCFG_HEDH_OFF                          (0U)        /* OFF                */
#define GWCXCFG_HEDL_OFF                          (0U)        /* OFF                */
#define GWCXCFG_TAIL_OFF                          (0U)        /* OFF                */
#define GWCXCFG_FFOG_OFF                          (0U)        /* OFF                */
#define GWCXCFG_RFOG_OFF                          (0U)        /* OFF                */
#define GWCXCFG_CONLT_PR_NOSEND                   (0U)        /* Not Send           */
#define GWCXCFG_CONLT_PR_OFF                      (1U)        /* OFF                */
#define GWCXCFG_CONLT_PR_ON                       (2U)        /* ON                 */
#define GWCXCFG_CONLT_PR_NOUSE                    (3U)        /* Not Used           */
#define GWCXCFG_BW_SW_PR_NOSEND                   (0U)        /* Not Send           */
#define GWCXCFG_BW_SW_PR_OFF                      (1U)        /* OFF                */
#define GWCXCFG_BW_SW_PR_ON                       (2U)        /* ON                 */
#define GWCXCFG_BW_SW_PR_NOUSE                    (3U)        /* Not Used           */
#define GWCXCFG_AUTINT_NOSEND                     (0U)        /* Not Send           */
#define GWCXCFG_AUTINT_OFF                        (1U)        /* OFF                */
#define GWCXCFG_AUTINT_ON                         (2U)        /* ON                 */
#define GWCXCFG_AUTINT_NOUSE                      (3U)        /* Not Used           */

#define GWCXCFG_CONLT_PR_MSGTBL_NUM               (2U)        /* Table Size         */
#define GWCXCFG_BW_SW_PR_MSGTBL_NUM               (2U)        /* Table Size         */
#define GWCXCFG_AUTINT_MSGTBL_NUM                 (2U)        /* Table Size         */

/** MET1S41 **/
#define GWCXCFG_STGSWSTAT_OFF                     (0U)        /* OFF */ /* also used by MET1S43 and MET1S44 */
#define GWCXCFG_STGSWSTAT_ON                      (1U)        /* ON  */
#define GWCXCFG_AUDMUTE_OFF                       (0U)        /* OFF */
#define GWCXCFG_AUDMUTE_ON                        (1U)        /* ON  */
#define GWCXCFG_VOL_LV_DEF                        (0U)        /* No Action */

/** MET1S43 **/
#define GWCXCFG_STGSWSTAT_MOT_NML                 (0U)        /* Normal        */
#define GWCXCFG_STGSWSTAT_MOT_DISCNCT             (1U)        /* Disconnect    */
#define GWCXCFG_STGSWSTAT_VIB_EXIST_UNDET         (0U)        /* Undetermined  */
#define GWCXCFG_STGSWSTAT_VIB_EXIST               (1U)        /* Functionality */
#define GWCXCFG_STGSWSTAT_VIB_NOT_EXIST           (2U)        /* No function   */
#define GWCXCFG_STGSWSTAT_VIB_EXIST_UNDEF         (3U)        /* Undefined     */
#define GWCXCFG_STGSWSTAT_GRP_EXIST_UNDET         (0U)        /* Undetermined  */
#define GWCXCFG_STGSWSTAT_GRP_EXIST               (1U)        /* Functionality */
#define GWCXCFG_STGSWSTAT_GRP_NOT_EXIST           (2U)        /* No function   */
#define GWCXCFG_STGSWSTAT_GRP_EXIST_UNDEF         (3U)        /* Undefined     */

/** MET1S45 **/
#define GWCXCFG_STGHTRPRES_NO_FUNC                (0U)        /* No function   */
#define GWCXCFG_STGHTRPRES_ONOFF                  (1U)        /* Type ON/OFF   */
#define GWCXCFG_STGHTRPRES_MULTI                  (2U)        /* Type Multi    */
#define GWCXCFG_STGHTRPRES_UNDET                  (7U)        /* Undetermined  */

#define GWCXCFG_SHIFT_1BYTE                       (8U)        /* Data Shift 1Byte */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    void        ( * fp_vd_errchk)(void);                                       /*  Error Check IF                   */
}ST_GWCX_ERRCHK;

typedef struct{
    void        ( * fp_vd_send)(const U1  u1_a_pwrsts);                        /*  Message Send IF                  */
}ST_GWCX_MSGCONF;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U1                      u1_g_GWCX_ERRCHKTASK_NUM;                 /*  Error Check Number               */
extern const U1                      u1_g_GWCX_WRTMSG_NUM;                     /*  Gateway Write Message Number     */

extern const ST_GWCX_ERRCHK          st_gp_GWCX_ERRCHKIF[GATEWAY_CXPICFG_ERRCHKTASK_NUM]; /*  Error Check IF        */
extern const ST_GWCX_MSGCONF         st_gp_GWCX_MSGIF[GATEWAY_CXPICFG_WRTMSG_NUM];        /*  Message Config        */


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variation Setup Notification API Registrations                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* GATEWAY_CXPI_PRIVATE_CFG_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History : see gateway_cxpi_cfg.c                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
