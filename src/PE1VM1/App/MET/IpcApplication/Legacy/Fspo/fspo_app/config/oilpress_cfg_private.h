/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oil pressure                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
#ifndef OILPRSS_CFG_H
#define OILPRSS_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILPRSS_CFG_H_MAJOR                      (1)
#define OILPRSS_CFG_H_MINOR                      (0)
#define OILPRSS_CFG_H_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "fspomgr.h"
#include "fsposnsr.h"
#include "fspo_cmn.h"

#include "oilpress.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILPRSS_BPOM_AVENUM                      (4U)
#define OILPRSS_BPOMSIG_MAX                      (1280U)

#define OILPRSS_LSB_MULU                         (625U)     
#define OILPRSS_PSI_MULU                         (1813U)
#define OILPRSS_LSB_DIV                          (4000U)
#define OILPRSS_PSI_DIV                          (8000U)

#define OILPRSS_WRNOFF                           (0U)
#define OILPRSS_WRNON                            (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_OILPRSS_PRSSUNIT()                    (u1_g_FspocmnGetPrssUnit())

#define OILPRSS_IGON_EVT                         (FSPOMGR_IGON_EVT)
#define OILPRSS_OILWRN_EVT                       (FSPOMGR_OILPRSWRN_EVT)

#define OILPRSS_UNIT_PSI                         (FSPOCMN_UNIT_PSI)
#define OILPRSS_UNIT_BAR                         (FSPOCMN_UNIT_BAR)

#define OILPRSS_ENG1G17FAIL                      (FSPOSNSR_SET_ENG1G17FAIL)
#define OILPRSS_FAILCHK                          (OILPRSS_ENG1G17FAIL)
#define OILPRSS_ENG1G17RCVD                      (FSPOSNSR_SET_ENG1G17RCVD)

#define u4_OILPRESS_CVT(press)                   ((U4)(press) * (U4)10U)
#define u1_OILPRSS_CALIB_KPA_MAX                 (u1_CALIB_MCUID0653_KPAOLPMAX)
#define u1_OILPRSS_CALIB_KPA_MIN                 (u1_CALIB_MCUID0654_KPAOLPMIN)
#define u1_OILPRSS_CALIB_BAR_MAX                 (u1_CALIB_MCUID0655_BAROLPMAX)
#define u1_OILPRSS_CALIB_BAR_MIN                 (u1_CALIB_MCUID0656_BAROLPMIN)
#define u1_OILPRSS_CALIB_PSI_MAX                 (u1_CALIB_MCUID0657_PSIOLPMAX)
#define u1_OILPRSS_CALIB_PSI_MIN                 (u1_CALIB_MCUID0658_PSIOLPMIN)

#define OILPRSS_KPA_MAX_DEF                      (CALIB_MCUID0653_DEF)
#define OILPRSS_KPA_MIN_DEF                      (CALIB_MCUID0654_DEF)
#define OILPRSS_BAR_MAX_DEF                      (CALIB_MCUID0655_DEF)
#define OILPRSS_BAR_MIN_DEF                      (CALIB_MCUID0656_DEF)
#define OILPRSS_PSI_MAX_DEF                      (CALIB_MCUID0657_DEF)
#define OILPRSS_PSI_MIN_DEF                      (CALIB_MCUID0658_DEF)

#define OILPRSS_KPAMAX_MAX                       (CALIB_MCUID0653_MAX)
#define OILPRSS_KPAMIN_MAX                       (CALIB_MCUID0654_MAX)
#define OILPRSS_BARMAX_MAX                       (CALIB_MCUID0655_MAX)
#define OILPRSS_BARMIN_MAX                       (CALIB_MCUID0656_MAX)
#define OILPRSS_PSIMAX_MAX                       (CALIB_MCUID0657_MAX)
#define OILPRSS_PSIMIN_MAX                       (CALIB_MCUID0658_MAX)

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


#endif      /* OILPRSS_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  oilprss.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
