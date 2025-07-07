/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  DtcCtl                                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "PncreqCtl.h"
#include    "memfill_u1.h"
#include    "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    PNCREQCTL_STOP               (0U)
#define    PNCREQCTL_OPERATE            (1U)

#define    PNCREQCTL_PNCID_56_63        (0U)
#define    PNCREQCTL_PNCID_48_55        (1U)
#define    PNCREQCTL_PNCID_40_47        (2U)
#define    PNCREQCTL_PNCID_32_39        (3U)
#define    PNCREQCTL_PNCID_24_31        (4U)
#define    PNCREQCTL_PNCID_16_23        (5U)
#define    PNCREQCTL_ALIVECOUNETR       (6U)

#define    PNCREQCTL_PNCID_16_MASK      (0x80U)
#define    PNCREQCTL_PNCID_40_MASK      (0x80U)
#define    PNCREQCTL_PNCID_43_MASK      (0x10U)
#define    PNCREQCTL_PNCID_44_MASK      (0x08U)

#define    PNCREQCTL_PNCID_REQNUM       (4U)
#define    PNCREQCTL_PNCID_16           (0U)
#define    PNCREQCTL_PNCID_40           (1U)
#define    PNCREQCTL_PNCID_43           (2U)
#define    PNCREQCTL_PNCID_44           (3U)

#define    PNCREQCTL_REQ_OFF            (0U)
#define    PNCREQCTL_REQ_ON             (1U)

#define    PNCREQCTL_TIMECNTINIT        (U2_MAX)
#define    PNCREQCTL_TIMEOUT            (3000U)         /* 60s LSB:20ms */
#define    PNCREQCTL_TXCNTINIT          (U1_MAX)
#define    PNCREQCTL_TXREQTIME          (100U)          /* 2s  LSB:20ms */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2    u2_s_pncreqctl_timeoutcnt;
static U1    u1_s_pncreqctl_actsts;
static U1    u1_s_pncreqctl_alvcnt;
static U1    u1_s_pncreqctl_req[PNCREQCTL_PNCID_REQNUM];
static U1    u1_s_pncreqctl_txcnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_PncReqctl_PartialNMReqJdg(const U1* u1_ap_PNCREQDATA);
static void     vd_s_PncReqctl_PartialNMSetReq(const U1* u1_ap_PNCREQDATA);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_PncReqctl_Init(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PncReqctl_Init(void)
{
    u2_s_pncreqctl_timeoutcnt = (U2)PNCREQCTL_TIMECNTINIT;
    u1_s_pncreqctl_actsts = (U1)PNCREQCTL_STOP;
    u1_s_pncreqctl_alvcnt = (U1)U1_MAX;
    u1_s_pncreqctl_txcnt  = (U1)PNCREQCTL_TXCNTINIT;
    vd_g_MemfillU1(&u1_s_pncreqctl_req[PNCREQCTL_PNCID_16], (U1)PNCREQCTL_REQ_OFF, (U4)PNCREQCTL_PNCID_REQNUM);
}

/*===================================================================================================================================*/
/*  void            vd_g_PncReqctl_MainTask(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PncReqctl_MainTask(void)
{
    U1    u1_t_reqdata[PNCREQCTL_PNCID_REQNUM];

    if(u1_s_pncreqctl_actsts == (U1)PNCREQCTL_OPERATE){
        if((u2_s_pncreqctl_timeoutcnt >= (U2)PNCREQCTL_TIMEOUT) &&
           (u2_s_pncreqctl_timeoutcnt != (U2)PNCREQCTL_TIMECNTINIT)){
            vd_g_MemfillU1(&u1_t_reqdata[PNCREQCTL_PNCID_16], (U1)PNCREQCTL_REQ_OFF, (U4)PNCREQCTL_PNCID_REQNUM);
            vd_s_PncReqctl_PartialNMSetReq(&u1_t_reqdata[PNCREQCTL_PNCID_16]);
            u2_s_pncreqctl_timeoutcnt = (U2)PNCREQCTL_TIMECNTINIT;
            u1_s_pncreqctl_txcnt = (U1)PNCREQCTL_TXCNTINIT;
        }
        if((u1_s_pncreqctl_txcnt >= (U1)PNCREQCTL_TXREQTIME) &&
           (u1_s_pncreqctl_txcnt != (U1)PNCREQCTL_TXCNTINIT)){
            vd_s_PncReqctl_PartialNMSetReq(&u1_s_pncreqctl_req[PNCREQCTL_PNCID_16]);
            u1_s_pncreqctl_txcnt  = (U1)0U;
        }
        if(u2_s_pncreqctl_timeoutcnt < (U2)PNCREQCTL_TIMECNTINIT){
            u2_s_pncreqctl_timeoutcnt++;
        }
        if(u1_s_pncreqctl_txcnt < (U1)PNCREQCTL_TXCNTINIT){
            u1_s_pncreqctl_txcnt++;
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_PncReqctl_PartialNMSendReq(const U1 * u1_ap_PNCREQDATA)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PncReqctl_PartialNMSendReq(const U1 * u1_ap_PNCREQDATA)
{
    if((u1_s_pncreqctl_actsts == (U1)PNCREQCTL_OPERATE) &&
       ((u1_ap_PNCREQDATA != NULL_PTR) &&
        (u1_s_pncreqctl_alvcnt != u1_ap_PNCREQDATA[PNCREQCTL_ALIVECOUNETR]))){
        u1_s_pncreqctl_alvcnt = u1_ap_PNCREQDATA[PNCREQCTL_ALIVECOUNETR];
        u2_s_pncreqctl_timeoutcnt = (U2)0U;
        u1_s_pncreqctl_txcnt  = (U1)0U;
        vd_s_PncReqctl_PartialNMReqJdg(&u1_ap_PNCREQDATA[PNCREQCTL_PNCID_56_63]);
        vd_s_PncReqctl_PartialNMSetReq(&u1_s_pncreqctl_req[PNCREQCTL_PNCID_16]);
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_PncReqctl_PartialNMGetSts(const U1 u1_a_STS)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PncReqctl_PartialNMGetSts(const U1 u1_a_STS)
{
    U1    u1_t_reqdata[PNCREQCTL_PNCID_REQNUM];
    
    if(u1_a_STS == (U1)PNCREQCTL_OPERATE){
        if(u1_s_pncreqctl_actsts == (U1)PNCREQCTL_STOP){
            u2_s_pncreqctl_timeoutcnt = (U2)0U;
            u1_s_pncreqctl_alvcnt = (U1)U1_MAX;
            vd_g_MemfillU1(&u1_s_pncreqctl_req[PNCREQCTL_PNCID_16], (U1)PNCREQCTL_REQ_OFF, (U4)PNCREQCTL_PNCID_REQNUM);
        }
        u1_s_pncreqctl_actsts = u1_a_STS;
    }
    else if(u1_a_STS == (U1)PNCREQCTL_STOP){
        u2_s_pncreqctl_timeoutcnt = (U2)PNCREQCTL_TIMECNTINIT;
        u1_s_pncreqctl_txcnt  = (U1)PNCREQCTL_TXCNTINIT;
        vd_g_MemfillU1(&u1_t_reqdata[PNCREQCTL_PNCID_16], (U1)PNCREQCTL_REQ_OFF, (U4)PNCREQCTL_PNCID_REQNUM);
        vd_s_PncReqctl_PartialNMSetReq(&u1_t_reqdata[PNCREQCTL_PNCID_16]);
        u1_s_pncreqctl_actsts = u1_a_STS;
    }
    else{
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_PncReqctl_PartialNMReqJdg(const U1* u1_ap_PNCREQDATA)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PncReqctl_PartialNMReqJdg(const U1* u1_ap_PNCREQDATA)
{
    U1     u1_t_req;

    u1_t_req = u1_ap_PNCREQDATA[PNCREQCTL_PNCID_16_23] & (U1)PNCREQCTL_PNCID_16_MASK;
    if(u1_t_req != (U1)0U){
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_16] = (U1)PNCREQCTL_REQ_ON;
    }
    else{
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_16] = (U1)PNCREQCTL_REQ_OFF;
    }

    u1_t_req = u1_ap_PNCREQDATA[PNCREQCTL_PNCID_40_47] & (U1)PNCREQCTL_PNCID_40_MASK;
    if(u1_t_req != (U1)0U){
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_40] = (U1)PNCREQCTL_REQ_ON;
    }
    else{
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_40] = (U1)PNCREQCTL_REQ_OFF;
    }

    u1_t_req = u1_ap_PNCREQDATA[PNCREQCTL_PNCID_40_47] & (U1)PNCREQCTL_PNCID_43_MASK;
    if(u1_t_req != (U1)0U){
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_43] = (U1)PNCREQCTL_REQ_ON;
    }
    else{
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_43] = (U1)PNCREQCTL_REQ_OFF;
    }

    u1_t_req = u1_ap_PNCREQDATA[PNCREQCTL_PNCID_40_47] & (U1)PNCREQCTL_PNCID_44_MASK;
    if(u1_t_req != (U1)0U){
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_44] = (U1)PNCREQCTL_REQ_ON;
    }
    else{
        u1_s_pncreqctl_req[PNCREQCTL_PNCID_44] = (U1)PNCREQCTL_REQ_OFF;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_PncReqctl_PartialNMSetReq(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PncReqctl_PartialNMSetReq(const U1* u1_ap_PNCREQDATA)
{
    static const U1    u1_sp_PNCREQCTL_WRH_HCH[PNCREQCTL_PNCID_REQNUM]= {
        (U1)OXCAN_WRH_HCH_0, /* PNC_16 */
        (U1)OXCAN_WRH_HCH_1, /* PNC_40 */
        (U1)OXCAN_WRH_HCH_2, /* PNC_43 */
        (U1)OXCAN_WRH_HCH_3  /* PNC_44 */
    };
    
    U1 u1_t_cnt;
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PNCREQCTL_PNCID_REQNUM; u1_t_cnt++){
        if(u1_ap_PNCREQDATA[u1_t_cnt] == (U1)PNCREQCTL_REQ_ON){
            vd_g_oXCANWrhReqHch(u1_sp_PNCREQCTL_WRH_HCH[u1_t_cnt], (U1)OXCAN_WRH_REQ_WK);
        }
        else{
            vd_g_oXCANWrhReqHch(u1_sp_PNCREQCTL_WRH_HCH[u1_t_cnt], (U1)OXCAN_WRH_REQ_SL);
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
/*  0.0.0    06/27/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
