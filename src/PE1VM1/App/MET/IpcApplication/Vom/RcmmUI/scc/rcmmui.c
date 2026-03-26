/* 1.4.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Recommendation user interface                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RCMMUI_C_MAJOR                          (1)
#define RCMMUI_C_MINOR                          (4)
#define RCMMUI_C_PATCH                          (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "rcmmui_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RCMMUI_C_MAJOR != RCMMUI_H_MAJOR) || \
     (RCMMUI_C_MINOR != RCMMUI_H_MINOR) || \
     (RCMMUI_C_PATCH != RCMMUI_H_PATCH))
#error "rcmmui.c and rcmmui.h : source and header files are inconsistent!"
#endif

#if ((RCMMUI_C_MAJOR != RCMMUI_CFG_H_MAJOR) || \
     (RCMMUI_C_MINOR != RCMMUI_CFG_H_MINOR) || \
     (RCMMUI_C_PATCH != RCMMUI_CFG_H_PATCH))
#error "rcmmui.c and rcmmui_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RCMMUI_NEG_RESP                         (0xF0U)
#define RCMMUI_USRACR_RESP                      (0x20U)
#define RCMMUI_NUM_REQ                          (26U)

#define RCMMUI_UACT_INIT                        (0xFEU)
#define RCMMUI_UACT_INVLD                       (0xFFU)

#define RCMMUI_ITAB_MASK                        (0xFF7FU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2                                          u2_reqtype;
    U1                                          u1_rxresp;
    U1                                          u1_usractresp;
} ST_RCMMUI_REQUEST;


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                                      u1_s_rcmmui_usract;
static  U1                                      u1_s_rcmmui_reqid;
static  U2                                      u2_s_rcmmui_reqelpsd;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      u1_s_RcmmUISearchReq(const U2 u2_a_RCMM);
static  U1      u1_s_RcmmUICheckPow(const U1 u1_a_REQID);
void            vd_s_RcmmUICheckPowSts(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  const   ST_RCMMUI_REQUEST               st_sp_RCMMUI_REQUESTS[RCMMUI_NUM_REQ]    = {
    /* START REQUEST */
    {   (U2)0x0109U,            (U1)0x10U,              (U1)0x13U       },      /* 00 RCMMUI_STREQ_1_1   */
    {   (U2)0x0119U,            (U1)0x10U,              (U1)0x10U       },      /* 01 RCMMUI_STREQ_1_3   */
    {   (U2)0x0209U,            (U1)0x10U,              (U1)0x10U       },      /* 02 RCMMUI_STREQ_2_1   */
    {   (U2)0x0309U,            (U1)0x10U,              (U1)0x10U       },      /* 03 RCMMUI_STREQ_3_1_1 */
    {   (U2)0x0409U,            (U1)0x10U,              (U1)0x10U       },      /* 04 RCMMUI_STREQ_3_1_2 */
    {   (U2)0x0000U,            (U1)0x00U,              (U1)0x00U       },      /* 05 No use             */
    {   (U2)0x0609U,            (U1)0x10U,              (U1)0x13U       },      /* 06 RCMMUI_STREQ_6_1   */
    {   (U2)0x0611U,            (U1)0x10U,              (U1)0x14U       },      /* 07 RCMMUI_STREQ_6_2   */
    {   (U2)0x0619U,            (U1)0x10U,              (U1)0x10U       },      /* 08 RCMMUI_STREQ_6_3   */
    {   (U2)0x0809U,            (U1)0x10U,              (U1)0x13U       },      /* 09 RCMMUI_STREQ_8_1   */
    {   (U2)0x0811U,            (U1)0x10U,              (U1)0x14U       },      /* 10 RCMMUI_STREQ_8_2   */
    {   (U2)0x0819U,            (U1)0x10U,              (U1)0x10U       },      /* 11 RCMMUI_STREQ_8_3   */
    {   (U2)0x0B09U,            (U1)0x10U,              (U1)0x13U       },      /* 12 RCMMUI_STREQ_11_1  */
    {   (U2)0x0B19U,            (U1)0x10U,              (U1)0x10U       },      /* 13 RCMMUI_STREQ_11_3  */
    {   (U2)0x0C09U,            (U1)0x10U,              (U1)0x13U       },      /* 14 RCMMUI_STREQ_12_1  */
    {   (U2)0x0C19U,            (U1)0x10U,              (U1)0x10U       },      /* 15 RCMMUI_STREQ_12_3  */
    /* END REQUEST */
    {   (U2)0x0178U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0x0278U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0x0378U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0x0478U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0x0678U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0x0878U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0x0B78U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0x0C78U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0xFF00U,            (U1)0x30U,              (U1)0x00U       },
    {   (U2)0xFF80U,            (U1)0x30U,              (U1)0x00U       }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_RcmmUIInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_RcmmUIInit(void)
{
    u1_s_rcmmui_usract   = (U1)RCMMUI_UACT_INVLD;
    u1_s_rcmmui_reqid    = (U1)RCMMUI_REQ_NONE;
    u2_s_rcmmui_reqelpsd = (U2)U2_MAX;

    vd_g_RcmmUIInitCfg();
}

/*===================================================================================================================================*/
/* void            vd_g_RcmmUIMainTask(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_RcmmUIMainTask(void)
{
    static   const   U1                         u1_sp_USRACT_SIG[RCMMUI_NUM_USRACT] = {
        (U1)0x01U,                              /* 00 RCMMUI_USRACR_YES   */
        (U1)0x02U,                              /* 01 RCMMUI_USRACR_NO    */
        (U1)0x0DU,                              /* 02 RCMMUI_USRACR_ENTER */
        (U1)0x0EU,                              /* 03 RCMMUI_USRACR_TOP   */
        (U1)0x0FU                               /* 04 RCMMUI_USRACR_BACK  */
    };
    const   ST_RCMMUI_REQUEST *                 stp_t_REQ;
    U2                                          u2_t_rcmm;
    U1                                          u1_t_reqid;
    U1                                          u1_t_response;
    U1                                          u1_t_powchk;
    U1                                          u1_t_usractchk;


    /* Timer control */
    if (u2_s_rcmmui_reqelpsd < (U2)U2_MAX) {
        u2_s_rcmmui_reqelpsd++;
    }
    if (u2_s_rcmmui_reqelpsd >= (U2)RCMMI_STREQ_TO) {
        u1_s_rcmmui_reqid = (U1)RCMMUI_REQ_NONE;
    }

    /*  Power state check */
    vd_s_RcmmUICheckPowSts(); 

    /* Start end request */
    u2_t_rcmm   = (U2)0U;
    vd_g_RcmmUICfgCanRx(&u2_t_rcmm);

    u1_t_response =  (U1)0U;

    if (u2_t_rcmm != (U2)0U) {
        u1_t_reqid     = u1_s_RcmmUISearchReq(u2_t_rcmm);
        u1_t_response  = (U1)RCMMUI_NEG_RESP;
        if (u1_t_reqid < (U1)RCMMUI_NUM_REQ) {
            u1_s_rcmmui_reqid    = (U1)RCMMUI_REQ_NONE;
            u2_s_rcmmui_reqelpsd = (U2)U2_MAX;
            u1_t_response        = st_sp_RCMMUI_REQUESTS[u1_t_reqid].u1_rxresp;
            u2_t_rcmm           &= (U2)RCMMUI_ITAB_MASK;
        }
        u1_t_powchk = u1_s_RcmmUICheckPow(u1_t_reqid);
        if ((u1_t_reqid  <  (U1)RCMMUI_NUM_STREQ) &&
            (u1_t_powchk == (U1)TRUE            )) {

            u1_s_rcmmui_reqid    = u1_t_reqid;
            u1_s_rcmmui_usract   = (U1)RCMMUI_UACT_INIT;
            u2_s_rcmmui_reqelpsd = (U2)0U;
        }
    }
    /* User action control */
    else if ((u1_s_rcmmui_usract < (U1)RCMMUI_NUM_USRACT) &&
             (u1_s_rcmmui_reqid  < (U1)RCMMUI_NUM_STREQ )) {

        u1_t_usractchk = (U1)((U1)1U << u1_s_rcmmui_usract);
        stp_t_REQ      = &st_sp_RCMMUI_REQUESTS[u1_s_rcmmui_reqid];
        if ((stp_t_REQ->u1_usractresp & u1_t_usractchk) != (U1)0U) {
            u2_t_rcmm      = stp_t_REQ->u2_reqtype;
            u1_t_response  = (U1)RCMMUI_USRACR_RESP | u1_sp_USRACT_SIG[u1_s_rcmmui_usract];
        }

        u1_s_rcmmui_usract = (U1)RCMMUI_UACT_INVLD;
    }
    else {
        /* do nothing */
    }


    if (u1_t_response != (U1)0U) {
        vd_g_RcmmUICfgCanTx(u2_t_rcmm, u1_t_response);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_RcmmUISelect(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_RcmmUISelect(void)
{
    return (u1_s_rcmmui_reqid);
}

/*===================================================================================================================================*/
/* void            vd_g_RcmmUIUserAct(const U1 u1_a_CID, const U1 u1_a_USRACT)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_RcmmUIUserAct(const U1 u1_a_CID, const U1 u1_a_USRACT)
{
    if ((u1_a_USRACT         < (U1)RCMMUI_NUM_USRACT) &&
        (u1_s_rcmmui_usract == (U1)RCMMUI_UACT_INIT )) {
        if(u1_a_CID == u1_s_rcmmui_reqid    ){
            u1_s_rcmmui_usract = u1_a_USRACT;
        }
    }

    if((u1_a_USRACT == (U1)RCMMUI_USRACT_YES                                       ) &&
       ((u1_a_CID   == (U1)RCMMUI_STREQ_1_1) || (u1_a_CID == (U1)RCMMUI_STREQ_11_1)) &&
       (u1_a_CID    == u1_s_rcmmui_reqid                                           )) {
        vd_g_RcmmUIPbdmswPut((U1)RCMMUI_PBDMSW_ON);
    }
    else{
        vd_g_RcmmUIPbdmswPut((U1)RCMMUI_PBDMSW_OFF);
    }

}

/*===================================================================================================================================*/
/* static  U1      u1_s_RcmmUISearchReq(const U2 u2_a_RCMM)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_RcmmUISearchReq(const U2 u2_a_RCMM)
{
    U4          u4_t_loop;
    U1          u1_t_reqid;


    u1_t_reqid = (U1)U1_MAX;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)RCMMUI_NUM_REQ; u4_t_loop++) {
        if (u2_a_RCMM == st_sp_RCMMUI_REQUESTS[u4_t_loop].u2_reqtype) {
            u1_t_reqid = (U1)u4_t_loop;
        }
    }
    return (u1_t_reqid);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_RcmmUICheckPow(const U1 u1_a_REQID)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_RcmmUICheckPow(const U1 u1_a_REQID)
{
    U1     u1_t_chk;

    u1_t_chk = u1_g_RcmmUICfgCheckPow(u1_a_REQID);

    return (u1_t_chk);
}

/*===================================================================================================================================*/
/*  void              vd_s_RcmmUICheckPowSts(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_s_RcmmUICheckPowSts(void)
{
    U1 u1_t_powsts_chk;

    if (u1_s_rcmmui_reqid != (U1)RCMMUI_REQ_NONE) {
        u1_t_powsts_chk = u1_s_RcmmUICheckPow(u1_s_rcmmui_reqid);
        if (u1_t_powsts_chk == (U1)FALSE) {
            u1_s_rcmmui_reqid = (U1)RCMMUI_REQ_NONE;
            u2_s_rcmmui_reqelpsd = (U2)U2_MAX;
        }
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    02/18/2018  HY       New.                                                                                               */
/*  1.1.0    10/07/2020  TH       Add to send PBDMSW and getting elapsed time of rcmmui display start.                               */
/*  1.2.0    10/01/2025  YR       Change config for 19PFv3                                                                           */
/*  1.3.0    07/03/2025  KO       Change config for BEV System_Consideration_2.                                                      */
/*  1.4.0    01/26/2026  SN       Change for MET-B_PROSRV-CSTD-1-02-A-C0                                                             */
/*                                "TOP" button removed from all messages by parameter.                                               */
/*                                Bugfix(BEVCDCMON-258)                                                                              */
/*                                Display is hidden by mask processing when not in operating power state.                            */
/*  1.4.1    03/17/2026  HY(K)    Change for BEV Full_Function_2.                                                                    */
/*                                MET-B_PROSRV-CSTD-1-02-A-C0 Bugfix(BEV3CDCMET-4550)                                                */
/*                                Delete exception-handling branching in vd_g_RcmmUIUserAct function.                                */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  05/17/2024  PG       Add REQ for PROSRV                                                                                 */
/*                                Delete u1_g_RcmmUITimeoutGet function                                                              */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * TH   = Takahiro Hirano,  Denso Techno                                                                                          */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * SN   = Shizuka Nakajima,  KSE                                                                                                  */
/*  * HY(K)= Haruki Yagi,  KSE                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
