/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  NM Diag  Detection of abnormal global-ecu (Detection of excessive wakeup and sleep ng continuation)                              */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_NMGBL_C_MAJOR               (1U)
#define TYDOCAN_DTC_NMGBL_C_MINOR               (0U)
#define TYDOCAN_DTC_NMGBL_C_PATCH               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_dtc_nmgbl_cfg_private.h"
#include "tydocan_dtc_nmgbl.h"
#include "tydocan_sal.h"
#include "int_drv.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYDOCAN_DTC_NMGBL_C_MAJOR != TYDOCAN_DTC_NMGBL_H_MAJOR) || \
     (TYDOCAN_DTC_NMGBL_C_MINOR != TYDOCAN_DTC_NMGBL_H_MINOR) || \
     (TYDOCAN_DTC_NMGBL_C_PATCH != TYDOCAN_DTC_NMGBL_H_PATCH))
#error "tydocan_dtc_nmgbl.c and tydocan_dtc_nmgbl.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_NMGBL_C_MAJOR != TYDOCAN_DTC_NMGBL_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_NMGBL_C_MINOR != TYDOCAN_DTC_NMGBL_CFG_H_MINOR) || \
     (TYDOCAN_DTC_NMGBL_C_PATCH != TYDOCAN_DTC_NMGBL_CFG_H_PATCH))
#error "tydocan_dtc_nmgbl.c and tydocan_dtc_nmgbl_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_NMGBL_RXCNT_MAX                    (5U)

#define TYDC_NMGBL_CANID_NM_MIN                 (0x440U)
#define TYDC_NMGBL_CANID_NM_MAX                 (0x47FU)
#define TYDC_NMGBL_CANID_DIAG_MIN               (0x18000000UL)
#define TYDC_NMGBL_CANID_DIAG_MAX               (0x18FFFFFFUL)
/* #define TYDC_NMGBL_CANID_CTRL_WK_MIN            (0x000U) */
#define TYDC_NMGBL_CANID_CTRL_WK_MAX            (0x6FFU)    /* exclude NM_MIN to NM_MAX */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_tydc_dtc_nmgbl_mon_mode    __attribute__((section(".bss_BACK")));
static U4   u4_sp_tydc_dtc_nmgbl_cid_log[TYDC_DTC_NMGBL_CID_NUM][TYDC_NMGBL_RXCNT_MAX];
static U1   u1_sp_tydc_dtc_nmgbl_cid_cnt[TYDC_DTC_NMGBL_CID_NUM];
static U1   u1_sp_tydc_dtc_nmgbl_cid_ordr[TYDC_DTC_NMGBL_CID_NUM];

static U4   u4_s_tydc_dtc_nmgbl_cur_nm;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_TydcDtcNmGblChkRcvOrder(const U1 u1_t_TYPE);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblInit(const U1 u1_a_BR_INIT)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblInit(const U1 u1_a_BR_INIT)
{
    if(u1_a_BR_INIT == (U1)TRUE){
        u1_s_tydc_dtc_nmgbl_mon_mode = (U1)TYDC_DTC_NMGBL_RXMON_NONE;
    }

    vd_g_TyDoCANDtcNmGblCanidClear();

    vd_g_TyDoCANDtcNmGblWkInit(u1_a_BR_INIT);
    vd_g_TyDoCANDtcNmGblSngInit(u1_a_BR_INIT);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblMainTask(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblMainTask(void)
{
    vd_g_TyDoCANDtcNmGblWkMainTask();
    vd_g_TyDoCANDtcNmGblSngMainTask();
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcUdmDelNmGbl(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcUdmDelNmGbl(void)
{
    vd_g_TyDoCANDtcNmGblInit((U1)TRUE);
    return((U1)OXDC_DTC_UDM_DEL_OK);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblSetMonitorMode(const U1 u1_a_MODE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblSetMonitorMode(const U1 u1_a_MODE)
{
    u1_s_tydc_dtc_nmgbl_mon_mode = u1_a_MODE;
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmGblGetMonitorMode(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmGblGetMonitorMode(void)
{
    return(u1_s_tydc_dtc_nmgbl_mon_mode);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblCanidClear(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblCanidClear(void)
{
     U4        u4_t_gli;

     U4        u4_t_type;
     U4        u4_t_cnt;

     u4_t_gli = u4_g_IRQ_DI();

     for(u4_t_type = (U4)0U; u4_t_type < (U4)TYDC_DTC_NMGBL_CID_NUM; u4_t_type++){
          for(u4_t_cnt = (U4)0U; u4_t_cnt < (U4)TYDC_NMGBL_RXCNT_MAX; u4_t_cnt++){
               u4_sp_tydc_dtc_nmgbl_cid_log[u4_t_type][u4_t_cnt]  = (U4)0U;
          }

          u1_sp_tydc_dtc_nmgbl_cid_cnt[u4_t_type]  = (U1)0U;
          u1_sp_tydc_dtc_nmgbl_cid_ordr[u4_t_type] = (U1)0U;
     }

     u4_s_tydc_dtc_nmgbl_cur_nm  = (U4)0U;

     vd_g_IRQ_EI(u4_t_gli);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmGblGetNmLast(U4 * u4_ap_cid)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmGblGetNmLast(U4 * u4_ap_cid)
{
    U1 u1_t_ret;

    if(u4_s_tydc_dtc_nmgbl_cur_nm != (U4)0U){
        *u4_ap_cid = u4_s_tydc_dtc_nmgbl_cur_nm;
        u1_t_ret = (U1)TRUE;
    }
    else{
        *u4_ap_cid = (U1)0U;
        u1_t_ret = (U1)FALSE;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmGblGetCidByCnt(const U1 u1_a_TYPE, const U1 u1_a_CNT, U4 * u4_ap_cid)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmGblGetCidByCnt(const U1 u1_a_TYPE, const U1 u1_a_CNT, U4 * u4_ap_cid)
{
    U1 u1_t_ret;

    if(u1_sp_tydc_dtc_nmgbl_cid_cnt[u1_a_TYPE] > u1_a_CNT){
        *u4_ap_cid = u4_sp_tydc_dtc_nmgbl_cid_log[u1_a_TYPE][u1_a_CNT];
        u1_t_ret = (U1)TRUE;
    }
    else{
        *u4_ap_cid = (U1)0U;
        u1_t_ret = (U1)FALSE;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1        u1_g_TyDoCANDtcNmGblGetRcvOrdr(const U1 u1_a_TYPE)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmGblGetRcvOrdr(const U1 u1_a_TYPE)
{
    return(u1_sp_tydc_dtc_nmgbl_cid_ordr[u1_a_TYPE]);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmGblPreStoreMsg(const U1 u1_a_CH, const U4 u4_a_CANID)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmGblPreStoreMsg(const U1 u1_a_CH, const U4 u4_a_CANID)
{
    U4        u4_t_gli;
    U1        u1_t_cnt;

    if((u1_s_tydc_dtc_nmgbl_mon_mode != (U1)TYDC_DTC_NMGBL_RXMON_NONE) &&
       (u1_a_CH == u1_g_TYDC_DTC_NMGBL_CANIF_CH)){

        u4_t_gli = u4_g_IRQ_DI();

        /* Check NM Frame (excessive wakeup and sleep ng continuation) */
        if((u4_a_CANID <= (U4)TYDC_NMGBL_CANID_NM_MAX) &&
           (u4_a_CANID >= (U4)TYDC_NMGBL_CANID_NM_MIN)){

            u1_t_cnt = u1_sp_tydc_dtc_nmgbl_cid_cnt[TYDC_DTC_NMGBL_CID_NM];
            if(u1_t_cnt < (U1)TYDC_NMGBL_RXCNT_MAX){

                u4_sp_tydc_dtc_nmgbl_cid_log[TYDC_DTC_NMGBL_CID_NM][u1_t_cnt] = u4_a_CANID;
                u1_sp_tydc_dtc_nmgbl_cid_cnt[TYDC_DTC_NMGBL_CID_NM]++;
            }

            u4_s_tydc_dtc_nmgbl_cur_nm = u4_a_CANID;
            vd_s_TydcDtcNmGblChkRcvOrder((U1)TYDC_DTC_NMGBL_CID_NM);
        }
        /* Check DIAG Frame (excessive wakeup and sleep ng continuation) */
        else if((u4_a_CANID <= (U4)TYDC_NMGBL_CANID_DIAG_MAX) &&
                (u4_a_CANID >= (U4)TYDC_NMGBL_CANID_DIAG_MIN)){

            u1_t_cnt = u1_sp_tydc_dtc_nmgbl_cid_cnt[TYDC_DTC_NMGBL_CID_DI];
            if(u1_t_cnt < (U1)TYDC_NMGBL_RXCNT_MAX){

                u4_sp_tydc_dtc_nmgbl_cid_log[TYDC_DTC_NMGBL_CID_DI][u1_t_cnt] = u4_a_CANID;
                u1_sp_tydc_dtc_nmgbl_cid_cnt[TYDC_DTC_NMGBL_CID_DI]++;
            }

            vd_s_TydcDtcNmGblChkRcvOrder((U1)TYDC_DTC_NMGBL_CID_DI);
        }
        /* Check CONTROL Frame (excessive wakeup) */
        else if(u1_s_tydc_dtc_nmgbl_mon_mode == (U1)TYDC_DTC_NMGBL_RXMON_WK){

            if(u4_a_CANID  <= (U4)TYDC_NMGBL_CANID_CTRL_WK_MAX){
                u1_t_cnt = u1_sp_tydc_dtc_nmgbl_cid_cnt[TYDC_DTC_NMGBL_CID_CTL];
                if(u1_t_cnt < (U1)TYDC_NMGBL_RXCNT_MAX){

                    u4_sp_tydc_dtc_nmgbl_cid_log[TYDC_DTC_NMGBL_CID_CTL][u1_t_cnt] = u4_a_CANID;
                    u1_sp_tydc_dtc_nmgbl_cid_cnt[TYDC_DTC_NMGBL_CID_CTL]++;
                }

                vd_s_TydcDtcNmGblChkRcvOrder((U1)TYDC_DTC_NMGBL_CID_CTL);
            }
        }
        /* Check Special Event Frame (sleep ng continuation) */
        else{
            /* Do nothing (For 19PFv3, there is no "Message with MsgID" to target.) */
        }

        vd_g_IRQ_EI(u4_t_gli);
    }
}
/*===================================================================================================================================*/
/*  static void     vd_s_TydcDtcNmGblChkRcvOrder(const U1 u1_t_TYPE)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_TydcDtcNmGblChkRcvOrder(const U1 u1_t_TYPE)
{
    U4     u4_t_lpcnt;
    U1     u1_t_next;

    u1_t_next = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_DTC_NMGBL_CID_NUM; u4_t_lpcnt++){

        if(u1_sp_tydc_dtc_nmgbl_cid_ordr[u4_t_lpcnt] > u1_t_next){
            u1_t_next = u1_sp_tydc_dtc_nmgbl_cid_ordr[u4_t_lpcnt];
        }
    }

    if((u1_t_next                                <  (U1)TYDC_DTC_NMGBL_CID_NUM) &&
       (u1_sp_tydc_dtc_nmgbl_cid_ordr[u1_t_TYPE] == (U1)0U                    )){

        u1_sp_tydc_dtc_nmgbl_cid_ordr[u1_t_TYPE] = u1_t_next + (U1)1U;
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
/*  1.0.0     1/17/2024  TI       New.                                                                                               */
/*  1.0.1     7/04/2024  TI       tydocan_dtc_nmgbl_wk.c v1.0.0 -> v1.0.1                                                            */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
