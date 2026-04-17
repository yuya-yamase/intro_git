/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXention of SEC : Intrusion Event Detection                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXSEC_IED_C_MAJOR                        (1U)
#define OXSEC_IED_C_MINOR                        (0U)
#define OXSEC_IED_C_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "IdsM.h"
#include "oxsec.h"
#include "oxsec_ied.h"
#include "oxcan_acex_def.h"
#include "oxdocan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXSEC_IED_C_MAJOR != OXSEC_H_MAJOR) || \
     (OXSEC_IED_C_MINOR != OXSEC_H_MINOR) || \
     (OXSEC_IED_C_PATCH != OXSEC_H_PATCH))
#error "oxsec_ied.c and oxsec.h : source and header files are inconsistent!"
#endif

#if ((OXSEC_IED_C_MAJOR != OXSEC_IED_H_MAJOR) || \
     (OXSEC_IED_C_MINOR != OXSEC_IED_H_MINOR) || \
     (OXSEC_IED_C_PATCH != OXSEC_IED_H_PATCH))
#error "oxsec_ied.c and oxsec_ied.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXSEC_IED_LEN_FV                         (7U)
#define OXSEC_IED_LEN_MAC_SEV                    (34U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                                 u1_sp_oxsec_ied_fv[OXCAN_OMA_NUM_REC][OXSEC_IED_LEN_FV]; 
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXSECIedInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*===================================================================================================================================*/
void    vd_g_oXSECIedInit(void)
{

    U4                           u4_t_loop_cnt;
    U4                           u4_t_loop_max;
    U1 *                         st_tp_fv;

    u4_t_loop_max = (U4)(OXCAN_OMA_NUM_REC * OXSEC_IED_LEN_FV);
    st_tp_fv = (U1 *)&u1_sp_oxsec_ied_fv[0];

    for(u4_t_loop_cnt = (U4)0U; u4_t_loop_cnt < u4_t_loop_max; u4_t_loop_cnt++){
        st_tp_fv[u4_t_loop_cnt] = (U1)0U;
    }
    return;
}

/*===================================================================================================================================*/
/*  void    vd_g_oXSECIedOmaRslt(const U2 u2_a_RX, const U1 u1_a_OMA_VR, const U4 u4_a_CANID, const U1* u1_ap_FV)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  OMA = On-Board MAC Authentication                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECIedOmaRslt(const U2 u2_a_RX, const U1 u1_a_OMA_VR, const U4 u4_a_CANID, const U1* u1_ap_FV)
{

    U4                           u4_t_loop_cnt;
    U1                           u1_tp_data[OXSEC_IED_LEN_MAC_SEV];
    
    
    /* #define SECOC_VERIFICATIONSUCCESS                ((SecOC_VerificationResultType)0x00)  */
    /* #define SECOC_VERIFICATIONFAILURE                ((SecOC_VerificationResultType)0x01)  */
    /* #define SECOC_FRESHNESSFAILURE                   ((SecOC_VerificationResultType)0x02)  */
    /* #define SECOC_AUTHENTICATIONBUILDFAILURE         ((SecOC_VerificationResultType)0x03)  */
    /* #define SECOC_NO_VERIFICATION                    ((SecOC_VerificationResultType)0x04)  */
    /* #define SECOC_VERIFICATIONFAILURE_OVERWRITTEN    ((SecOC_VerificationResultType)0x05)  */
    /* #define SECOC_AB_VERIFICATIONFAILURE_VERIFYSTART ((SecOC_VerificationResultType)0x40)  */
    if(u1_a_OMA_VR == (U1)0x00U){
        for(u4_t_loop_cnt = (U4)0U; u4_t_loop_cnt < (U4)OXSEC_IED_LEN_FV; u4_t_loop_cnt++){
            u1_sp_oxsec_ied_fv[u2_a_RX][u4_t_loop_cnt] = u1_ap_FV[u4_t_loop_cnt];
        }

    }else{

        /* TODO: Add Diag Mask */
        
        u1_tp_data[0] = (U1)0x01U;   /* Format Version: Fixed value 0x01 */

        (void)u1_g_oXDoCANAubIfTripcnt(&u1_tp_data[1]);   /* Diagnostic Time information :7bytes */
        (void)u1_g_oXDoCANAubIfGmt(&u1_tp_data[8]);       /* Diagnostic UTC information :6bytes */
        (void)u1_g_oXDoCANAubIfOdo(&u1_tp_data[14]);      /* Diagnostic vehicle odometer information :4bytes  */

        u1_tp_data[18] = (U1)((u4_a_CANID >> 8U) & (U1)0xFFU);     /* Message ID */
        u1_tp_data[19] = (U1)(u4_a_CANID & 0xFF);

        u1_tp_data[20] = u1_ap_FV[0];      /* Trip counter (latest value) */
        u1_tp_data[21] = u1_ap_FV[1];
        u1_tp_data[22] = u1_ap_FV[2];
        u1_tp_data[23] = u1_ap_FV[3];      /* Message counter (latest value) */
        u1_tp_data[24] = u1_ap_FV[4];
        u1_tp_data[25] = u1_ap_FV[5];
        u1_tp_data[26] = u1_ap_FV[6];

        u1_tp_data[27] = u1_sp_oxsec_ied_fv[u2_a_RX][0];  /* Trip counter (previously received value) */
        u1_tp_data[28] = u1_sp_oxsec_ied_fv[u2_a_RX][1];
        u1_tp_data[29] = u1_sp_oxsec_ied_fv[u2_a_RX][2];
        u1_tp_data[30] = u1_sp_oxsec_ied_fv[u2_a_RX][3];  /* Message counter (previously received value) */
        u1_tp_data[31] = u1_sp_oxsec_ied_fv[u2_a_RX][4];
        u1_tp_data[32] = u1_sp_oxsec_ied_fv[u2_a_RX][5];
        u1_tp_data[33] = u1_sp_oxsec_ied_fv[u2_a_RX][6];

        IdsM_SetSecurityEventWithContextData((U2)IdsMConf_IdsMEvent_Event_85A2, (const U1*)&u1_tp_data[0], (U2)OXSEC_IED_LEN_MAC_SEV);
    }
    
    return;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/10/2026  KT       New                                                                                                */
/*                                                                                                                                   */
/*  * KT   = Kazuya Takayama, DENSO CREATE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
