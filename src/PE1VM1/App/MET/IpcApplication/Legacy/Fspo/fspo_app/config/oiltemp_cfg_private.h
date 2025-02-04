/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oil temperature                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
#ifndef OILTMP_PRM
#define OILTMP_PRM

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILTMP_CFG_H_MAJOR                       (1)
#define OILTMP_CFG_H_MINOR                       (0)
#define OILTMP_CFG_H_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "lerp_u2.h"

#include "fspomgr.h"
#include "fsposnsr.h"

#include "oiltemp.h"
#include "locale.h"
#include "vardef.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILTMP_BTHOE_AVENUM                      (4U)
#define OILTMP_BTHOE_TEMPCSIG_MAX                (320U)
#define OILTMP_BTHOE_LSB                         (100)
#define OILTMP_TMP_ERR                           (3600U / FSPOSNSR_TASK_CYCLE)

#define OILTMP_TMPC_LSBMULU                      (125)
#define OILTMP_TMPC_LSBDIV                       (4)
#define OILTMP_TMPC_OFST                         (-8000)
#define OILTMP_COM_OFST                          (80)

#define OILTMP_CHGF_DAT9                         (9)
#define OILTMP_CHGF_DAT5                         (5)
#define OILTMP_CHGF_DAT32                        (64 * OILTMP_BTHOE_LSB)

#define OILTMP_OVERHEAT_OFF                      (0U)
#define OILTMP_OVERHEAT_ON                       (1U)
#define OILTMP_OVERHEAT_TMP                      (140U)

#define OILTMP_UNIT_MSK                          (0x01U)
#define OILTMP_1BIT_SFT                          (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_OILTMP_TEMP_UNIT()                    (u1_g_Unit((U1)UNIT_IDX_AMBTMP))
#define u2_OILTMP_GET_SIGSTS()                   (u2_g_FsposnsrGetSigSts())

#define OILTMP_IGON_EVT                          (FSPOMGR_IGON_EVT)
#define OILTMP_TEMPF                             (0U)
#define OILTMP_TEMPC                             (1U)
#define OILTMP_DEF                               (OILTMP_TEMPC)
#define OILTMP_TEMP_JDG                          (1U)                               /* Get unit info:1  Fahrenheit */

#define OILTMP_ENG1G17FAIL                       (FSPOSNSR_SET_ENG1G17FAIL)
#define OILTMP_FAILCHK                           (OILTMP_ENG1G17FAIL)
#define OILTMP_ENG1G17RCVD                       (FSPOSNSR_SET_ENG1G17RCVD)

#define OILTMP_UNIT_OTHER_TMPF                   (0x00U)
#define OILTMP_UNIT_OTHER_TMPC                   (0x01U)
#define OILTMP_UNIT_DEF                          (OILTMP_UNIT_OTHER_TMPC)

#define u2_OILTMP_CMAP_OVERHEAT_HYS(ovht)        (((U2)(ovht) * (U2)2U) + (U2)80U)
                                                                        /* (ovht * 2) + (40 * 2)                                     */
#define u2_OILTMP_FMAP_OVERHEAT_HYS(ovht)        ((((U2)(ovht) * (U2)18U) / (U2)5U) + (U2)144U)
                                                                        /* (((ovht * 2) * 9) / 5) + (32 * 2)) + (40 * 2)             */
#define u2_OILTMP_CNV_TMP(tmp)                   ((U2)(tmp) * (U2)2U)   /* (((tmp - 40) * 2) + 80)                                    */
#define u2_OILTMP_CALIB_OLTMAXC                  (u2_CALIB_MCUID0625_OLTMAXC)
#define u2_OILTMP_CALIB_OLTMINC                  (u2_CALIB_MCUID0626_OLTMINC)
#define u2_OILTMP_CALIB_OLTMAXF                  (u2_CALIB_MCUID0627_OLTMAXF)
#define u2_OILTMP_CALIB_OLTMINF                  (u2_CALIB_MCUID0628_OLTMINF)
#define u1_OILTMP_HYSTERESIS                     (u1_CALIB_MCUID0629_HYS)

#define OILTMP_TMPC_MAX_DEF                      (CALIB_MCUID0625_DEF)
#define OILTMP_TMPC_MIN_DEF                      (CALIB_MCUID0626_DEF)
#define OILTMP_TMPF_MAX_DEF                      (CALIB_MCUID0627_DEF)
#define OILTMP_TMPF_MIN_DEF                      (CALIB_MCUID0628_DEF)

#define OILTMP_CALIB_OLTMAXC_MAX                 (CALIB_MCUID0625_MAX)
#define OILTMP_CALIB_OLTMINC_MAX                 (CALIB_MCUID0626_MAX)
#define OILTMP_CALIB_OLTMINC_MIN                 (CALIB_MCUID0626_MIN)
#define OILTMP_CALIB_OLTMAXF_MAX                 (CALIB_MCUID0627_MAX)
#define OILTMP_CALIB_OLTMINF_MAX                 (CALIB_MCUID0628_MAX)
#define OILTMP_CALIB_OLTMINF_MIN                 (CALIB_MCUID0628_MIN)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILTMP_UNIT_TYP_MAX                (2U)
#define OILTMP_UNIT_TYP_FMAP               (0U)
#define OILTMP_UNIT_TYP_CMAP               (1U)

typedef struct{
    U2  u2_oh_off;
    U2  u2_oh_on;
}ST_OILTMP_OVERHEAT_HYS;

#endif      /* OILTMP_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  oiltemp.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
