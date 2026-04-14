/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Virtual Crypto Client                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCRYCL_C_MAJOR                         (1)
#define VCRYCL_C_MINOR                         (0)
#define VCRYCL_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* VCC buffer size  : client to proxy */
#define VCRYCL_VCC_BUF_TX_NBYTE           (32U)
#define VCRYCL_VCC_BUF_TX_NWORD           (8U)

/* VCC buffer size  : proxy to client */
#define VCRYCL_VCC_BUF_RX_NBYTE           (8U)
#define VCRYCL_VCC_BUF_RX_NWORD           (2U)

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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
/*  void    vd_g_vCryCl_Init(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_vCryCl_Init(void)
{
    (void)ehvm_vcc_clear_channel((U4)VCRYCL_VCC_ID_P2C);
}

/*===================================================================================================================================*/
/*  void    vd_g_vCryCl_MainFunction(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_vCryCl_MainFunction(void)
{
    U4                    u4_t_lpcnt;
    U4                    u4_t_nbyte;
    U4                    u4_tp_word[VCRYCL_VCC_BUF_RX_NWORD];
    ehvm_std_return_t     u1_t_vcc_ret;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)VCRYCL_VCC_RX_LP_MAX; u4_t_lpcnt++){
        u1_t_vcc_ret = ehvm_vcc_receive(VCRYCL_VCC_ID_P2C,
                                        &u4_tp_word[0],
                                        VCRYCL_VCC_BUF_RX_NBYTE,
                                        &u4_t_nbyte );
        if (u1_t_vcc_ret == E_EHVM_OK) {
            if(u4_t_nbyte == VCRYCL_VCC_BUF_RX_NBYTE){
                vd_g_vCryClCfg_Callback(u4_tp_word[VCRYCL_VCC_BUF_RX_IDX_ID1], (U1)u4_tp_word[VCRYCL_VCC_BUF_RX_IDX_RET]);
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
/*  void  vd_g_vCryCl_KeyUpdate(U4 u4_a_keyId, U4 u4_a_keyElementId, const U1* u1_ap_keyPtr, U4 u4_a_keyLength, U4 u4_a_jobId);           */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_KeyUpdate(U4 u4_a_keyId, U4 u4_a_keyElementId, const U1* u1_ap_keyPtr, U4 u4_a_keyLength, U4 u4_a_jobId)
{
    U4                    u4_tp_word[VCRYCL_VCC_BUF_TX_NWORD];

    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_KEYUPDATE;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_keyId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG2] = u4_a_keyElementId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_keyPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_keyLength;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG5] = u4_a_jobId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)0U;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            &u4_tp_word[0],
                            VCRYCL_VCC_BUF_TX_NBYTE);
}

/*========================================================================================================================================*/
/*  void  vd_g_vCryCl_KeyElementGet(U4 u4_a_keyId, U4 u4_a_keyElementId, U1* u1_ap_keyPtr, U4* u4_ap_keyLengthPtr, U4 u4_a_jobId)         */
/* -------------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                     */
/*  Return:         -                                                                                                                     */
/*========================================================================================================================================*/
void  vd_g_vCryCl_KeyElementGet(U4 u4_a_keyId, U4 u4_a_keyElementId, U1* u1_ap_keyPtr, U4* u4_ap_keyLengthPtr, U4 u4_a_jobId)
{
    U4                    u4_tp_word[VCRYCL_VCC_BUF_TX_NWORD];

    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_KEYELEMENTGET;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_keyId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG2] = u4_a_keyElementId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_keyPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG4] = (U4)u4_ap_keyLengthPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG5] = u4_a_jobId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)0U;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            &u4_tp_word[0],
                            VCRYCL_VCC_BUF_TX_NBYTE);
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
    U4                    u4_tp_word[VCRYCL_VCC_BUF_TX_NWORD];

    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_ENCRYPT;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_a_mode;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_dataPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_dataLength;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_resultPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)u4_ap_resultLengthPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            &u4_tp_word[0],
                            VCRYCL_VCC_BUF_TX_NBYTE);
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
    U4                    u4_tp_word[VCRYCL_VCC_BUF_TX_NWORD];

    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_SERVICE] = (U4)VCRYCL_ID_SERVICE_MACGENERATE;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG1] = u4_a_jobId;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG2] = (U4)u1_a_mode;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG3] = (U4)u1_ap_dataPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG4] = u4_a_dataLength;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG5] = (U4)u1_ap_macPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG6] = (U4)u4_ap_macLengthPtr;
    u4_tp_word[VCRYCL_VCC_BUF_TX_IDX_ARG7] = (U4)0U;
    (void)ehvm_vcc_transmit(VCRYCL_VCC_ID_C2P, 
                            &u4_tp_word[0],
                            VCRYCL_VCC_BUF_TX_NBYTE);
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
