/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DENSO ICT1 Coding Style Standard Template                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIPROXY_CFG_C_MAJOR                     (1)
#define HMIPROXY_CFG_C_MINOR                     (4)
#define HMIPROXY_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"

#include "hmihud.h"
#include "hmilocale.h"
#include "hmimaint.h"
#include "hmiodo.h"
#include "hmiputxt.h"
#include "hmitt.h"
#include "hmiwchime.h"
#include "hmitripcom.h"
#include "hmiscreen.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIPROXY_CFG_C_MAJOR != HMIPROXY_H_MAJOR) || \
     (HMIPROXY_CFG_C_MINOR != HMIPROXY_H_MINOR) || \
     (HMIPROXY_CFG_C_PATCH != HMIPROXY_H_PATCH))
#error "hmiproxy_cfg.c and hmiputxt.h : source and header files are inconsistent!"
#endif

#if ((HMIPROXY_CFG_C_MAJOR != HMIPROXY_CFG_H_MAJOR) || \
     (HMIPROXY_CFG_C_MINOR != HMIPROXY_CFG_H_MINOR) || \
     (HMIPROXY_CFG_C_PATCH != HMIPROXY_CFG_H_PATCH))
#error "hmiproxy_cfg.c and hmiproxy_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void ( * const              fp_gp_vd_HMIPROXY_BON_INIT[HMIPROXY_INIT_NUM])(void) = {
     &vd_g_HmiHudInit,
     &vd_g_HmiLocaleInit,
     &vd_g_HmiMaintInit,
     &vd_g_HmiOdoInit,
     &vd_g_HmiPuTxtInit,
     &vd_g_HmiTtInit,
     &vd_g_HmiWchimeInit,
     &vd_g_HmiTripcomInit,
     &vd_g_HmiScreenInit
};

void ( * const              fp_gp_vd_HMIPROXY_RST_INIT[HMIPROXY_INIT_NUM])(void) = {
     &vd_g_HmiHudInit,
     &vd_g_HmiLocaleInit,
     &vd_g_HmiMaintInit,
     &vd_g_HmiOdoInit,
     &vd_g_HmiPuTxtInit,
     &vd_g_HmiTtInit,
     &vd_g_HmiWchimeInit,
     &vd_g_HmiTripcomInit,
     &vd_g_HmiScreenInit
};

void ( * const              fp_gp_vd_HMIPROXY_WKUP_INIT[HMIPROXY_INIT_NUM])(void) = {
     &vd_g_HmiHudInit,
     &vd_g_HmiLocaleInit,
     &vd_g_HmiMaintInit,
     &vd_g_HmiOdoInit,
     &vd_g_HmiPuTxtInit,
     &vd_g_HmiTtInit,
     &vd_g_HmiWchimeInit,
     &vd_g_HmiTripcomInit,
     &vd_g_HmiScreenInit
};

const ST_HMIPROXY     st_gp_HMIPROXY[HMIPROXY_MAINTASK_NUM] = {
     {&vd_g_HmiHudMainTask ,     (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiLocaleMainTask,   (U4)SCHDLR_TASKBIT__20MS_B  },
     {&vd_g_HmiMaintMainTask,    (U4)SCHDLR_TASKBIT__50MS_C  },
     {&vd_g_HmiOdoMainTask,      (U4)SCHDLR_TASKBIT__50MS_C  },
     {&vd_g_HmiPuTxtMainTask,    (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiTtMainTask,       (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiWchimeMainTask,   (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiTripcomMainTask,  (U4)SCHDLR_TASKBIT__50MS_E  },
     {&vd_g_HmiScreenMainTask,   (U4)SCHDLR_TASKBIT__50MS_A  },
     {vdp_PTR_NA,                (U4)SCHDLR_TASKBIT_RGLR     }   /* <- Terminator. Do Not Delete! */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/16/2017  TA       New.                                                                                               */
/*  1.1.0    03/20/2020  TH       Setting for 800B CV.                                                                               */
/*  1.2.0    10/07/2020  TH       Setting for 800B CV-R.                                                                             */
/*  1.3.0    01/06/2021  TH       Follow 775B 1A.                                                                                    */
/*  1.4.0    05/08/2025  MN       Change for BEV PreCV.                                                                              */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  10/31/2023  SH       Add HmiDate IF                                                                                     */
/* 19PFv3-2  04/04/2024  KH       Delete VRCTRL function                                                                             */
/* 19PFv3-3  05/17/2024  PG       Delete hmircmmui                                                                                   */
/* 19PFv3-4  07/22/2024  AA       Change function for shutdown check                                                                 */
/* 19PFv3-5  08/22/2024  TN       Delete hmitaste function.                                                                          */
/* 19PFv3-6  05/20/2025  PG       Add HmiAdu module                                                                                  */
/* 19PFv3-7  06/27/2025  SH       Add HmiTdoor module                                                                                */
/* BEV-1     10/31/2025  MA       Change for BEV rebase                                                                              */
/* BEV-2     05/08/2025  MN       Change for BEV PreCV.(MET-M_CLKCTL-CSTD-0-/MET-M_CAL-CSTD-0-) Delete hmidate and hmiclock          */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*  * TN   = Tetsushi Nakanao, Denso Techno                                                                                          */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
