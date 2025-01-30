/* 1.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DENSO ICT1 Coding Style Standard Hmimm2c124n                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIMM2C124N_C_MAJOR                         (1)
#define HMIMM2C124N_C_MINOR                         (2)
#define HMIMM2C124N_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "hmimm2c124n_cfg_private.h"
/* Platform */
#include "oxcan.h"
#include "vardef.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIMM2C124N_C_MAJOR != HMIMM2C124N_H_MAJOR) || \
     (HMIMM2C124N_C_MINOR != HMIMM2C124N_H_MINOR) || \
     (HMIMM2C124N_C_PATCH != HMIMM2C124N_H_PATCH))
#error "hmimm2c124n.c and hmimm2c124n.h : source and header files are inconsistent!"
#endif

#if ((HMIMM2C124N_C_MAJOR != HMIMM2C124N_CFG_H_MAJOR) || \
     (HMIMM2C124N_C_MINOR != HMIMM2C124N_CFG_H_MINOR) || \
     (HMIMM2C124N_C_PATCH != HMIMM2C124N_CFG_H_PATCH))
#error "hmimm2c124n.c and HMIMM2C124N_cfg_private.h : source and header files are inconsistent!"
#endif


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIMM2C124N_STS_MASK                        (0x03U)
#define HMIMM2C124N_STS_DTA                         (0U)
#define HMIMM2C124N_FIRST_DTA                       (1U)
#define HMIMM2C124N_NORX_STS                        (1U)
#define HMIMM2C124N_TOUT_STS                        (1U)
#define HMIMM2C124N_1BITSHIFT                       (1U)
#define HMIMM2C124N_1BITMASK                        (0x01U)
#define MM_AVNMS73_CH1                              (MSG_AVNMS73_RXCH1)
#define HMIMM2C124N_NUM_CAN_BUF                     (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1  u1_idx;
    U2  u2_msgid;
}ST_HMI_MM_124N;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_ETH_DTA_NUM];
static U4   u4_sp_HMIMM2C124N_subsbuf[HMIMM2C124N_ETH_DTA_NUM];
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void   vd_s_HmiMM2C124NSubBusDataProcess(U4 * u4_ap_pdu_tx);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_HMI_MM_124N st_gp_HMI_MM124NMSG[] = {
        {   (U1)0U,     (U2)MM_AVNMS73_CH1  }    /*  000: 000:AVNMS73       */
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HMIMM2C124NInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMM2C124NInit(void)
{
    U4  u4_t_loop;    /* loop counter */

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMM2C124N_ETH_DTA_NUM; u4_t_loop++){
        u4_sp_HMIMM2C124N_ethbuf[u4_t_loop] = (U4)0U;
        u4_sp_HMIMM2C124N_subsbuf[u4_t_loop] = (U4)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_HMIMM2C124NMainTask(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMM2C124NMainTask(void)
{
    U4 u4_t_loop;    /* loop counter */
    U1 u1_t_sig;     /* demand signal */
    U1 u1_t_norx;    /* Ethernet not recieve status */
    U1 u1_t_tout;    /* Ethernet timeout status */
    U1 u1_t_mmcnnct_comsys;

    u1_t_norx = (U1)(u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_STS_DTA] & (U4)HMIMM2C124N_1BITMASK);
    u1_t_tout = (U1)((u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_STS_DTA] >> HMIMM2C124N_1BITSHIFT) & (U4)HMIMM2C124N_1BITMASK);

    if(u1_t_tout == (U1)HMIMM2C124N_TOUT_STS){    /* Ethernet STATUS is TimeOut */
        for(u4_t_loop = (U4)1U ; u4_t_loop < (U4)HMIMM2C124N_ETH_DTA_NUM ; u4_t_loop++){
            u4_sp_HMIMM2C124N_ethbuf[u4_t_loop] = (U4)0U;
        }
    } else if (u1_t_norx == (U1)HMIMM2C124N_NORX_STS) { /* Ethernet STATUS is NotRecieve */
        for(u4_t_loop = (U4)1U ; u4_t_loop < (U4)HMIMM2C124N_ETH_DTA_NUM ; u4_t_loop++){
            u4_sp_HMIMM2C124N_ethbuf[u4_t_loop] = (U4)0U;
        }
    }else{
        /* Do Nothing */
    }

    u1_t_mmcnnct_comsys = u1_g_VardefMmMthd();
    if((U1)VDF_MM_MTHD_MMSUBBUS == u1_t_mmcnnct_comsys)
    {
        vd_s_HmiMM2C124NSubBusDataProcess(&u4_sp_HMIMM2C124N_subsbuf[HMIMM2C124N_STS_DTA]);
    }
    else
    {
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_HMIMM2C124N_SIG_NUM ; u4_t_loop++){
            if(((st_gp_MM2C124N_SIGIF[u4_t_loop].fp_vd_send) != vdp_PTR_NA) &&
               ((st_gp_MM2C124N_SIGIF[u4_t_loop].fp_u1_read) != vdp_PTR_NA)){
                u1_t_sig = (st_gp_MM2C124N_SIGIF[u4_t_loop].fp_u1_read)((U1)u4_t_loop, &u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_FIRST_DTA]);
                (st_gp_MM2C124N_SIGIF[u4_t_loop].fp_vd_send)(u1_t_sig);
            }
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HMIMM2C124NDataPut(const U4 * u4_ap_REQ)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u4_ap_REQ   : MM2C118N address                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiMM2C124NDataPut(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {

        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMM2C124N_ETH_DTA_NUM ; u4_t_loop++){
            u4_sp_HMIMM2C124N_ethbuf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
        u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_STS_DTA] &= (U4)HMIMM2C124N_STS_MASK;
    }
}
/*===================================================================================================================================*/
/*  U1 u1_g_HmiMM2C124NSig(const U1 u1_a_SIG_IDX)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG_IDX  :  signal index number                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_HmiMM2C124NSig(const U1 u1_a_SIG_IDX)
{
    U1    u1_t_sig;       /* recieve signal */
    U1 u1_t_mmcnnct_comsys;

    u1_t_mmcnnct_comsys = u1_g_VardefMmMthd();
    switch(u1_a_SIG_IDX)
    {
        case HMI2C124N_SAFETY:
            if((U1)VDF_MM_MTHD_MMSUBBUS == u1_t_mmcnnct_comsys)
            {
                u1_t_sig = (st_gp_MM2C124N_SIGIF[HMI2C124N_SAFETY].fp_u1_read)((U1)HMI2C124N_SAFETY, &u4_sp_HMIMM2C124N_subsbuf[HMIMM2C124N_FIRST_DTA]);
            }
            else
            {
                u1_t_sig = (st_gp_MM2C124N_SIGIF[HMI2C124N_SAFETY].fp_u1_read)((U1)HMI2C124N_SAFETY, &u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_FIRST_DTA]);
            }
            break;
        case HMI2C124N_REPORT:
            if((U1)VDF_MM_MTHD_MMSUBBUS == u1_t_mmcnnct_comsys)
            {
                u1_t_sig = (st_gp_MM2C124N_SIGIF[HMI2C124N_REPORT].fp_u1_read)((U1)HMI2C124N_REPORT, &u4_sp_HMIMM2C124N_subsbuf[HMIMM2C124N_FIRST_DTA]);
            }
            else
            {
                u1_t_sig = (st_gp_MM2C124N_SIGIF[HMI2C124N_REPORT].fp_u1_read)((U1)HMI2C124N_REPORT, &u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_FIRST_DTA]);
            }
            break;
        default:
            u1_t_sig = (U1)0;
            break;
    }
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  U1 u1_g_HmiMM2C124NStsChk()                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/

U1 u1_g_HmiMM2C124NStsChk(void)
{
    U1 u1_t_norx;    /* Ethernet not recieve status */
    U1 u1_t_mmcnnct_comsys;

    u1_t_mmcnnct_comsys = u1_g_VardefMmMthd();
    if((U1)VDF_MM_MTHD_MMSUBBUS == u1_t_mmcnnct_comsys)
    {
        u1_t_norx = (U1)(u4_sp_HMIMM2C124N_subsbuf[HMIMM2C124N_STS_DTA] & (U4)HMIMM2C124N_1BITMASK);
    }
    else
    {
        u1_t_norx = (U1)(u4_sp_HMIMM2C124N_ethbuf[HMIMM2C124N_STS_DTA] & (U4)HMIMM2C124N_1BITMASK);
    }
    return(u1_t_norx);
}

/*===================================================================================================================================*/
/*  static void   vd_s_HmiMM2C118NSubBusDataProcess(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void   vd_s_HmiMM2C124NSubBusDataProcess(U4 * u4_ap_pdu_tx)
{
    U1                           u1_tp_sgnl[HMIMM2C124N_NUM_CAN_BUF];
    U2                           u2_t_lpcnt;
    U2                           u2_t_num_tbl;
    U4 *                         u4p_t_data;
    U2                           u2_t_msgidx;
    U4                           u4_t_loop;    /* loop counter */
    const ST_HMI_MM_124N*        st_tp_hmimm2c124frame;
    U1                           u1_t_sts;

    u2_t_num_tbl = (U2)(sizeof(st_gp_HMI_MM124NMSG) / sizeof(st_gp_HMI_MM124NMSG[0]));
    st_tp_hmimm2c124frame = st_gp_HMI_MM124NMSG;
    u4p_t_data   = &u4_ap_pdu_tx[HMIMM2C124N_FIRST_DTA];

    for(u2_t_lpcnt = (U2)0U ; u2_t_lpcnt < u2_t_num_tbl ; u2_t_lpcnt++){
        u2_t_msgidx = st_tp_hmimm2c124frame[u2_t_lpcnt].u2_msgid;
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMIMM2C124N_NUM_CAN_BUF ; u4_t_loop++){
            u1_tp_sgnl[u4_t_loop] = (U1)0U;
        }
        u1_t_sts = (U1)Com_GetIPDUStatus((PduIdType)u2_t_msgidx);
        u1_t_sts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

        (void)Com_ReadIPDU((PduIdType)u2_t_msgidx, &u1_tp_sgnl[0] );

        *u4p_t_data = (((U4)u1_tp_sgnl[3] <<  24U) |
                       ((U4)u1_tp_sgnl[2] <<  16U) |
                       ((U4)u1_tp_sgnl[1] <<   8U) |
                        (U4)u1_tp_sgnl[0]);
        u4p_t_data++;
        *u4p_t_data = (((U4)u1_tp_sgnl[7] <<  24U) |
                       ((U4)u1_tp_sgnl[6] <<  16U) |
                       ((U4)u1_tp_sgnl[5] <<   8U) |
                        (U4)u1_tp_sgnl[4]);
        u4p_t_data++;
    }

    u4_ap_pdu_tx[HMIMM2C124N_STS_DTA] = (U4)u1_t_sts;

}


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    03/16/2020  TH       New.                                                                                               */
/*  1.1.0    10/07/2020  TH       Change config for 800B CV-R.                                                                       */
/*  1.2.0    01/06/2021  TH       Add to dealing with timeout of Ethernet.                                                           */
/*                                                                                                                                   */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
