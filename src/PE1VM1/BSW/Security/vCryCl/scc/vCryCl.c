/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  vCrypto Client                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCRYCL_C_MAJOR                         (1)
#define VCRYCL_C_MINOR                         (0)
#define VCRYCL_C_PATCH                         (0)

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "vCryCl_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VCRYCL_C_MAJOR != VCRYCL_H_MAJOR) || \
     (VCRYCL_C_MINOR != VCRYCL_H_MINOR) || \
     (VCRYCL_C_PATCH != VCRYCL_H_PATCH))
#error "vCryCl.c and vCryCl.h : source and header files are inconsistent!"
#endif

#if ((VCRYCL_C_MAJOR != VCRYCL_CFG_H_MAJOR) || \
     (VCRYCL_C_MINOR != VCRYCL_CFG_H_MINOR) || \
     (VCRYCL_C_PATCH != VCRYCL_CFG_H_PATCH))
#error "vCryCl.c and vCryCl_cfg_private.h : source and header files are inconsistent!"
#endif


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* VCC buffer size [byte] : client to proxy */
#define VCRYCL_VCC_BUF_TX_SIZE            (32U)
/* VCC buffer size [byte] : proxy to client */
#define VCRYCL_VCC_BUF_RX_SIZE            (16U)

#define VCRYCL_VCC_RX_LP_MAX              (5U)

/* Data layout of the VCC buffer */
#define VCRYCL_VCC_BUF_TX_IDX_SERVICE     (0U)
#define VCRYCL_VCC_BUF_TX_IDX_ARG1        (1U)
#define VCRYCL_VCC_BUF_TX_IDX_ARG2        (2U)
#define VCRYCL_VCC_BUF_TX_IDX_ARG3        (3U)
#define VCRYCL_VCC_BUF_TX_IDX_ARG4        (4U)
#define VCRYCL_VCC_BUF_TX_IDX_ARG5        (5U)
#define VCRYCL_VCC_BUF_TX_IDX_ARG6        (6U)
#define VCRYCL_VCC_BUF_TX_IDX_ARG7        (7U)

#define VCRYCL_VCC_BUF_RX_IDX_RET         (0U)
#define VCRYCL_VCC_BUF_RX_IDX_ID1         (1U)
#define VCRYCL_VCC_BUF_RX_IDX_ID2         (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* VCC local buffer */
static U4 u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_SIZE];
static U4 u4_sp_vCryCl_VccBufRx[VCRYCL_VCC_BUF_RX_SIZE];
static U4 u4_s_vCryCl_VccBufRxLen;


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_vCryCl_Init(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_vCryCl_Init(void)
{
    U4 u4_t_idx;
    
    /* initialize variables */
    for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYCL_VCC_BUF_TX_SIZE; u4_t_idx++) {
        u4_sp_vCryCl_VccBufTx[u4_t_idx] = (U4)0U;
    }
    for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYCL_VCC_BUF_RX_SIZE; u4_t_idx++) {
        u4_sp_vCryCl_VccBufRx[u4_t_idx] = (U4)0U;
    }
    u4_s_vCryCl_VccBufRxLen = (U4)0U;

}

/*===================================================================================================================================*/
/*  void    vd_g_vCryCl_MainFunction(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_vCryCl_MainFunction(void)
{
    U4 u4_t_lpcnt;
    U4 u4_t_idx;
    ehvm_std_return_t u1_t_vcc_ret;
    U4 u4_t_job;
    U1 u1_t_csm_ret;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)VCRYCL_VCC_RX_LP_MAX; u4_t_lpcnt++){
        /* VCC receive Check */
        u1_t_vcc_ret = ehvm_vcc_receive(VCRYCL_VCC_ID_P2C,
                                        u4_sp_vCryCl_VccBufRx,
                                        VCRYCL_VCC_BUF_RX_SIZE,
                                        &u4_s_vCryCl_VccBufRxLen );
        if (u1_t_vcc_ret == E_EHVM_OK) {
            u1_t_csm_ret = (U1)u4_sp_vCryCl_VccBufRx[VCRYCL_VCC_BUF_RX_IDX_RET];
            u4_t_job     = u4_sp_vCryCl_VccBufRx[VCRYCL_VCC_BUF_RX_IDX_ID1];
            /* Call Back */
            vd_g_vCryClCfg_Callback(u4_t_job, u1_t_csm_ret);
            /* Buffer Clear */
            for (u4_t_idx = (U4)0U; u4_t_idx < (U4)VCRYCL_VCC_BUF_RX_SIZE; u4_t_idx++) {
                u4_sp_vCryCl_VccBufRx[u4_t_idx] = (U4)0U;
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

/*========================================================================================================================================*/
/*  void  vd_g_vCryCl_KeyUpdate(U4 u4_a_keyId, const U1* u1_ap_keyPtr, U4 u4_a_keyLength,                                                 */
/*                              U4 u4_a_jobId, U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)                                            */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_KeyUpdate(U4 u4_a_keyId, const U1* u1_ap_keyPtr, U4 u4_a_keyLength, 
                            U4 u4_a_jobId, U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_KEYUPDATE;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_keyId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_ap_keyPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = u4_a_keyLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_resultPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)u4_ap_resultLengthPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
}

/*========================================================================================================================================*/
/* void  vd_g_vCryCl_Encrypt(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,                                    */
/*                           U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)                                                              */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_Encrypt(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                          U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_ENCRYPT;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_a_mode;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_dataPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_dataLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_resultPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)u4_ap_resultLengthPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
}
/*========================================================================================================================================*/
/* void  vd_g_vCryCl_Decrypt(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,                                    */
/*                           U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)                                                              */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_Decrypt(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                          U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_DECRYPT;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_a_mode;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_dataPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_dataLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_resultPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)u4_ap_resultLengthPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
}

/*========================================================================================================================================*/
/* void  vd_g_vCryCl_MacGenerate(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,                                */
/*                               U1* u1_ap_macPtr, U4* u4_ap_macLengthPtr)                                                                */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_MacGenerate(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                              U1* u1_ap_macPtr, U4* u4_ap_macLengthPtr)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_MACGENERATE;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_a_mode;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_dataPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_dataLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_macPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)u4_ap_macLengthPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
}

/*========================================================================================================================================*/
/* void  vd_g_vCryCl_MacVerify(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,                                  */
/*                             const U1* u1_ap_macPtr, const U4 u4_a_macLength, U1* u1_ap_verifyPtr)                                      */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_MacVerify(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                            const U1* u1_ap_macPtr, const U4 u4_a_macLength, U1* u1_ap_verifyPtr)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_MACVERIFY;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_a_mode;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_dataPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_dataLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_macPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = u4_a_macLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)u1_ap_verifyPtr;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
}



/*========================================================================================================================================*/
/* void  vd_g_vCryCl_SignatureVerify(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,                            */
/*                                   const U1* u1_ap_signaturePtr, U4 u4_a_signatureLength, U1* u1_ap_verifyPtr);                         */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_SignatureVerify(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                                  const U1* u1_ap_signaturePtr, U4 u4_a_signatureLength, U1* u1_ap_verifyPtr)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_SIGNATUREVERIFY;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_a_mode;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_dataPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_dataLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_signaturePtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = u4_a_signatureLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)u1_ap_verifyPtr;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
}

/*====================================================================================================================================*/
/* void  vd_g_vCryCl_JobRandomSeed(U4 u4_a_jobId, U4 u4_a_keyId, const U1* u1_ap_seedPtr, U4 u4_a_seedLength)                         */
/* ---------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                 */
/*  Return:         -                                                                                                                 */
/*====================================================================================================================================*/
void  vd_g_vCryCl_JobRandomSeed(U4 u4_a_jobId, U4 u4_a_keyId, const U1* u1_ap_seedPtr, U4 u4_a_seedLength)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_JOBRANDOMSEED;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = u4_a_keyId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_seedPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_seedLength;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)0U;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)0U;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
}

/*====================================================================================================================================*/
/* void  vd_g_vCryCl_RandomGenerate(U4 u4_a_jobId, U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)                                    */
/* ---------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                 */
/*  Return:         -                                                                                                                 */
/*====================================================================================================================================*/
void  vd_g_vCryCl_RandomGenerate(U4 u4_a_jobId, U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr)
{
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_RANDOMGENERATE;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_ap_resultPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u4_ap_resultLengthPtr;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG4] = (U4)0U;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)0U;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)0U;
    u4_sp_vCryCl_VccBufTx[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            u4_sp_vCryCl_VccBufTx,
                            VCRYCL_VCC_BUF_TX_SIZE);
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
