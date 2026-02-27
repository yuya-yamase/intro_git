
/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  vCrypto Proxy                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCRYPX_C_MAJOR                            (1)
#define VCRYPX_C_MINOR                            (0)
#define VCRYPX_C_PATCH                            (0)

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
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
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* VCC buffer size [byte] : client to proxy */
#define VCRYPX_VCC_BUF_RX_SIZE             (32U)
/* VCC buffer size [byte] : proxy to client */
#define VCRYPX_VCC_BUF_TX_SIZE             (16U)

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
#define VCRYPX_VCC_BUF_TX_IDX_ID2          (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    U4               u4_keyid;        /* Required for key update */
    U4               u4_keyPtr;       /* Required for key update */
    U4               u4_keyLenPtr;    /* Required for key update */
} ST_VCRYPX_JOB_CONTEXT_TYPE;

typedef void       ( * FP_VCRYPX_SERVICE)(void);
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/* Service Function */
static void vd_s_vCryPx_KeyUpdate(void);
static void vd_s_vCryPx_Encrypt(void);
static void vd_s_vCryPx_Decrypt(void);
static void vd_s_vCryPx_MacGenerate(void);
static void vd_s_vCryPx_MacVerify(void);
static void vd_s_vCryPx_SignatureVerify(void);
static void vd_s_vCryPx_JobRandomSeed(void);
static void vd_s_vCryPx_RandomGenerate(void);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* Job context during processing */
static ST_VCRYPX_JOB_CONTEXT_TYPE st_gp_vCryPx_JobContext;

/* VCC local buffer */
static U4  u4_sp_vCryPx_VccBufTx[VCRYPX_VCC_BUF_TX_SIZE];
static U4  u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_SIZE];
static U4  u4_sp_vCryPx_VccBufRxLen;

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

const FP_VCRYPX_SERVICE fp_gp_vd_VCRYPX_SERVICE[] = {
    &vd_s_vCryPx_KeyUpdate       ,     /* #define VCRYPX_ID_SERVICE_KEYUPDATE         (0U) */
    &vd_s_vCryPx_Encrypt         ,     /* #define VCRYPX_ID_SERVICE_ENCRYPT           (1U) */
    &vd_s_vCryPx_Decrypt         ,     /* #define VCRYPX_ID_SERVICE_DECRYPT           (2U) */
    &vd_s_vCryPx_MacGenerate     ,     /* #define VCRYPX_ID_SERVICE_MACGENERATE       (3U) */
    &vd_s_vCryPx_MacVerify       ,     /* #define VCRYPX_ID_SERVICE_MACVERIFY         (4U) */
    &vd_s_vCryPx_SignatureVerify ,     /* #define VCRYPX_ID_SERVICE_SIGNATUREVERIFY   (5U) */
    &vd_s_vCryPx_JobRandomSeed   ,     /* #define VCRYPX_ID_SERVICE_JOBRANDOMSEED     (6U) */
    &vd_s_vCryPx_RandomGenerate        /* #define VCRYPX_ID_SERVICE_RANDOMGENERATE    (7U) */
};


/*===================================================================================================================================*/
/*  void  vd_g_vCryPx_Init(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_Init(void)
{
    U4 u4_t_idx;
    
    /* initialize variables */
    st_gp_vCryPx_JobContext.u4_keyid     = (U4)U4_MAX;
    st_gp_vCryPx_JobContext.u4_keyPtr    = (U4)0U;
    st_gp_vCryPx_JobContext.u4_keyLenPtr = (U4)0U;

    for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYPX_VCC_BUF_TX_SIZE; u4_t_idx++) {
        u4_sp_vCryPx_VccBufTx[u4_t_idx] = (U4)0U;
    }
    for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYPX_VCC_BUF_RX_SIZE; u4_t_idx++) {
        u4_sp_vCryPx_VccBufRx[u4_t_idx] = (U4)0U;
    }
    u4_sp_vCryPx_VccBufRxLen = (U4)0U;
}

/*===================================================================================================================================*/
/*  void  vd_g_vCryPx_MainFunction(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_MainFunction(void)
{
    U4 u4_t_lpcnt;
    ehvm_std_return_t u1_t_vcc_ret;
    U4 u4_t_serv_id;
    U4 u4_t_idx;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)VCRYRX_VCC_RX_LP_MAX; u4_t_lpcnt++){
        /* VCC receive Check */
        u1_t_vcc_ret = ehvm_vcc_receive(VCRYPX_VCC_ID_C2P,
                                        u4_sp_vCryPx_VccBufRx,
                                        VCRYPX_VCC_BUF_RX_SIZE,
                                        &u4_sp_vCryPx_VccBufRxLen );
        if (u1_t_vcc_ret == E_EHVM_OK) {
            /* VCC received */
            u4_t_serv_id = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_SERVICE];
            if(u4_t_serv_id < (U4)VCRYPX_ID_SERVICE_NUM){
                fp_gp_vd_VCRYPX_SERVICE[u4_t_serv_id]();
            }
            /* Buffer Clear */
            for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYPX_VCC_BUF_RX_SIZE; u4_t_idx++) {
                u4_sp_vCryPx_VccBufRx[u4_t_idx] = (U4)0U;
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
/*  void  vd_g_vCryPx_CsmCallback_General(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)              　                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_CsmCallback_General(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)
{
    /* Return the execution result to the client */
    u4_sp_vCryPx_VccBufTx[VCRYPX_VCC_BUF_TX_IDX_RET] = (U4)u1_a_RSLT;
    u4_sp_vCryPx_VccBufTx[VCRYPX_VCC_BUF_TX_IDX_ID1] = u4_a_jobId;
    u4_sp_vCryPx_VccBufTx[VCRYPX_VCC_BUF_TX_IDX_ID2] = (U4)0U;

    (void)ehvm_vcc_transmit(VCRYPX_VCC_ID_P2C, 
                            u4_sp_vCryPx_VccBufTx,
                            VCRYPX_VCC_BUF_TX_SIZE);
}
/*===================================================================================================================================*/
/*  void  vd_g_vCryPx_CsmCallback_KeySetValid(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_vCryPx_CsmCallback_KeySetValid(U4 u4_a_jobId, Crypto_ResultType u1_a_RSLT)
{
    U1    u1_t_csm_ret;


    u1_t_csm_ret = u1_a_RSLT;
    if(u1_a_RSLT == (U1)CRYPTO_E_VER_OK){
        u1_t_csm_ret = Csm_KeyElementGet (st_gp_vCryPx_JobContext.u4_keyid,
                                          u4_g_VCRYPX_KEY_GET_ELEM_ID,
                                          (U1 *)st_gp_vCryPx_JobContext.u4_keyPtr,
                                          (U4 *)st_gp_vCryPx_JobContext.u4_keyLenPtr);
    }

    /* Return the execution result to the client */
    u4_sp_vCryPx_VccBufTx[VCRYPX_VCC_BUF_TX_IDX_RET] = (U4)u1_t_csm_ret;
    u4_sp_vCryPx_VccBufTx[VCRYPX_VCC_BUF_TX_IDX_ID1] = u4_a_jobId;
    u4_sp_vCryPx_VccBufTx[VCRYPX_VCC_BUF_TX_IDX_ID2] = (U4)0U;

    (void)ehvm_vcc_transmit(VCRYPX_VCC_ID_P2C, 
                            u4_sp_vCryPx_VccBufTx,
                            VCRYPX_VCC_BUF_TX_SIZE);
    /* Clear the running job context */
    st_gp_vCryPx_JobContext.u4_keyid     = (U4)U4_MAX;
    st_gp_vCryPx_JobContext.u4_keyPtr    = (U4)0U;
    st_gp_vCryPx_JobContext.u4_keyLenPtr = (U4)0U;
}
/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_KeyUpdate(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_KeyUpdate(void)
{
    U4 u4_t_key_id;
    U4 u4_t_job_id;
    U1 u1_t_csm_ret;

    u1_t_csm_ret = (U1)CRYPTO_E_BUSY;
    if(st_gp_vCryPx_JobContext.u4_keyid == (U4)U4_MAX){
        u4_t_key_id = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1];
        u4_t_job_id = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4];
        u1_t_csm_ret = Csm_KeyElementSet(u4_t_key_id,
                                         u4_g_VCRYPX_KEY_SET_ELEM_ID,
                                         (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],
                                         u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3]);
        if(u1_t_csm_ret == (U1)E_OK){
            u1_t_csm_ret = Csm_JobKeySetValid(u4_t_job_id, u4_t_key_id);
            if(u1_t_csm_ret == (U1)E_OK){
                st_gp_vCryPx_JobContext.u4_keyid     = u4_t_key_id;
                st_gp_vCryPx_JobContext.u4_keyPtr    = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5];
                st_gp_vCryPx_JobContext.u4_keyLenPtr = u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6];
            }
        }
    }

    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_KeySetValid(u4_t_job_id, u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_Encrypt(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_Encrypt(void)
{
    U1 u1_t_csm_ret;

    u1_t_csm_ret = Csm_Encrypt(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],             /* jobId */
                               u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],             /* mode */
                               (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],  /* dataPtr */
                               u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4],             /* dataLength */
                               (U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5],        /* resultPtr */
                               (U4*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6] );      /* resultLengthPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_General(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_Decrypt(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_Decrypt(void)
{
    U1 u1_t_csm_ret;

    u1_t_csm_ret = Csm_Decrypt(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],             /* jobId */
                               u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],             /* mode */
                               (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],  /* dataPtr */
                               u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4],             /* dataLength */
                               (U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5],        /* resultPtr */
                               (U4*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6] );      /* resultLengthPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_General(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
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
    U1 u1_t_csm_ret;

    u1_t_csm_ret = Csm_MacGenerate(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],             /* jobId */
                                   u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],             /* mode */
                                   (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],  /* dataPtr */
                                   u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4],             /* dataLength */
                                   (U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5],        /* macPtr */
                                   (U4*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6] );      /* macLengthPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_General(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_MacVerify(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_MacVerify(void)
{
    U1 u1_t_csm_ret;

    u1_t_csm_ret = Csm_MacVerify(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],                             /* jobId */
                                 u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],                             /* mode */
                                 (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],                  /* dataPtr */
                                 u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4],                             /* dataLength */
                                 (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5],                  /* macPtr */
                                 u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6],                             /* macLengthPtr */
                                 (Crypto_VerifyResultType*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG7] ); /* verifyPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_General(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_SignatureVerify(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_SignatureVerify(void)
{
    U1 u1_t_csm_ret;

    u1_t_csm_ret = Csm_SignatureVerify(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],                             /* jobId */
                                       u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],                             /* mode */
                                       (U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],                        /* dataPtr */
                                       u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4],                             /* dataLength */
                                       (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG5],                  /* signaturePtr */
                                       u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG6],                             /* signatureLength */
                                       (Crypto_VerifyResultType*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG7] ); /* verifyPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_General(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_JobRandomSeed(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_JobRandomSeed(void)
{
    U1 u1_t_csm_ret;

    u1_t_csm_ret = Csm_JobRandomSeed(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],              /* jobId */
                                     u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],              /* keyId */
                                     (const U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3],   /* seedPtr */
                                     u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG4] );            /* seedLength */
    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_General(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_vCryPx_RandomGenerate(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_vCryPx_RandomGenerate(void)
{
    U1 u1_t_csm_ret;

    u1_t_csm_ret = Csm_RandomGenerate(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1],              /* jobId */
                                      (U1*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG2],         /* resultPtr */
                                      (U4*)u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG3] );       /* resultLengthPtr */
    if(u1_t_csm_ret != (U1)E_OK){
        /* Csm Error */
        vd_g_vCryPx_CsmCallback_General(u4_sp_vCryPx_VccBufRx[VCRYPX_VCC_BUF_RX_IDX_ARG1], u1_t_csm_ret);
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
/*  1.0.0    12/01/2025  KN       New.                                                                                               */
/*                                                                                                                                   */
/*  * KN   = Kasumi Nakamura, DENSO                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/