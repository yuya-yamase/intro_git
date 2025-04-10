/* bsw_cannm_a_eventque_h_v3-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/EVENTQUE/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_EVENTQUE_H
#define BSW_CANNM_A_EVENTQUE_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_A_EVT_NONE             (0x0000U)    /* No event       */
#define BSW_CANNM_A_EVT_NONE_MIRR        (0xffffU)    /* No Event Invert Value */

/* CVT-NM EVENT */
                                                  /* Event group */
#define BSW_CANNM_A_EVT_CVT_GDRV         (0x2000U)    /* Driver */
#define BSW_CANNM_A_EVT_CVT_GAWAKE       (0x3000U)    /* AWAKE */
#define BSW_CANNM_A_EVT_CVT_GOSEK        (0x4000U)    /* OSEK to CVT-NM state change */
#define BSW_CANNM_A_EVT_CVT_GTIMER       (0x5000U)    /* CVT Timer */

#define BSW_CANNM_A_EVT_OSK_GINI         (0x0100U)    /* Initialization */
#define BSW_CANNM_A_EVT_OSK_GAWAKE       (0x0300U)    /* GOTOMODE(AWAKE/SLEEP) */
#define BSW_CANNM_A_EVT_OSK_GTIMER       (0x0500U)    /* OSEK timer */
#define BSW_CANNM_A_EVT_OSK_GSMSG        (0x0600U)    /* Transmission complete MSG  */
#define BSW_CANNM_A_EVT_OSK_GRMSG        (0x0700U)    /* Receive complete MSG  */
#define BSW_CANNM_A_EVT_OSK_GBOFF        (0x0800U)    /* BusOff  */

#define BSW_CANNM_A_EVT_CTL_GTIMER       (BSW_CANNM_A_EVT_CVT_GTIMER | BSW_CANNM_A_EVT_OSK_GTIMER )

/* CVT event */
#define BSW_CANNM_A_EVT_CVT_EBSLPST      ((0x0001U) | BSW_CANNM_A_EVT_CVT_GOSEK)   /* Notification of the start BUSSLEEP      QUE */
#define BSW_CANNM_A_EVT_CVT_EBSLPFN      ((0x0002U) | BSW_CANNM_A_EVT_CVT_GOSEK)   /* Notification of the startup BUSSLEEP      QUE */
#define BSW_CANNM_A_EVT_CVT_ESLPCAN      ((0x0003U) | BSW_CANNM_A_EVT_CVT_GOSEK)   /* SLEEP cancellation notification QUE */
#define BSW_CANNM_A_EVT_CVT_ERESET       ((0x0004U) | BSW_CANNM_A_EVT_CVT_GOSEK)   /* RESET notification - QUE */
#define BSW_CANNM_A_EVT_CVT_EAWAKE       ((0x0005U) | BSW_CANNM_A_EVT_CVT_GAWAKE)  /* AWAKE indication - QUE */
#define BSW_CANNM_A_EVT_CVT_ESLEEP       ((0x0006U) | BSW_CANNM_A_EVT_CVT_GAWAKE)  /* SLEEP indication QUE */
#define BSW_CANNM_A_EVT_CVT_EBSLPSTLMP   ((0x0101U) | BSW_CANNM_A_EVT_CVT_GOSEK)   /* Notification of the start BUSSLEEP LIMP QUE */
#define BSW_CANNM_A_EVT_CVT_EBSLPFNLMP   ((0x0102U) | BSW_CANNM_A_EVT_CVT_GOSEK)   /* Notification of the startup BUSSLEEP LIMP QUE */
#define BSW_CANNM_A_EVT_CVT_EDRVST       ((0x0007U) | BSW_CANNM_A_EVT_CVT_GDRV)    /* Start the driver QUE */
#define BSW_CANNM_A_EVT_CVT_ETPONWOUT    ((0x001dU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* Wait for initial start TIMEOUT */
#define BSW_CANNM_A_EVT_CVT_ETAWAKEOUT   ((0x002dU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* AWAKE Holding waiting - TIMEOUT */
#define BSW_CANNM_A_EVT_CVT_ETPONSOUT    ((0x003dU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* Wait for sleep after reset - TIMEOUT */
#define BSW_CANNM_A_EVT_CVT_ETNWUWOUT    ((0x004dU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* Wait for awake before sleep - TIMEOUT */
#define BSW_CANNM_A_EVT_CVT_ETWUWOUT     ((0x005dU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* Waiting for startup after wake-up TIMEOUT */
#define BSW_CANNM_A_EVT_CVT_ETNOEDGWOUT  ((0x008dU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* Waiting for edge detection invalidation TIMEOUT */
#define BSW_CANNM_A_EVT_CVT_ETNRMEGWOUT  ((0x009dU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* Wait for edge detection start NORMAL TIMEOUT */
#define BSW_CANNM_A_EVT_CVT_ETENAPERI    ((0x00adU) | BSW_CANNM_A_EVT_CVT_GTIMER)  /* Wait for the start of periodic message transmission TIMEOUT */

/* OSEK event */
#define BSW_CANNM_A_EVT_OSK_ESTOP        ((0x0001U) | BSW_CANNM_A_EVT_OSK_GINI)    /* Stop OSEK-NM Request QUE */
#define BSW_CANNM_A_EVT_OSK_ESTART       ((0x0002U) | BSW_CANNM_A_EVT_OSK_GINI)    /* Request to start OSEK-NM - QUE */
#define BSW_CANNM_A_EVT_OSK_EGMDAW       ((0x0003U) | BSW_CANNM_A_EVT_OSK_GAWAKE)  /* GotoMode() awake      QUE */
#define BSW_CANNM_A_EVT_OSK_EGMDSL       ((0x0004U) | BSW_CANNM_A_EVT_OSK_GAWAKE)  /* GotoMode() sleep      QUE */
#define BSW_CANNM_A_EVT_OSK_EBSOFF       ((0x0005U) | BSW_CANNM_A_EVT_OSK_GBOFF)   /* BusOff                QUE */
#define BSW_CANNM_A_EVT_OSK_ESDRNG       ((0x0006U) | BSW_CANNM_A_EVT_OSK_GSMSG)   /* Transmission completion - Ring   MSG */
#define BSW_CANNM_A_EVT_OSK_ESDOTH       ((0x0007U) | BSW_CANNM_A_EVT_OSK_GSMSG)   /* Transmission completion - Other than Ring   MSG */
#define BSW_CANNM_A_EVT_OSK_ERDALV       ((0x0008U) | BSW_CANNM_A_EVT_OSK_GRMSG)   /* Receive complete Alive MSG */
#define BSW_CANNM_A_EVT_OSK_ERDRNG       ((0x0009U) | BSW_CANNM_A_EVT_OSK_GRMSG)   /* Receive complete Ring MSG */
#define BSW_CANNM_A_EVT_OSK_ERDLMP       ((0x000aU) | BSW_CANNM_A_EVT_OSK_GRMSG)   /* Receive complete Limp-Home MSG */
#define BSW_CANNM_A_EVT_OSK_ETTYPOUT     ((0x001dU) | BSW_CANNM_A_EVT_OSK_GTIMER)  /* Ring transmission interval - TTyp - TIMEOUT */
#define BSW_CANNM_A_EVT_OSK_ETMAXOUT     ((0x002dU) | BSW_CANNM_A_EVT_OSK_GTIMER)  /* Ring Enabling Interval - TMax - TIMEOUT */
#define BSW_CANNM_A_EVT_OSK_ETERROUT     ((0x003dU) | BSW_CANNM_A_EVT_OSK_GTIMER)  /* LimpHome transmission interval   Terror TIMEOUT */
#define BSW_CANNM_A_EVT_OSK_ETWBSOUT     ((0x004dU) | BSW_CANNM_A_EVT_OSK_GTIMER)  /* Wait for BUSSLEEP state transition TWbs   TIMEOUT */
#define BSW_CANNM_A_EVT_OSK_ETERWBSOUT   ((0x005dU) | BSW_CANNM_A_EVT_OSK_GTIMER)  /* Wait for BUSSLEEP state transition TErrWbs TErrWbsTIMEOUT */

#define BSW_CANNM_A_EVT_ALL_FAILTOUT     ((0x00fdU) | BSW_CANNM_A_EVT_CTL_GTIMER)  /* Timer for fail          */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  bsw_cannm_a_event_InitChMod(BswU1 u1NetID, BswU1 u1ModKind);
void  bsw_cannm_a_event_SetEvent(BswU1 u1NetID, BswU1 u1ModKind, BswU2 u2EventNo );
BswU2 bsw_cannm_a_event_GetEvent(BswU1 u1NetID, BswU1 u1ModKind);
BswU2 bsw_cannm_a_event_GetToutEvent(BswU1 u1NetID, BswU1 u1ModKind);
void  bsw_cannm_a_event_CheckRam(BswU1 u1NetID);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANNM_A_EVENTQUE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/03/16                                             */
/*  v2-0-0          :2021/12/03                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
