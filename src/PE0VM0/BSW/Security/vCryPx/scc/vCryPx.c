/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Virtual Crypto Proxy server                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCRYPX_C_MAJOR                            (1)
#define VCRYPX_C_MINOR                            (0)
#define VCRYPX_C_PATCH                            (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vCryPx_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VCRYPX_C_MAJOR != VCRYPX_H_MAJOR) || \
     (VCRYPX_C_MINOR != VCRYPX_H_MINOR) || \
     (VCRYPX_C_PATCH != VCRYPX_H_PATCH))
#error "vCryPx.c and vCryPx.h : source and header files are inconsistent!"
#endif

#if ((VCRYPX_C_MAJOR != VCRYPX_CFG_H_MAJOR) || \
     (VCRYPX_C_MINOR != VCRYPX_CFG_H_MINOR) || \
     (VCRYPX_C_PATCH != VCRYPX_CFG_H_PATCH))
#error "vCryPx.c and vCryPx_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* VCC buffer size : client to proxy */
#define VCRYPX_VCC_BUF_RX_NBYTE            (32U)
#define VCRYPX_VCC_BUF_RX_NWORD            (8U)

/* VCC buffer size : proxy to client */
#define VCRYPX_VCC_BUF_TX_NBYTE            (8U)
#define VCRYPX_VCC_BUF_TX_NWORD            (2U)

#define VCRYRX_VCC_RX_LP_MAX               (5U)

/* Data layout of the VCC buffer */
#define VCRYPX_VCC_BUF_RX_IDX_SERVICE      (0U)
#define VCRYPX_VCC_BUF_RX_IDX_ARG1         (1U)
#define VCRYPX_VCC_BUF_RX_IDX_ARG2         (2U)
#define VCRYPX_VCC_BUF_RX_IDX_ARG3         (3U)
#define VCRYPX_VCC_BUF_RX_IDX_ARG4         (4U)
#define VCRYPX_VCC_BUF_RX_IDX_ARG5         (5U)
#define VCRYPX_VCC_BUF_RX_IDX_ARG6         (6U)
#define VCRYPX_VCC_BUF_RX_IDX_ARG7         (7U)

#define VCRYPX_VCC_BUF_TX_IDX_RET          (0U)
#define VCRYPX_VCC_BUF_TX_IDX_ID1          (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef void       ( * FP_VCRYPX_SERVICE)(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* VCC local buffer */
static U4  u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_NWORD];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_vCryPx_VccSend(U4 u4_a_jobId, U1 u1_a_RSLT);
static void vd_s_vCryPx_KeyUpdate(void);
static void vd_s_vCryPx_KeyElementGet(void);
static void vd_s_vCryPx_Encrypt(void);
static void vd_s_vCryPx_MacGenerate(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const FP_VCRYPX_SERVICE fp_gp_vd_VCRYPX_SERVICE[] = {
    &vd_s_vCryPx_KeyUpdate       ,     /* #define VCRYPX_ID_SERVICE_KEYUPDATE         (0U) */
    &vd_s_vCryPx_KeyElementGet   ,     /* #define VCRYPX_ID_SERVICE_KEYELEMENTGET     (1U) */
    &vd_s_vCryPx_Encrypt         ,     /* #define VCRYPX_ID_SERVICE_ENCRYPT           (2U) */
    &vd_s_vCryPx_MacGenerate           /* #define VCRYPX_ID_SERVICE_MACGENERATE       (3U) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void  vd_g_vCryPx_Init(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_Init(void)
{
    U4                    u4_t_idx;

    for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYPX_VCC_BUF_RX_NWORD; u4_t_idx++) {
        u4_sp_vCryPx_VccBufRx[u4_t_idx] = (U4)0U;
    }
    
    (void)ehvm_vcc_clear_channel((U4)VCRYPX_VCC_ID_C2P);
    
}

/*===================================================================================================================================*/
/*  void  vd_g_vCryPx_MainFunction(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_MainFunction(void)
{
    U4                    u4_t_lpcnt;
    U4                    u4_t_serv_id;
    U4                    u4_t_idx;
    U4                    u4_t_nbyte;
    ehvm_std_return_t     u1_t_vcc_ret;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)VCRYRX_VCC_RX_LP_MAX; u4_t_lpcnt++){

        u1_t_vcc_ret = ehvm_vcc_receive(VCRYPX_VCC_ID_C2P,
                                        &u4_sp_vCryPx_VccBufRx[0],
                                        VCRYPX_VCC_BUF_RX_NBYTE,
                                        &u4_t_nbyte);
        if (u1_t_vcc_ret == E_EHVM_OK) {
            if(u4_t_nbyte == VCRYPX_VCC_BUF_RX_NBYTE){
                u4_t_serv_id = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_SERVICE];
                if(u4_t_serv_id < (U4)VCRYPX_ID_SERVICE_NUM){
                    fp_gp_vd_VCRYPX_SERVICE[u4_t_serv_id]();
                }
                for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYPX_VCC_BUF_RX_NWORD; u4_t_idx++) {
                    u4_sp_vCryPx_VccBufRx[u4_t_idx] = (U4)0U;
                }
            }
        }
        else if (u1_t_vcc_ret == E_EHVM_RECEIVE_OVERWRITE_OCCURS) {
            /* Nothing to do */
        }
        else{
            break;
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_VccSend(U4 u4_a_jobId, U1 u1_a_RSLT)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_VccSend(U4 u4_a_jobId, U1 u1_a_RSLT)
{
    U4                    u4_tp_word[VCRYPX_VCC_BUF_TX_NWORD];

    u4_tp_word[VCRYPX_VCC_BUF_TX_IDX_RET] = (U4)u1_a_RSLT;
    u4_tp_word[VCRYPX_VCC_BUF_TX_IDX_ID1] = u4_a_jobId;
    (void)ehvm_vcc_transmit(VCRYPX_VCC_ID_P2C,  &u4_tp_word[0], VCRYPX_VCC_BUF_TX_NBYTE);

}

/*===================================================================================================================================*/
/*  void  vd_g_vCryPx_CsmCallback_General(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_CsmCallback_General(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)
{
    vd_s_vCryPx_VccSend(u4_a_jobId, u1_a_RSLT);
}
/*===================================================================================================================================*/
/*  void  vd_g_vCryPx_CsmCallback_KeySetValid(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_CsmCallback_KeySetValid(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)
{
    vd_s_vCryPx_VccSend(u4_a_jobId, u1_a_RSLT);
}
/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_KeyUpdate(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_KeyUpdate(void)
{
    U4                    u4_t_key_id;
    U4                    u4_t_job_id;
    U1                    u1_t_csm_ret;

    u1_t_csm_ret = (U1)CRYPTO_E_BUSY;
    u4_t_job_id = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5];
    u4_t_key_id = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1];
    u1_t_csm_ret = Csm_KeyElementSet(u4_t_key_id,
                                     u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],              /* keyElementId  */
                                     (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],   /* keyPtr */
                                     u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4]);             /* keyLength */
    if(u1_t_csm_ret == (U1)E_OK){
        u1_t_csm_ret = Csm_JobKeySetValid(u4_t_job_id, u4_t_key_id);
    }

    if(u1_t_csm_ret != (U1)E_OK){
        vd_s_vCryPx_VccSend(u4_t_job_id, u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_KeyElementGet(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_KeyElementGet(void)
{

    U1                    u1_t_csm_ret;

    u1_t_csm_ret = Csm_KeyElementGet (u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],         /* keyId         */
                                      u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],         /* keyElementId  */
                                      (U1 *)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],   /* keyPtr        */
                                      (U4 *)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4]);  /* keyLengthPtr  */

    vd_s_vCryPx_VccSend(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5], u1_t_csm_ret);

}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_Encrypt(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_Encrypt(void)
{
    U1                    u1_t_csm_ret;

    u1_t_csm_ret = Csm_Encrypt(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],             /* jobId */
                               u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],             /* mode */
                               (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],  /* dataPtr */
                               u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4],             /* dataLength */
                               (U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5],        /* resultPtr */
                               (U4*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6] );      /* resultLengthPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        vd_s_vCryPx_VccSend(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_MacGenerate(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_MacGenerate(void)
{
    U1                    u1_t_csm_ret;

    u1_t_csm_ret = Csm_MacGenerate(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],             /* jobId */
                                   u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],             /* mode */
                                   (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],  /* dataPtr */
                                   u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4],             /* dataLength */
                                   (U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5],        /* macPtr */
                                   (U4*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6] );      /* macLengthPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        vd_s_vCryPx_VccSend(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
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
/*  1.0.0    03/10/2026  KN       New.                                                                                               */
/*                                                                                                                                   */
/*  * KN   = Kasumi Nakamura, DENSO CREATE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
