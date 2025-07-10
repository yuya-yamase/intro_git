/* 0.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef User Customization : Physical Value Unit Configuration                                                                    */
/*===================================================================================================================================*/

#ifndef VMMUNIT_CFG_H
#define VMMUNIT_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VMMUNIT_CFG_H_MAJOR                       (0)
#define VMMUNIT_CFG_H_MINOR                       (0)
#define VMMUNIT_CFG_H_PATCH                       (1)

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
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif
#include "vardef.h"
#include "locale.h"
#include "vmmunit.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Definitions                                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VMMUNIT_NUM_M_UNTDB1            (4U)

#define VMMUNIT_M_UNTDB1_KMPL           (0x40U)
#define VMMUNIT_M_UNTDB1_LP100KM        (0x20U)
#define VMMUNIT_M_UNTDB1_MPGUS          (0x10U)
#define VMMUNIT_M_UNTDB1_MPGEU          (0x08U)

#define VMMUNIT_NUM_KIND                (2U)
#define VMMUNIT_KIND_VDF                (0U)
#define VMMUNIT_KIND_MMCST              (1U)

#define VMMUNIT_TIMEOUT                 (COM_TIMEOUT)
#define VMMUNIT_NO_RX                   (COM_NO_RX)

#define VMMUNIT_AVN1S21_TOUT            (10000U / OXCAN_MAIN_TICK)         /* 10[sec] */

#define VMMUNIT_UNIT_NUM                (4U)

#define VMMUNIT_A_UNTCSP_NUM            (8U)
#define VMMUNIT_A_UNTCSP_UNKNOWN        (0xffU)

#define VMMUNIT_TX_JUDGE                (16U)

#define VMMUNIT_RIMID_M_UNITDB1         (RIMID_U1_M_UNTDB1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_VMMUNIT_GETSLCTUNIT()        (u1_g_VardefUnitSlctFuecoByPid())

#define u1_VMMUNIT_ACCISON()             (u1_g_VehopemdAccOn())

#define u1_VMMUNIT_GETMSGSTS_AVN1S21()  (u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_AVN1S21, (U4)OXCAN_SYS_ACC, (U2)VMMUNIT_AVN1S21_TOUT))
#if 0   /* BEV BSW provisionally */
#define vd_VMMUNIT_RXMSG_A_CSPCHG(x)    ((void)Com_ReceiveSignal(ComConf_ComSignal_A_CSPCHG,(x)))
#define vd_VMMUNIT_RXMSG_A_UNTCSP(x)    ((void)Com_ReceiveSignal(ComConf_ComSignal_A_UNTCSP,(x)))
#else
#define vd_VMMUNIT_RXMSG_A_CSPCHG(x)    (vdp_PTR_NA)
#define vd_VMMUNIT_RXMSG_A_UNTCSP(x)    (vdp_PTR_NA)
#endif

#if 0   /* BEV BSW provisionally */
#define vd_VMMUNIT_WRITE_M_UNTDB1(x)    ((void)Com_SendSignal(ComConf_ComSignal_M_UNTDB1,(x)))    /* COM Tx STUB delete */
#else
#define vd_VMMUNIT_WRITE_M_UNTDB1(x)    (vdp_PTR_NA)
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

static const U1    u1_gp2_VMMUNIT_UNITCONVRT[VMMUNIT_NUM_M_UNTDB1][VMMUNIT_NUM_KIND] = {
    /* VMMUNIT_KIND_VDF                                                  VMMUNIT_KIND_MMCST                             */
    { (U1)VDF_UNIT_FUECO_BIT_KMPL                                      , (U1)VMMUNIT_M_UNTDB1_KMPL    },   /*  km/l     */
    { (U1)VDF_UNIT_FUECO_BIT_LP100KM                                   , (U1)VMMUNIT_M_UNTDB1_LP100KM },   /*  l/100km  */
    { (U1)VDF_UNIT_FUECO_BIT_MPG_USA                                   , (U1)VMMUNIT_M_UNTDB1_MPGUS   },   /*  MPG(US)  */
    { (U1)VDF_UNIT_FUECO_BIT_MPG_UK | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VMMUNIT_M_UNTDB1_MPGEU   }    /*  MPG(UK)  */
};

static const U1    u1_gp2_VMMUNIT_CNRTLOCALE[VMMUNIT_A_UNTCSP_NUM][VMMUNIT_UNIT_NUM] = {
    /* DIST                           SPEED                          FUECO                          ELECO                                A_UNTCSP     */
    { (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN },   /*  000:Unknown  */
    { (U1)UNIT_VAL_DIST_KM         , (U1)UNIT_VAL_SPEED_KMPH      , (U1)UNIT_VAL_FUECO_KMPL      , (U1)UNIT_VAL_ELECO_KMPKWH    },   /*  001:km/L     */
    { (U1)UNIT_VAL_DIST_KM         , (U1)UNIT_VAL_SPEED_KMPH      , (U1)UNIT_VAL_FUECO_LP100KM   , (U1)UNIT_VAL_ELECO_KWHP100KM },   /*  010:L/100km  */
    { (U1)UNIT_VAL_DIST_MILE       , (U1)UNIT_VAL_SPEED_MPH       , (U1)UNIT_VAL_FUECO_MPG_USA   , (U1)UNIT_VAL_ELECO_MILEPKWH  },   /*  011:MPG(US)  */
    { (U1)UNIT_VAL_DIST_MILE       , (U1)UNIT_VAL_SPEED_MPH       , (U1)UNIT_VAL_FUECO_MPG_UK    , (U1)UNIT_VAL_ELECO_MILEPKWH  },   /*  100:MPG(UK)  */
    { (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN },   /*  101:Unknown  */
    { (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN },   /*  110:Unknown  */
    { (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN , (U1)VMMUNIT_A_UNTCSP_UNKNOWN }    /*  111:Unknown  */
};

static const U1    u1_gp_VMMUNIT_LOCALEIDX[VMMUNIT_UNIT_NUM] = {
    (U1)UNIT_IDX_DIST,
    (U1)UNIT_IDX_SPEED,
    (U1)UNIT_IDX_FUECO,
    (U1)UNIT_IDX_ELECO
};

/* A_UNTCSP �? M_UNTDB1 */
static const U1    u1_gp_VMMUNIT_METUNIT_TBL[VMMUNIT_A_UNTCSP_NUM] = {
    (U1)0U,                           /*  000:Unknown  */
    (U1)VMMUNIT_M_UNTDB1_KMPL,        /*  001:km/L     */
    (U1)VMMUNIT_M_UNTDB1_LP100KM,     /*  010:L/100km  */
    (U1)VMMUNIT_M_UNTDB1_MPGUS,       /*  011:MPG(US)  */
    (U1)VMMUNIT_M_UNTDB1_MPGEU,       /*  100:MPG(UK)  */
    (U1)0U,                           /*  101:Unknown  */
    (U1)0U,                           /*  110:Unknown  */
    (U1)0U                            /*  111:Unknown  */
};

static const U1    u1_gp_VMMUNIT_TX_JUDGE_TBL[VMMUNIT_TX_JUDGE] = {
    (U1)TRUE,                   /* Non                                */
    (U1)TRUE,                   /* MPGUK                              */
    (U1)TRUE,                   /* MPGUS                              */
    (U1)FALSE,                  /* MPGUK,MPGUS                        */
    (U1)TRUE,                   /* L/100km                            */
    (U1)TRUE,                   /* MPGUK,L/100km                      */
    (U1)TRUE,                   /* MPGUS,L/100km                      */
    (U1)FALSE,                  /* MPGUK,MPGUS,L/100km                */
    (U1)TRUE,                   /* km/L                               */
    (U1)TRUE,                   /* MPGUK,km/L                         */
    (U1)TRUE,                   /* MPGUS,km/L                         */
    (U1)FALSE,                  /* MPGUK,MPGUS,km/L                   */
    (U1)TRUE,                   /* L/100km,km/L                       */
    (U1)TRUE,                   /* MPGUK,L/100km,km/L(UK only)        */
    (U1)TRUE,                   /* MPGUS,L/100km,km/L(US only)        */
    (U1)TRUE                    /* MPGUK,MPGUS,L/100km,km/L(US only)  */
};

#endif /* #ifndef VMMUNIT_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  vmmunit.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
