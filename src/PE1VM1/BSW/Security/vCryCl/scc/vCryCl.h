/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  vCrypto Client                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VCRYCL_H
#define VCRYCL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCRYCL_H_MAJOR                         (1)
#define VCRYCL_H_MINOR                         (0)
#define VCRYCL_H_PATCH                         (0)

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "vCryCl_cfg_private.h"

/*--------------------------------------------------------------------------*/
/*  Literal Definitions                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

void    vd_g_vCryCl_Init(void);
void    vd_g_vCryCl_MainFunction(void);

void  vd_g_vCryCl_KeyUpdate(U4 u4_a_keyId, const U1* u1_ap_keyPtr, U4 u4_a_keyLength,
                            U4 u4_a_jobId, U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr);

void  vd_g_vCryCl_Encrypt(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                          U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr);
void  vd_g_vCryCl_Decrypt(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                          U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr);
void  vd_g_vCryCl_MacGenerate(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                              U1* u1_ap_macPtr, U4* u4_ap_macLengthPtr);
void  vd_g_vCryCl_MacVerify(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                            const U1* u1_ap_macPtr, const U4 u4_a_macLength, U1* u1_ap_verifyPtr);
void  vd_g_vCryCl_SignatureVerify(U4 u4_a_jobId, U1 u1_a_mode, const U1* u1_ap_dataPtr, U4 u4_a_dataLength,
                                  const U1* u1_ap_signaturePtr, U4 u4_a_signatureLength, U1* u1_ap_verifyPtr);

void  vd_g_vCryCl_JobRandomSeed(U4 u4_a_jobId, U4 u4_a_keyId, const U1* u1_ap_seedPtr, U4 u4_a_seedLength);
void  vd_g_vCryCl_RandomGenerate(U4 u4_a_jobId, U1* u1_ap_resultPtr, U4* u4_ap_resultLengthPtr);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/



#endif  /* VCRYCL_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vCryCl.c                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
