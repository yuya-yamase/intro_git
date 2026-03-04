/* CryIf_c_v2-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CryIf/CODE                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <CryIf.h>
#include <Csm.h>
#include <Csm_Cfg_Fixed.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYIF_START_SEC_CODE
#include <CryIf_MemMap.h>

static FUNC(Std_ReturnType, CRYIF_CODE) CryIf_SetRedirection
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) ptJob,
    uint16 u2CryptoIndex
);

static FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CheckKeyId
(
    uint32 u4KeyId,
    uint16 u2CryptoIndex
);

#define CRYIF_STOP_SEC_CODE
#include <CryIf_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRYIF_START_SEC_CODE
#include <CryIf_MemMap.h>

/****************************************************************************/
/* Function Name | CryIf_Init                                               */
/* Description   | Initializes the CryIf module.                            */
/* Preconditions | -                                                        */
/* Parameters    | configPtr : Pointer to a selected                        */
/*               |             configuration structure. No use.             */
/* Return Value  | -                                                        */
/* Notes         | SWS_CryIf_91000                                          */
/****************************************************************************/
FUNC(void, CRYIF_CODE) CryIf_Init
(
    P2CONST(CryIf_ConfigType, AUTOMATIC, CRYIF_APPL_DATA) configPtr
)
{
    return;
}

/****************************************************************************/
/* Function Name | CryIf_GetVersionInfo                                     */
/* Description   | Returns the version information of CryIf module.         */
/* Preconditions | -                                                        */
/* Parameters    | versioninfo : Pointer to where to store the version      */
/*               |               information of this module.                */
/* Return Value  | -                                                        */
/* Notes         | SWS_CryIf_91001                                          */
/****************************************************************************/
FUNC(void, CRYIF_CODE) CryIf_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CRYIF_APPL_DATA) versioninfo
)
{
    boolean b_VersionInfoApi = CryIf_Cfg_bVersionInfoApi;

    if ( b_VersionInfoApi == (boolean)TRUE )
    {
        if( versioninfo != NULL_PTR )
        {
            versioninfo->vendorID         = (uint16)CRYIF_VENDOR_ID;
            versioninfo->moduleID         = (uint16)CRYIF_MODULE_ID;
            versioninfo->sw_major_version = (uint8)CRYIF_SW_MAJOR_VERSION;
            versioninfo->sw_minor_version = (uint8)CRYIF_SW_MINOR_VERSION;
            versioninfo->sw_patch_version = (uint8)CRYIF_SW_PATCH_VERSION;
        }
    }/* CryIf_Cfg_bVersionInfoApi  valid */

    return;
}

/****************************************************************************/
/* Function Name | CryIf_ProcessJob                                         */
/* Description   | Pass the job received from Csm to the Crypto Driver      */
/*               | Object specified in the config.                          */
/* Preconditions | -                                                        */
/* Parameters    | channelId : Holds the identifier of the crypto channel.  */
/*               | job       : Pointer to the configuration of the job.     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK      : Request successful                           */
/*               | E_NOT_OK  : Request failed                               */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_VALID : the key is not valid            */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : a key element has the       */
/*               |                              wrong size                  */
/*               | CRYPTO_E_KEY_READ_FAIL :  key element extraction is      */
/*               |                           not allowed                    */
/*               | CRYPTO_E_KEY_WRITE_FAIL : the writing access failed      */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : the key is not available    */
/*               | CRYPTO_E_JOB_CANCELED : the synchronous Job has been     */
/*               |                         canceled                         */
/*               | CRYPTO_E_KEY_EMPTY : uninitialized source key element    */
/*               | CRYPTO_E_ENTROPY_EXHAUSTED :  Entropy is depleted        */
/* Notes         | SWS_CryIf_91003                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_ProcessJob
(
    uint32 channelId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    Crypto_ServiceInfoType ud_Service;
    Std_ReturnType ud_SetRedirectionResult;
    uint32 u4_KeyId;
    uint32 u4_TargetKeyId;
    uint16 u2_CryptoIndex;
    uint32 u4_ObjectId;

    if( channelId < CryIf_Cfg_stChannel.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stChannel.ptConfig[channelId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptProcessJob != NULL_PTR )
        {
            if( ( job != NULL_PTR )                                &&
                ( job->jobPrimitiveInfo != NULL_PTR )              &&
                ( job->jobPrimitiveInfo->primitiveInfo != NULL_PTR ) )
            {
                ud_SetRedirectionResult = CryIf_SetRedirection( job, u2_CryptoIndex );

                if( ud_SetRedirectionResult == (Std_ReturnType)E_OK )
                {
                    ud_Service = job->jobPrimitiveInfo->primitiveInfo->service;

                    if( ( ud_Service == CRYPTO_KEYSETVALID )           ||
                        ( ud_Service == CRYPTO_RANDOMSEED )            ||
                        ( ud_Service == CRYPTO_KEYGENERATE )           ||
                        ( ud_Service == CRYPTO_KEYEXCHANGECALCPUBVAL ) ||
                        ( ud_Service == CRYPTO_KEYEXCHANGECALCSECRET ) )
                    {
                        u4_KeyId = job->jobPrimitiveInputOutput.cryIfKeyId;

                        if( u4_KeyId < CryIf_Cfg_stKey.u4ConfigNum )
                        {
                            if( u2_CryptoIndex == (uint16)CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoIndex )
                            {
                                job->cryptoKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;

                                ud_Ret = E_OK;
                            }
                        }
                    }
                    else if( ud_Service == CRYPTO_KEYDERIVE )
                    {
                        u4_KeyId = job->jobPrimitiveInputOutput.cryIfKeyId;
                        u4_TargetKeyId = job->jobPrimitiveInputOutput.targetCryIfKeyId;

                        if( ( u4_KeyId < CryIf_Cfg_stKey.u4ConfigNum )     &&
                            ( u4_TargetKeyId < CryIf_Cfg_stKey.u4ConfigNum ) )
                        {
                            if( ( u2_CryptoIndex == (uint16)CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoIndex )     &&
                                ( u2_CryptoIndex == (uint16)CryIf_Cfg_stKey.ptConfig[u4_TargetKeyId].u4CryptoIndex ) )
                            {
                                job->cryptoKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;
                                job->targetCryptoKeyId = CryIf_Cfg_stKey.ptConfig[u4_TargetKeyId].u4CryptoKeyId;

                                ud_Ret = E_OK;
                            }
                        }
                    }
                    else if( ( ud_Service == CRYPTO_MACGENERATE )       ||
                             ( ud_Service == CRYPTO_MACVERIFY )         ||
                             ( ud_Service == CRYPTO_ENCRYPT )           ||
                             ( ud_Service == CRYPTO_DECRYPT )           ||
                             ( ud_Service == CRYPTO_AEADENCRYPT )       ||
                             ( ud_Service == CRYPTO_AEADDECRYPT )       ||
                             ( ud_Service == CRYPTO_SIGNATUREGENERATE ) ||
                             ( ud_Service == CRYPTO_SIGNATUREVERIFY ) )
                    {
                        u4_KeyId = job->jobPrimitiveInfo->cryIfKeyId;

                        if( u4_KeyId < CryIf_Cfg_stKey.u4ConfigNum )
                        {
                            if( u2_CryptoIndex == (uint16)CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoIndex )
                            {
                                job->cryptoKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;

                                ud_Ret = E_OK;
                            }
                        }
                    }
                    else if( ( ud_Service == CRYPTO_HASH )         ||
                             ( ud_Service == CRYPTO_RANDOMGENERATE ) )
                    {
                        ud_Ret = E_OK;
                    }
                    else
                    {
                        /* No Processing */
                    }

                    if( ud_Ret == (Std_ReturnType)E_OK )
                    {
                        u4_ObjectId = CryIf_Cfg_stChannel.ptConfig[channelId].u4ObjectId;

                        ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptProcessJob( u4_ObjectId, job );
                    }
                }
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_CancelJob                                          */
/* Description   | Call the job cancel function of Crypto Driver Object     */
/*               | specified in the config.                                 */
/* Preconditions | -                                                        */
/* Parameters    | channelId : Holds the identifier of the crypto channel.  */
/*               | job       : Pointer to the configuration of the job.     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK      : Request successful, job has been removed     */
/*               | E_NOT_OK  : Request failed, job could not be removed     */
/*               | CRYPTO_E_JOB_CANCELED : The job has been cancelled       */
/*               |                         but is still processed.          */
/*               |                         No results will be returned to   */
/*               |                         the application.                 */
/* Notes         | SWS_CryIf_91014                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CancelJob
(
    uint32 channelId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_ObjectId;

    if( channelId < CryIf_Cfg_stChannel.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stChannel.ptConfig[channelId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptCancelJob != NULL_PTR )
        {
            u4_ObjectId = CryIf_Cfg_stChannel.ptConfig[channelId].u4ObjectId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptCancelJob( u4_ObjectId, job );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_CallbackNotification                               */
/* Description   | Notify Csm of the completion of the request,             */
/*               | including the result of the cryptographic operation.     */
/* Preconditions | -                                                        */
/* Parameters    | job    : Holds a pointer to the job, which has finished. */
/*               | result : Contains the result of                          */
/*               |          the cryptographic operation.                    */
/* Return Value  | -                                                        */
/* Notes         | SWS_CryIf_91013                                          */
/****************************************************************************/
FUNC(void, CRYIF_CODE) CryIf_CallbackNotification
(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job,
    Crypto_ResultType result
)
{
    Csm_CallbackNotification( job, result );

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | CryIf_SetRedirection                                     */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptJob  :                                                 */
/*               | u2CryptoIndex :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Successful or no redirection key conversion.*/
/*               | E_NOT_OK   : KeyId is out of range.                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYIF_CODE) CryIf_SetRedirection
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) ptJob,
    uint16 u2CryptoIndex
)
{
    Std_ReturnType ud_Ret = E_OK;
    Std_ReturnType ud_CheckKeyIdResult;
    uint32 u4_KeyId;

    if( ptJob->jobRedirectionInfoRef != NULL_PTR )
    {
        if( ( ptJob->jobRedirectionInfoRef->redirectionConfig & CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT ) != (uint8)0U )
        {
            u4_KeyId = ptJob->jobRedirectionInfoRef->inputKeyId;

            ud_CheckKeyIdResult = CryIf_CheckKeyId( u4_KeyId, u2CryptoIndex );

            if( ud_CheckKeyIdResult == (Std_ReturnType)E_OK )
            {
                ptJob->jobRedirectionInfoRef->inputKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;
            }
            else
            {
                ud_Ret = E_NOT_OK;
            }
        }

        if( ( ud_Ret == (Std_ReturnType)E_OK ) &&
            ( ( ptJob->jobRedirectionInfoRef->redirectionConfig & CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT ) != (uint8)0U ) )
        {
            u4_KeyId = ptJob->jobRedirectionInfoRef->secondaryInputKeyId;

            ud_CheckKeyIdResult = CryIf_CheckKeyId( u4_KeyId, u2CryptoIndex );

            if( ud_CheckKeyIdResult == (Std_ReturnType)E_OK )
            {
                ptJob->jobRedirectionInfoRef->secondaryInputKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;
            }
            else
            {
                ud_Ret = E_NOT_OK;
            }
        }

        if( ( ud_Ret == (Std_ReturnType)E_OK ) &&
            ( ( ptJob->jobRedirectionInfoRef->redirectionConfig & CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT ) != (uint8)0U ) )
        {
            u4_KeyId = ptJob->jobRedirectionInfoRef->tertiaryInputKeyId;

            ud_CheckKeyIdResult = CryIf_CheckKeyId( u4_KeyId, u2CryptoIndex );

            if( ud_CheckKeyIdResult == (Std_ReturnType)E_OK )
            {
                ptJob->jobRedirectionInfoRef->tertiaryInputKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;
            }
            else
            {
                ud_Ret = E_NOT_OK;
            }
        }

        if( ( ud_Ret == (Std_ReturnType)E_OK ) &&
            ( ( ptJob->jobRedirectionInfoRef->redirectionConfig & CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT ) != (uint8)0U ) )
        {
            u4_KeyId = ptJob->jobRedirectionInfoRef->outputKeyId;

            ud_CheckKeyIdResult = CryIf_CheckKeyId( u4_KeyId, u2CryptoIndex );

            if( ud_CheckKeyIdResult == (Std_ReturnType)E_OK )
            {
                ptJob->jobRedirectionInfoRef->outputKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;
            }
            else
            {
                ud_Ret = E_NOT_OK;
            }
        }

        if( ( ud_Ret == (Std_ReturnType)E_OK ) &&
            ( ( ptJob->jobRedirectionInfoRef->redirectionConfig & CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT ) != (uint8)0U ) )
        {
            u4_KeyId = ptJob->jobRedirectionInfoRef->secondaryOutputKeyId;

            ud_CheckKeyIdResult = CryIf_CheckKeyId( u4_KeyId, u2CryptoIndex );

            if( ud_CheckKeyIdResult == (Std_ReturnType)E_OK )
            {
                ptJob->jobRedirectionInfoRef->secondaryOutputKeyId = CryIf_Cfg_stKey.ptConfig[u4_KeyId].u4CryptoKeyId;
            }
            else
            {
                ud_Ret = E_NOT_OK;
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_CheckKeyId                                         */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | u4KeyId :                                                */
/*               | u2CryptoIndex :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Successful.                                 */
/*               | E_NOT_OK   : KeyId is out of range.                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CheckKeyId
(
    uint32 u4KeyId,
    uint16 u2CryptoIndex
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;

    if( u4KeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        if( u2CryptoIndex == (uint16)CryIf_Cfg_stKey.ptConfig[u4KeyId].u4CryptoIndex )
        {
            ud_Ret = E_OK;
        }
    }

    return ud_Ret;
}

#define CRYIF_STOP_SEC_CODE
#include <CryIf_MemMap.h>

/****************************************************************************/
/*  History                                                                 */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
