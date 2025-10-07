/* bsw_bswm_vps_ctrl2_h_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/VPS/CTRL2/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_VPS_CTRL2_H
#define     BSW_BSWM_VPS_CTRL2_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    BswU2 u2RlyOnConfTimer;
    BswU2 u2RlyOnConfRxTimer;
    BswU2 u2WfChgVPSTimer;
    BswU2 u2WfResetTimer;
    BswU2 u2WfRxPncTimer;
    BswU1 u1RlyOnConfTimerOn;
    BswU1 u1RlyOnConfRxTimerOn;
    BswU1 u1WfChgVPSTimerOn;
    BswU1 u1WfResetTimerOn;
    BswU1 u1WfRxPncTimerOn;
    BswU1 u1SetSysStEvnt;
    BswU1 u1VhPwStSpTransSt;
    BswU1 u1ActiveBus;
    BswU1 u1ActiveBusMrr;
    BswU1 u1SetSysStatReq;
    BswU1 u1RxSysStChng;
    BswU1 u1RlyOnConfKind;
    BswU1 u1RxTransSt0;
    BswU1 u1RxTransSt1;
    BswU1 u1RxVPSFixSt;
    BswU1 u1DummyPad0;
} Bsw_BswM_VPS_StsType;

typedef struct
{
    BswU2 u2RxVPSStatus;
    BswU2 u2RxVPSTimer;
    BswU1 u1RxVPSTimerOn;
    BswU1 u1DummyPad;
} Bsw_BswM_RxVPS_StsType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_BswM_VPS_StsType   bsw_bswm_vps_ctrl_stSts;
extern Bsw_BswM_RxVPS_StsType bsw_bswm_vps_ctrl_stRxVPSSts[];
extern BswU1                  bsw_bswm_vps_ctrl_u1SetWkFc[];
extern BswU4                  bsw_bswm_vps_ctrl_u4SysSt[];
extern BswU4                  bsw_bswm_vps_ctrl_u4SysStMrr[];
extern BswU4                  bsw_bswm_vps_ctrl_u4RxSysSt0[];
extern BswU4                  bsw_bswm_vps_ctrl_u4RxSysStMrr0[];
extern BswU4                  bsw_bswm_vps_ctrl_u4RxSysSt1[];
extern BswU4                  bsw_bswm_vps_ctrl_u4RxSysStMrr1[];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#endif  /* BSW_BSWM_CS_CTRL2_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2025/02/25                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
