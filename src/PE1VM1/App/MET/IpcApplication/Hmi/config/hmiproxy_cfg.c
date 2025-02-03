/* 1.3.0 */
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
#define HMIPROXY_CFG_C_MINOR                     (3)
#define HMIPROXY_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"

#include "hmimm2c100n.h"
#include "hmimm2c107n.h"
#include "hmimm2c112n.h"
#include "hmimm2c118n.h"
#include "hmimm2c124n.h"
#include "hmivardef.h"
#include "hmidiag.h"
#include "hmigateway.h"
#include "hmihud.h"
#include "hmilcom.h"
#include "hmilocale.h"
#include "hmimaint.h"
#include "hmioilmaint.h"
#include "hmiodo.h"
#include "hmirim.h"
#include "hmiputxt.h"
#include "hmitt.h"
#include "hmiwchime.h"
#include "hmitripcom.h"
#include "hmiclock.h"
#include "hmimcst.h"
#include "hmifuel.h"
#include "hmiscreen.h"
#include "hmitaste.h"
#include "hmidate.h"

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
#if 0   /* BEV BSW provisionally */
#else
#define SCHDLR_TASKBIT_RGLR                      (0x001ffffeU)
#endif
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
     &vd_g_HmiMM2C100NInit,
     &vd_g_HmiMM2C107NInit,
     &vd_g_HmiMM2C112NInit,
     &vd_g_HmiMM2C118NInit,
     &vd_g_HmiMM2C124NInit,
     &vd_g_HmiVardefInit,
     &vd_g_HmiDiagInit,
     &vd_g_HmiGatewayInit,
     &vd_g_HmiHudInit,
     &vd_g_HmiLcomInit,
     &vd_g_HmiLocaleInit,
     &vd_g_HmiMaintInit,
     &vd_g_HmiOilmaintInit,
     &vd_g_HmiOdoInit,
     &vd_g_HmiRimBonInit,
     &vd_g_HmiPuTxtInit,
     &vd_g_HmiTtInit,
     &vd_g_HmiWchimeInit,
     &vd_g_HmiTripcomInit,
     &vd_g_HmiClockInit,
     &vd_g_HmiMcstInit,
     &vd_g_HmiFuelInit,
     &vd_g_HmiScreenInit,
     &vd_g_HmiTasteInit,
     &vd_g_HmiDateInit
};

void ( * const              fp_gp_vd_HMIPROXY_RST_INIT[HMIPROXY_INIT_NUM])(void) = {
     &vd_g_HmiMM2C100NInit,
     &vd_g_HmiMM2C107NInit,
     &vd_g_HmiMM2C112NInit,
     &vd_g_HmiMM2C118NInit,
     &vd_g_HmiMM2C124NInit,
     &vd_g_HmiVardefInit,
     &vd_g_HmiDiagInit,
     &vd_g_HmiGatewayInit,
     &vd_g_HmiHudInit,
     &vd_g_HmiLcomInit,
     &vd_g_HmiLocaleInit,
     &vd_g_HmiMaintInit,
     &vd_g_HmiOilmaintInit,
     &vd_g_HmiOdoInit,
     &vd_g_HmiRimRstWkupInit,
     &vd_g_HmiPuTxtInit,
     &vd_g_HmiTtInit,
     &vd_g_HmiWchimeInit,
     &vd_g_HmiTripcomInit,
     &vd_g_HmiClockInit,
     &vd_g_HmiMcstInit,
     &vd_g_HmiFuelInit,
     &vd_g_HmiScreenInit,
     &vd_g_HmiTasteInit,
     &vd_g_HmiDateInit
};

void ( * const              fp_gp_vd_HMIPROXY_WKUP_INIT[HMIPROXY_INIT_NUM])(void) = {
     &vd_g_HmiMM2C100NInit,
     &vd_g_HmiMM2C107NInit,
     &vd_g_HmiMM2C112NInit,
     &vd_g_HmiMM2C118NInit,
     &vd_g_HmiMM2C124NInit,
     &vd_g_HmiVardefInit,
     &vd_g_HmiDiagInit,
     &vd_g_HmiGatewayInit,
     &vd_g_HmiHudInit,
     &vd_g_HmiLcomInit,
     &vd_g_HmiLocaleInit,
     &vd_g_HmiMaintInit,
     &vd_g_HmiOilmaintInit,
     &vd_g_HmiOdoInit,
     &vd_g_HmiRimRstWkupInit,
     &vd_g_HmiPuTxtInit,
     &vd_g_HmiTtInit,
     &vd_g_HmiWchimeInit,
     &vd_g_HmiTripcomInit,
     &vd_g_HmiClockInit,
     &vd_g_HmiMcstInit,
     &vd_g_HmiFuelInit,
     &vd_g_HmiScreenInit,
     &vd_g_HmiTasteInit,
     &vd_g_HmiDateInit
};

U1   ( * const              fp_gp_u1_HMIPROXY_SHTDWN_CHK[HMIPROXY_SHTDWN_NUM])(void) = {
     &u1_g_HmiScreenShtdwnOK
};

const ST_HMIPROXY     st_gp_HMIPROXY[HMIPROXY_MAINTASK_NUM] = {
     {&vd_g_HmiMM2C100NMainTask, (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiMM2C107NMainTask, (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiMM2C112NMainTask, (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiMM2C118NMainTask, (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiMM2C124NMainTask, (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiVardefMainTask,   (U4)SCHDLR_TASKBIT__20MS_B  },
     {&vd_g_HmiDiagMainTask ,    (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiGatewayMainTask , (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiHudMainTask ,     (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiLcomMainTask,     (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiLocaleMainTask,   (U4)SCHDLR_TASKBIT__20MS_B  },
     {&vd_g_HmiMaintMainTask,    (U4)SCHDLR_TASKBIT__50MS_C  },
     {&vd_g_HmiOdoMainTask,      (U4)SCHDLR_TASKBIT__50MS_C  },
     {&vd_g_HmiOilmaintMainTask, (U4)SCHDLR_TASKBIT__20MS_B  },
     {&vd_g_HmiRimMainTask,      (U4)SCHDLR_TASKBIT__50MS_E  },
     {&vd_g_HmiPuTxtMainTask,    (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiTtMainTask,       (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiWchimeMainTask,   (U4)SCHDLR_TASKBIT__10MS_A  },
     {&vd_g_HmiTripcomMainTask,  (U4)SCHDLR_TASKBIT__50MS_E  },
     {&vd_g_HmiClockMainTask,    (U4)SCHDLR_TASKBIT__20MS_A  },
     {&vd_g_HmiMcstMainTask,     (U4)SCHDLR_TASKBIT__20MS_B  },
     {&vd_g_HmiFuelMainTask,     (U4)SCHDLR_TASKBIT_100MS_E  },
     {&vd_g_HmiScreenMainTask,   (U4)SCHDLR_TASKBIT__50MS_A  },
     {&vd_g_HmiTasteMainTask,    (U4)SCHDLR_TASKBIT__50MS_E  },
     {&vd_g_HmiDateMainTask,     (U4)SCHDLR_TASKBIT__20MS_A  },
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
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  10/31/2023  SH       Add HmiDate IF                                                                                     */
/* 19PFv3-2  04/04/2024  KH       Delete VRCTRL function                                                                             */
/* 19PFv3-3  05/17/2024  PG       Delete hmircmmui                                                                                   */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
