/* 1.0.8 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXDOCAN_CFG_H
#define OXDOCAN_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_CFG_H_MAJOR                      (1U)
#define OXDOCAN_CFG_H_MINOR                      (0U)
#define OXDOCAN_CFG_H_PATCH                      (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxdocan_oem.h"
#include "oxdocan_saif.h"
#include "oxdocan.h"

#include "nvmc_mgr.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_KMPH_UNK                            (0xffffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_EOM_IGN_ON                          (0x01U)                 /* Ignition is ON                        */
#define OXDC_EOM_DIAG_ON                          (0x02U)                 /* DiagPower is ON                     */
#define OXDC_EOM_SI_ACT                          (0x04U)                 /* Shipping Inspection is activated      */
#define OXDC_EOM_NUO_DI                          (0x08U)                 /* NvM update operation is disabled      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                          session-rd000-004-b.doc / SESSION-018 */
#define OXDC_SESSION_DEF                         (0x01U)                 /* 0x01  defaultSession                  */
#define OXDC_SESSION_RPG                         (0x02U)                 /* 0x02  programmingSession              */
#define OXDC_SESSION_EXT                         (0x03U)                 /* 0x03  extendedDiagnosticSession       */
#define OXDC_SESSION_OTA                         (0x50U)                 /* 0x50  otaSession                      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_NUM_SID                             (5U)
#define OXDC_SID_22                              (0U)                    /* 0x22 : Read by Identifier             */
#define OXDC_SID_2E                              (1U)                    /* 0x2E : Write by Identifier            */
#define OXDC_SID_2F                              (2U)                    /* 0x2F : I/O Control                    */
#define OXDC_SID_31                              (3U)                    /* 0x31 : Routine                        */
#define OXDC_SID_BA                              (4U)                    /* 0xBA : ECU Shipping Inspection        */
#define OXDC_SID_INA                             (0xffU)                 /*        Service Inactive               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_SERV_TIM_MAX                        (0xfffeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_TASK_NUM_SLOT                       (10U)
#define OXDC_TSLOT_BIT_0                         (0x0001U)               /* 100ms A */
#define OXDC_TSLOT_BIT_1                         (0x0002U)               /* 100ms B */
#define OXDC_TSLOT_BIT_2                         (0x0004U)               /* 100ms C */
#define OXDC_TSLOT_BIT_3                         (0x0008U)               /* 100ms D */
#define OXDC_TSLOT_BIT_4                         (0x0010U)               /* 100ms E */
#define OXDC_TSLOT_BIT_5                         (0x0020U)               /* 100ms F */
#define OXDC_TSLOT_BIT_6                         (0x0040U)               /* 100ms G */
#define OXDC_TSLOT_BIT_7                         (0x0080U)               /* 100ms H */
#define OXDC_TSLOT_BIT_8                         (0x0100U)               /* 100ms I */
#define OXDC_TSLOT_BIT_9                         (0x0200U)               /* 100ms J */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_REQ_TYPE_PHYS                       (0U)
#define OXDC_REQ_TYPE_FUNC                       (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_IOC_PRM                             (2U)
#define OXDC_IOC_CSM                             (3U)                    /* Control State and/or Mask */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define vd_g_oXDoCANCfgReqNvmcToRun()            (vd_g_Nvmc_ClearShtdwnTimer())

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U1 *     u1p_RX;
    U4             u4_nbyte;          /* length of u1p_RX                                       */

    U2             u2_tim_elpsd;      /* resoluation = 10 milliseconds. Max = OXDC_SERV_TIM_MAX */
    U2             u2_kmph;           /* 0.01 km/h                                              */

    U1             u1_eom_bfr;        /* ECU Operation Mode OXDC_EOM_XXX                        */
    U1             u1_eom_aft;        /* ECU Operation Mode OXDC_EOM_XXX                        */
    U1             u1_sid;            /* OXDC_SID_XXX                                           */
    U1             u1_req_type;
    U1             u1_ses_bfr;        /* OXDC_SESSION_XX                                        */
    U1             u1_ses_aft;        /* OXDC_SESSION_XX                                        */
}ST_OXDC_REQ;

typedef struct{
    U1 *           u1p_tx;
    U4             u4_nbyte;          /* length of u1p_tx                                       */
}ST_OXDC_ANS;

typedef struct{
    const U1 *     u1p_RX;
    U4             u4_nbyte;          /* length of u1p_RX                                       */
}ST_OXDC_REQMSG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANAnsTx(const U1 u1_a_NRC, const ST_OXDC_ANS * st_ap_ANS);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* SID 0x14 : ClearDiagnosticInformation    */
/* SID 0x19 : ReadDTCInformation            */
/* SID 0x85 : ControlDTCSetting             */
void    vd_g_oXDoCANDtcBonInit(void);
void    vd_g_oXDoCANDtcRstInit(void);
void    vd_g_oXDoCANDtcWkupInit(void);
U4      u4_g_oXDoCANDtcMainTask(const ST_OXDC_REQ * st_ap_REQ, const U2 u2_a_TSLOT);

/* TimeStamp */
void    vd_g_oXDoCANTmstpBonInit(void);
void    vd_g_oXDoCANTmstpRstInit(void);
void    vd_g_oXDoCANTmstpWkupInit(void);
void    vd_g_oXDoCANTmstpMainTask(const U2 u2_a_TSLOT, const U1 u1_a_EOM);
void    vd_g_oXDoCANTmstpStaTmrwk(void);

/* SID 0x22 : ReadDataByIdentifier          */
void    vd_g_oXDoCANRebyIdInit(void);
void    vd_g_oXDoCANRebyIdMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/* SID 0x2E : WriteDataByIdentifier          */
void    vd_g_oXDoCANWrbyIdInit(void);
void    vd_g_oXDoCANWrbyIdMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/* SID 0x2F : InputOutputControlByIdentifier */
void    vd_g_oXDoCANIocInit(void);
void    vd_g_oXDoCANIocMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);
U1      u1_g_oXDoCANIocReqLenChk(const ST_OXDC_REQ * st_ap_REQ);

/* SID 0x31 : RoutineControl                 */
void    vd_g_oXDoCANRoutInit(void);
void    vd_g_oXDoCANRoutMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);
void    vd_g_oXDoCANRoutStop(const U1 u1_a_NEW);

/* SID 0x86 : ResponseOnEvent                */
void    vd_g_oXDoCANRoePreInit(const U1 u1_a_BON_INIT);
void    vd_g_oXDoCANRoeInit(void);
void    vd_g_oXDoCANRoeMainTask(const U1 u1_a_EOM);

/* SID 0xBA : ECUShippingInspection          */
void    vd_g_TyDoCANEsiInit(void);
void    vd_g_TyDoCANEsiMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANCfgBonPreInit(void);
void    vd_g_oXDoCANCfgRstPreInit(void);
void    vd_g_oXDoCANCfgWkupPreInit(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXDoCANCfgBonInit(void);
void    vd_g_oXDoCANCfgRstInit(void);
void    vd_g_oXDoCANCfgWkupInit(void);

void    vd_g_oXDoCANCfgServiceInit(void);
void    vd_g_oXDoCANCfgMainStart(const ST_OXDC_REQ * st_ap_REQ, const U2 u2_a_TSLOT);
void    vd_g_oXDoCANCfgServiceMain(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U2 u2_a_TSLOT);
void    vd_g_oXDoCANCfgMainFinish(const U2 u2_a_TSLOT);

void    vd_g_oXDoCANCfgComTREOvrrd(const U1 u1_a_COM_CH, const U1 u1_a_MODE);

void    vd_g_oXDoCANRpgInit(void);
U1      u1_g_oXDoCANRpgToAct(U1 * u1_a_errcode);
U1      u1_g_oXDoCANRpgToRun(const U1 u1_a_STATUS);
#if ( OXDC_FUNC_RPG_RESET == OXDC_USE )
void    vd_g_oXDoCANRpgChk(const U1 u1_a_RPG_EN);
#endif /* ( OXDC_FUNC_RPG_RESET == OXDC_USE ) */

void    vd_g_oXDoCANCfgRpgPrepToRun(const U2 u2_a_ELPSD);
#if ( OXDC_FUNC_RPG_RESET == OXDC_USE )
void    vd_g_oXDoCANRpgSwReset(void);
void    vd_g_oXDoCANCfgRpgSwReset(void);
#endif /* ( OXDC_FUNC_RPG_RESET == OXDC_USE ) */
U1      u1_g_oXDoCANCfgRpgCheck(void);
void    vd_g_oXDoCANCfgRpgCancel(void);

U2      u2_g_oXDoCANCfgKmph(void);
U1      u1_g_oXDoCANCfgEomchk(void);

U1      u1_g_oXDoCANCfgDidSessionBitChk(const U1 u1_a_CUR_SES, const U2 u2_a_CONF_SES);
U1      u1_g_oXDoCANCfgSecurityBitChk(const U2 u2_a_CONF_SEC);
void    vd_g_oXDoCANGetStoredReqData(ST_OXDC_REQMSG * st_ap_req);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                u2_g_OXDC_RPG_TIM_TO_RUN;
extern const U2                u2_g_OXDC_RBID_1CYC_READ;

#endif      /* OXDOCAN_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see oxdocan.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
