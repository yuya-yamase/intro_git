/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  inter-Virtual Machine CAN Bus status SHaring                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVCBSH_C_MAJOR                           (1)
#define IVCBSH_C_MINOR                           (0)
#define IVCBSH_C_PATCH                           (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ivcbsh_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((IVCBSH_C_MAJOR != IVCBSH_H_MAJOR) || \
     (IVCBSH_C_MINOR != IVCBSH_H_MINOR) || \
     (IVCBSH_C_PATCH != IVCBSH_H_PATCH))
#error "ivcbsh.c and ivcbsh.h : source and header files are inconsistent!"
#endif

#if ((IVCBSH_C_MAJOR != IVCBSH_CFG_H_MAJOR) || \
     (IVCBSH_C_MINOR != IVCBSH_CFG_H_MINOR) || \
     (IVCBSH_C_PATCH != IVCBSH_CFG_H_PATCH))
#error "ivcbsh.c and ivcbsh_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVCBSH_SYCTIM                           (5U)    /* 5ms */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVCBSH_TIM_NOCONNECT                    (5000U / IVCBSH_SYCTIM)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct
{
    U2              u2_fail;
    U4              u4_wri_pre;
    U4              u4_tim;         /* No Connect Timer */
}ST_IVCBSH_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_IVCBSH_STS    st_sp_ivcbsh_sts[IVCBSH_SYS_NUM_NET];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_iVCBshInitPrm(const U4 u4_a_POS, const U2 u2_a_CLRFAIL);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_iVCBshInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_iVCBshInit(void)
{
    U4      u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)IVCBSH_SYS_NUM_NET; u4_t_lpcnt++){
        st_sp_ivcbsh_sts[u4_t_lpcnt].u4_wri_pre = (U4)IVCBSH_STS_ACTIVE;
        vd_s_iVCBshInitPrm(u4_t_lpcnt, (U2)U2_MAX);
    }
}
/*===================================================================================================================================*/
/*  static void     vd_s_iVCBshInitPrm(const U4 u1_a_POS)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_iVCBshInitPrm(const U4 u4_a_POS, const U2 u2_a_CLRFAIL)
{
    if(u4_a_POS < (U4)IVCBSH_SYS_NUM_NET){
        st_sp_ivcbsh_sts[u4_a_POS].u2_fail  &=  ~(u2_a_CLRFAIL);
        st_sp_ivcbsh_sts[u4_a_POS].u4_tim   =   (U4)U4_MAX;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_iVCBshMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_iVCBshMainTask(void)
{
    static U2   u2_st_NWORD     = (U2)1U;

    U4      u4_t_lpcnt;
    U2      u2_t_can;
    U1      u1_t_txlog;
    U1      u1_t_rxlog;
    U4      u4_t_wri;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)IVCBSH_SYS_NUM_NET; u4_t_lpcnt++){
        u2_t_can    = (U2)IVCBSH_ERR_NONE;
        u4_t_wri    = st_sp_ivcbsh_sts[u4_t_lpcnt].u4_wri_pre;

        /* Active-Fail Judge */
        /* ----------------------------------------------------------------------------------------------------- */
        /* Attention :                                                                                           */
        /* ----------------------------------------------------------------------------------------------------- */
        /* The return of BswM_Can_GetChFailStatus is intentionally discarded because the API returns E_NOT_OK    */
        /* only if the 1st parameter "NetworkHandleType network" is greater than or equal to BSW_COM_CFG_CHNUM.  */
        /* ----------------------------------------------------------------------------------------------------- */
        (void)BswM_Can_GetChFailStatus(st_sp_IVCBSH_PRM[u4_t_lpcnt].u1_COM_CH, &u2_t_can);
        u1_t_txlog  = CanSM_GetTxConfirmationState(st_sp_IVCBSH_PRM[u4_t_lpcnt].u1_COM_CH);
        u1_t_rxlog  = CanSM_GetRxIndicationState(st_sp_IVCBSH_PRM[u4_t_lpcnt].u1_COM_CH);

        /* Fail Timer Start */
        if(((u2_t_can & (U2)(IVCBSH_ERR_BUSOFF | IVCBSH_ERR_SNDLOCK_USER)) != (U2)0U) &&
           (st_sp_ivcbsh_sts[u4_t_lpcnt].u4_tim == (U4)U4_MAX)){
            st_sp_ivcbsh_sts[u4_t_lpcnt].u4_tim = (U4)0U;
        }
        else{
            /* do nothing */
        }

        /* Failure Status Update */
        if(u2_t_can != (U2)IVCBSH_ERR_NONE){
            st_sp_ivcbsh_sts[u4_t_lpcnt].u2_fail    |=  u2_t_can;

            /* When the CAN bus status becomes BUS-OFF, CAN communication is no longer possible. */
            /* Therefore, CAN connection abnormalities are also detected as errors. */
            if(u2_t_can == (U2)IVCBSH_ERR_BUSOFF){
                st_sp_ivcbsh_sts[u4_t_lpcnt].u2_fail    |=  (U2)IVCBSH_ERR_SNDLOCK_USER;
            }
        }
        else{
            /* do nothing */
        }

        /* Failure Causes Judge and Abnormal recovery detection */
        if((st_sp_ivcbsh_sts[u4_t_lpcnt].u2_fail & (U2)IVCBSH_ERR_REGCHECK) != (U2)0U){
            /* Register Stuck */
            u4_t_wri    |=  (U4)IVCBSH_STS_REGSTUCK;
        }
        else{
            /* do nothing */
        }
        if((st_sp_ivcbsh_sts[u4_t_lpcnt].u2_fail   & (U2)IVCBSH_ERR_BUSOFF) != (U2)0U){
            /* Bus-off */
            if((u1_t_txlog == (U1)CANSM_TX_RX_NOTIFICATION) || 
               (u1_t_rxlog == (U1)CANSM_TX_RX_NOTIFICATION)){
                /* Normal Recovery */
                u4_t_wri    &=  ~(U4)(IVCBSH_STS_BUSOFF);
                vd_s_iVCBshInitPrm(u4_t_lpcnt, (U2)IVCBSH_ERR_BUSOFF);
            }
            else{
                u4_t_wri    |=  (U4)IVCBSH_STS_BUSOFF;
            }
        }
        else{
            /* do nothing */
        }
        if(((st_sp_ivcbsh_sts[u4_t_lpcnt].u2_fail & (U2)IVCBSH_ERR_SNDLOCK_USER) != (U2)0U) &&
           (st_sp_ivcbsh_sts[u4_t_lpcnt].u4_tim >= (U4)IVCBSH_TIM_NOCONNECT)){
            /* CAN Bus Disconnected */
            if((u1_t_txlog == (U1)CANSM_TX_RX_NOTIFICATION) || 
               (u1_t_rxlog == (U1)CANSM_TX_RX_NOTIFICATION)){
                /* Normal Recovery */
                u4_t_wri    &=  ~(U4)(IVCBSH_STS_NOCONNECT);
                vd_s_iVCBshInitPrm(u4_t_lpcnt, (U2)IVCBSH_ERR_SNDLOCK_USER);
            }
            else{
                u4_t_wri    |=  (U4)IVCBSH_STS_NOCONNECT;
                st_sp_ivcbsh_sts[u4_t_lpcnt].u4_tim = (U4)U4_MAX;
            }
        }
        else{
            /* do nothing */
        }

        /* inter-VM Sharing */
        if(st_sp_ivcbsh_sts[u4_t_lpcnt].u4_wri_pre != u4_t_wri){
            vd_g_iVDshWribyDid(st_sp_IVCBSH_PRM[u4_t_lpcnt].u2_IVDSH_ID, &u4_t_wri, u2_st_NWORD);
            st_sp_ivcbsh_sts[u4_t_lpcnt].u4_wri_pre = u4_t_wri;
        }
        else{
            /* do nothing */
        }

        /* Fail Timer Count */
        if(st_sp_ivcbsh_sts[u4_t_lpcnt].u4_tim  < (U4)U4_MAX){
            st_sp_ivcbsh_sts[u4_t_lpcnt].u4_tim++;
        }
        else{
            /* do nothing */
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
/*  1.0.0     7/07/2025  TN       New.                                                                                               */
/*  1.0.1     9/15/2025  TN       Change: Detects CAN connection abnormality as an error when CAN bus status is BUS OFF.             */
/*                                                                                                                                   */
/*  * TN   = Tetsu Naruse, DensoTechno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
