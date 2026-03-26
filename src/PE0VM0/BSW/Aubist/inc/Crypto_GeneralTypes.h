/* Crypto_GeneralTypes_h_v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crypto_GeneralTypes/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_GENERALTYPES_H
#define CRYPTO_GENERALTYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Rte_Csm_Type.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* SWS_Csm_01047 */
/* Crypto_AlgorithmFamilyType */
#define CRYPTO_ALGOFAM_NOT_SET                  ((Crypto_AlgorithmFamilyType)0x00U)
#define CRYPTO_ALGOFAM_SHA1                     ((Crypto_AlgorithmFamilyType)0x01U)
#define CRYPTO_ALGOFAM_SHA2_224                 ((Crypto_AlgorithmFamilyType)0x02U)
#define CRYPTO_ALGOFAM_SHA2_256                 ((Crypto_AlgorithmFamilyType)0x03U)
#define CRYPTO_ALGOFAM_SHA2_384                 ((Crypto_AlgorithmFamilyType)0x04U)
#define CRYPTO_ALGOFAM_SHA2_512                 ((Crypto_AlgorithmFamilyType)0x05U)
#define CRYPTO_ALGOFAM_SHA2_512_224             ((Crypto_AlgorithmFamilyType)0x06U)
#define CRYPTO_ALGOFAM_SHA2_512_256             ((Crypto_AlgorithmFamilyType)0x07U)
#define CRYPTO_ALGOFAM_SHA3_224                 ((Crypto_AlgorithmFamilyType)0x08U)
#define CRYPTO_ALGOFAM_SHA3_256                 ((Crypto_AlgorithmFamilyType)0x09U)
#define CRYPTO_ALGOFAM_SHA3_384                 ((Crypto_AlgorithmFamilyType)0x0AU)
#define CRYPTO_ALGOFAM_SHA3_512                 ((Crypto_AlgorithmFamilyType)0x0BU)
#define CRYPTO_ALGOFAM_SHAKE128                 ((Crypto_AlgorithmFamilyType)0x0CU)
#define CRYPTO_ALGOFAM_SHAKE256                 ((Crypto_AlgorithmFamilyType)0x0DU)
#define CRYPTO_ALGOFAM_RIPEMD160                ((Crypto_AlgorithmFamilyType)0x0EU)
#define CRYPTO_ALGOFAM_BLAKE_1_256              ((Crypto_AlgorithmFamilyType)0x0FU)
#define CRYPTO_ALGOFAM_BLAKE_1_512              ((Crypto_AlgorithmFamilyType)0x10U)
#define CRYPTO_ALGOFAM_BLAKE_2s_256             ((Crypto_AlgorithmFamilyType)0x11U)
#define CRYPTO_ALGOFAM_BLAKE_2s_512             ((Crypto_AlgorithmFamilyType)0x12U)
#define CRYPTO_ALGOFAM_3DES                     ((Crypto_AlgorithmFamilyType)0x13U)
#define CRYPTO_ALGOFAM_AES                      ((Crypto_AlgorithmFamilyType)0x14U)
#define CRYPTO_ALGOFAM_CHACHA                   ((Crypto_AlgorithmFamilyType)0x15U)
#define CRYPTO_ALGOFAM_RSA                      ((Crypto_AlgorithmFamilyType)0x16U)
#define CRYPTO_ALGOFAM_ED25519                  ((Crypto_AlgorithmFamilyType)0x17U)
#define CRYPTO_ALGOFAM_BRAINPOOL                ((Crypto_AlgorithmFamilyType)0x18U)
#define CRYPTO_ALGOFAM_ECCNIST                  ((Crypto_AlgorithmFamilyType)0x19U)
#define CRYPTO_ALGOFAM_RNG                      ((Crypto_AlgorithmFamilyType)0x1BU)
#define CRYPTO_ALGOFAM_SIPHASH                  ((Crypto_AlgorithmFamilyType)0x1CU)
#define CRYPTO_ALGOFAM_ECCANSI                  ((Crypto_AlgorithmFamilyType)0x1EU)
#define CRYPTO_ALGOFAM_ECCSEC                   ((Crypto_AlgorithmFamilyType)0x1FU)
#define CRYPTO_ALGOFAM_DRBG                     ((Crypto_AlgorithmFamilyType)0x20U)
#define CRYPTO_ALGOFAM_FIPS186                  ((Crypto_AlgorithmFamilyType)0x21U)
#define CRYPTO_ALGOFAM_PADDING_PKCS7            ((Crypto_AlgorithmFamilyType)0x22U)
#define CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS     ((Crypto_AlgorithmFamilyType)0x23U)
#define CRYPTO_ALGOFAM_PBKDF2                   ((Crypto_AlgorithmFamilyType)0x24U)
#define CRYPTO_ALGOFAM_KDFX963                  ((Crypto_AlgorithmFamilyType)0x25U)
#define CRYPTO_ALGOFAM_DH                       ((Crypto_AlgorithmFamilyType)0x26U)
#define CRYPTO_ALGOFAM_CUSTOM                   ((Crypto_AlgorithmFamilyType)0xFFU)

/* SWS_Csm_01048 */
/* Crypto_AlgorithmModeType */
#define CRYPTO_ALGOMODE_NOT_SET                 ((Crypto_AlgorithmModeType)0x00U)
#define CRYPTO_ALGOMODE_ECB                     ((Crypto_AlgorithmModeType)0x01U)
#define CRYPTO_ALGOMODE_CBC                     ((Crypto_AlgorithmModeType)0x02U)
#define CRYPTO_ALGOMODE_CFB                     ((Crypto_AlgorithmModeType)0x03U)
#define CRYPTO_ALGOMODE_OFB                     ((Crypto_AlgorithmModeType)0x04U)
#define CRYPTO_ALGOMODE_CTR                     ((Crypto_AlgorithmModeType)0x05U)
#define CRYPTO_ALGOMODE_GCM                     ((Crypto_AlgorithmModeType)0x06U)
#define CRYPTO_ALGOMODE_XTS                     ((Crypto_AlgorithmModeType)0x07U)
#define CRYPTO_ALGOMODE_RSAES_OAEP              ((Crypto_AlgorithmModeType)0x08U)
#define CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5        ((Crypto_AlgorithmModeType)0x09U)
#define CRYPTO_ALGOMODE_RSASSA_PSS              ((Crypto_AlgorithmModeType)0x0AU)
#define CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5       ((Crypto_AlgorithmModeType)0x0BU)
#define CRYPTO_ALGOMODE_8ROUNDS                 ((Crypto_AlgorithmModeType)0x0CU)
#define CRYPTO_ALGOMODE_12ROUNDS                ((Crypto_AlgorithmModeType)0x0DU)
#define CRYPTO_ALGOMODE_20ROUNDS                ((Crypto_AlgorithmModeType)0x0EU)
#define CRYPTO_ALGOMODE_HMAC                    ((Crypto_AlgorithmModeType)0x0FU)
#define CRYPTO_ALGOMODE_CMAC                    ((Crypto_AlgorithmModeType)0x10U)
#define CRYPTO_ALGOMODE_GMAC                    ((Crypto_AlgorithmModeType)0x11U)
#define CRYPTO_ALGOMODE_CTRDRBG                 ((Crypto_AlgorithmModeType)0x12U)
#define CRYPTO_ALGOMODE_SIPHASH_2_4             ((Crypto_AlgorithmModeType)0x13U)
#define CRYPTO_ALGOMODE_SIPHASH_4_8             ((Crypto_AlgorithmModeType)0x14U)
#define CRYPTO_ALGOMODE_PXXXR1                  ((Crypto_AlgorithmModeType)0x15U)
#define CRYPTO_ALGOMODE_CUSTOM                  ((Crypto_AlgorithmModeType)0xFFU)

/* SWS_Csm_91024 */
/* Crypto_InputOutputRedirectionConfigType */
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT    ((Crypto_InputOutputRedirectionConfigType)0x01U)
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT  ((Crypto_InputOutputRedirectionConfigType)0x02U)
#define CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT   ((Crypto_InputOutputRedirectionConfigType)0x04U)
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT   ((Crypto_InputOutputRedirectionConfigType)0x10U)
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT ((Crypto_InputOutputRedirectionConfigType)0x20U)

/* SWS_Csm_01028 */
/* Crypto_JobStateType */
#define CRYPTO_JOBSTATE_IDLE                    ((Crypto_JobStateType)0x00U)
#define CRYPTO_JOBSTATE_ACTIVE                  ((Crypto_JobStateType)0x01U)

/* SWS_Csm_01031 */
/* Crypto_ServiceInfoType */
#define CRYPTO_HASH                             ((Crypto_ServiceInfoType)0x00U)
#define CRYPTO_MACGENERATE                      ((Crypto_ServiceInfoType)0x01U)
#define CRYPTO_MACVERIFY                        ((Crypto_ServiceInfoType)0x02U)
#define CRYPTO_ENCRYPT                          ((Crypto_ServiceInfoType)0x03U)
#define CRYPTO_DECRYPT                          ((Crypto_ServiceInfoType)0x04U)
#define CRYPTO_AEADENCRYPT                      ((Crypto_ServiceInfoType)0x05U)
#define CRYPTO_AEADDECRYPT                      ((Crypto_ServiceInfoType)0x06U)
#define CRYPTO_SIGNATUREGENERATE                ((Crypto_ServiceInfoType)0x07U)
#define CRYPTO_SIGNATUREVERIFY                  ((Crypto_ServiceInfoType)0x08U)
#define CRYPTO_RANDOMGENERATE                   ((Crypto_ServiceInfoType)0x0BU)
#define CRYPTO_RANDOMSEED                       ((Crypto_ServiceInfoType)0x0CU)
#define CRYPTO_KEYGENERATE                      ((Crypto_ServiceInfoType)0x0DU)
#define CRYPTO_KEYDERIVE                        ((Crypto_ServiceInfoType)0x0EU)
#define CRYPTO_KEYEXCHANGECALCPUBVAL            ((Crypto_ServiceInfoType)0x0FU)
#define CRYPTO_KEYEXCHANGECALCSECRET            ((Crypto_ServiceInfoType)0x10U)
#define CRYPTO_KEYSETVALID                      ((Crypto_ServiceInfoType)0x13U)

/* SWS_Csm_01049 */
/* Crypto_ProcessingType */
#define CRYPTO_PROCESSING_ASYNC                 ((Crypto_ProcessingType)0x00U)
#define CRYPTO_PROCESSING_SYNC                  ((Crypto_ProcessingType)0x01U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8       Crypto_AlgorithmFamilyType;
typedef uint8       Crypto_AlgorithmModeType;
typedef uint8       Crypto_InputOutputRedirectionConfigType;
typedef uint8       Crypto_JobStateType;
typedef uint8       Crypto_ServiceInfoType;
typedef uint8       Crypto_ProcessingType;


/* SWS_Csm_01009 */
typedef struct
{
    P2CONST(uint8, TYPEDEF, CSM_APPL_DATA)                    inputPtr;
    uint32                                                    inputLength;
    P2CONST(uint8, TYPEDEF, CSM_APPL_DATA)                    secondaryInputPtr;
    uint32                                                    secondaryInputLength;
    P2CONST(uint8, TYPEDEF, CSM_APPL_DATA)                    tertiaryInputPtr;
    uint32                                                    tertiaryInputLength;
    P2VAR(uint8, TYPEDEF, CSM_APPL_DATA)                      outputPtr;
    P2VAR(uint32, TYPEDEF, CSM_APPL_DATA)                     outputLengthPtr;
    P2VAR(uint8, TYPEDEF, CSM_APPL_DATA)                      secondaryOutputPtr;
    P2VAR(uint32, TYPEDEF, CSM_APPL_DATA)                     secondaryOutputLengthPtr;
    P2VAR(Crypto_VerifyResultType, TYPEDEF, CSM_APPL_DATA)    verifyPtr;
    Crypto_OperationModeType                                    mode;
    uint32                                                      cryIfKeyId;
    uint32                                                      targetCryIfKeyId;
} Crypto_JobPrimitiveInputOutputType;

/* SWS_Csm_01010 */
typedef struct
{
    const uint32                    jobId;
    const uint32                    jobPriority;
} Crypto_JobInfoType;

/* SWS_Csm_01008 */
typedef struct
{
    Crypto_AlgorithmFamilyType      family;
    Crypto_AlgorithmFamilyType      secondaryFamily;
    uint32                          keyLength;
    Crypto_AlgorithmModeType        mode;
} Crypto_AlgorithmInfoType;

/* SWS_Csm_01011 */
typedef struct
{
    const uint32                    resultLength;
    const Crypto_ServiceInfoType    service;
    const Crypto_AlgorithmInfoType  algorithm;
} Crypto_PrimitiveInfoType;

/* SWS_Csm_01012 */
typedef struct
{
    P2CONST(Crypto_PrimitiveInfoType, TYPEDEF, CSM_APPL_DATA)   primitiveInfo;
    uint32                                                      cryIfKeyId;
    Crypto_ProcessingType                                       processingType;
} Crypto_JobPrimitiveInfoType;

/* SWS_Csm_91026 */
typedef struct
{
    uint8                           redirectionConfig;
    uint32                          inputKeyId;
    uint32                          inputKeyElementId;
    uint32                          secondaryInputKeyId;
    uint32                          secondaryInputKeyElementId;
    uint32                          tertiaryInputKeyId;
    uint32                          tertiaryInputKeyElementId;
    uint32                          outputKeyId;
    uint32                          outputKeyElementId;
    uint32                          secondaryOutputKeyId;
    uint32                          secondaryOutputKeyElementId;
} Crypto_JobRedirectionInfoType;

/* SWS_Csm_01013 */
typedef struct
{
    uint32                                                          jobId;
    Crypto_JobStateType                                             jobState;
    Crypto_JobPrimitiveInputOutputType                              jobPrimitiveInputOutput;
    P2CONST(Crypto_JobPrimitiveInfoType, TYPEDEF, CSM_APPL_DATA)  jobPrimitiveInfo;
    P2CONST(Crypto_JobInfoType, TYPEDEF, CSM_APPL_DATA)           jobInfo;
    uint32                                                          cryptoKeyId;
    P2VAR(Crypto_JobRedirectionInfoType, TYPEDEF, CSM_SHARED_VAR_NO_INIT) jobRedirectionInfoRef;
    uint32                                                          targetCryptoKeyId;
} Crypto_JobType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* CRYPTO_GENERALTYPES_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
