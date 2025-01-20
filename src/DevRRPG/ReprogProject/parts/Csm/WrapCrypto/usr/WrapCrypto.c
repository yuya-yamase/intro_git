/* WrapCrypto_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WrapCrypto/CODE                                             */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <WrapCrypto.h>
#include <Csm.h>
#include <SchM_Csm.h>
#include "WrapCrypto_Local.h"

/*===== Sample ===============================================================*/
#include <SchM_Crypto_83_sw.h>
#include <Sys.h>
#include <EcuM.h>
#include <WdgM.h>
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define WRAPCRYPTO_MASK_NEST_MAX                ((uint8)32U)

#define WRAPCRYPTO_API_ID_CSM_ERRORCALLOUT      ((uint8)0x01U)
#define WRAPCRYPTO_API_ID_CSM_TIMEOUTCALLOUT    ((uint8)0x02U)
#define WRAPCRYPTO_API_ID_SCHM_ENTER            ((uint8)0x03U)
#define WRAPCRYPTO_API_ID_SCHM_EXIT             ((uint8)0x04U)
#if (WRAPCRYPTO_USE_CRYPTO_SW_83 == STD_ON)
#define WRAPCRYPTO_API_ID_CRYPTO_ERRORCALLOUT   ((uint8)0x81U)
#endif

#if (WRAPCRYPTO_USE_CRYPTO_SW_83_SIGVERIFY == STD_ON)
#define WRAPCRYPTO_RSA_PUBLIC_EXPONENT          ((uint32)0x00010001UL)

#define WRAPCRYPTO_KEYMATERIAL_SIZE             ((uint8)12U)
#define WRAPCRYPTO_KEYMATERIAL_POS_0            ((uint8)0U)
#define WRAPCRYPTO_KEYMATERIAL_POS_1            ((uint8)1U)
#define WRAPCRYPTO_KEYMATERIAL_POS_2            ((uint8)2U)
#define WRAPCRYPTO_KEYMATERIAL_POS_3            ((uint8)3U)
#define WRAPCRYPTO_KEYMATERIAL_POS_4            ((uint8)4U)
#define WRAPCRYPTO_KEYMATERIAL_POS_5            ((uint8)5U)
#define WRAPCRYPTO_KEYMATERIAL_POS_6            ((uint8)6U)
#define WRAPCRYPTO_KEYMATERIAL_POS_7            ((uint8)7U)
#define WRAPCRYPTO_KEYMATERIAL_POS_8            ((uint8)8U)
#define WRAPCRYPTO_KEYMATERIAL_POS_9            ((uint8)9U)
#define WRAPCRYPTO_KEYMATERIAL_POS_10           ((uint8)10U)
#define WRAPCRYPTO_KEYMATERIAL_POS_11           ((uint8)11U)

#define WRAPCRYPTO_BIT_SHIFT_8                  ((uint8)8U)
#define WRAPCRYPTO_BIT_SHIFT_16                 ((uint8)16U)
#define WRAPCRYPTO_BIT_SHIFT_24                 ((uint8)24U)
#define WRAPCRYPTO_BIT_MASK_8                   ((uint32)0x000000FFUL)
#define WRAPCRYPTO_BIT_MASK_16                  ((uint32)0x0000FFFFUL)
#endif

#if (WRAPCRYPTO_USE_CRYPTO_SW_83 == STD_ON)
#define WRAPCRYPTO_CACHEKEY_DATA_SIZE           ((uint8)32U)

#define WRAPCRYPTO_KEYCACHE_KID_ENCRYPT_VAL     ((uint8)0x04U)
#define WRAPCRYPTO_KEYCACHE_KID_DECRYPT_VAL     ((uint8)0x05U)
#define WRAPCRYPTO_KEYCACHE_WP_VAL              ((uint8)0x01U)
#define WRAPCRYPTO_KEYCACHE_KU_VAL              ((uint8)0x00U)
#define WRAPCRYPTO_KEYCACHE_WC_VAL              ((uint8)0x01U)
#define WRAPCRYPTO_KEYCACHE_CID0_VAL            ((uint8)0x00U)
#define WRAPCRYPTO_KEYCACHE_CID1_VAL            ((uint8)0x00U)
#define WRAPCRYPTO_KEYCACHE_CID2_VAL            ((uint8)0x00U)
#define WRAPCRYPTO_KEYCACHE_CID3_VAL            ((uint8)0x01U)

#define WRAPCRYPTO_KEYCACHE_KID_POS             ((uint8)0U)
#define WRAPCRYPTO_KEYCACHE_WP_POS              ((uint8)1U)
#define WRAPCRYPTO_KEYCACHE_KU_POS              ((uint8)4U)
#define WRAPCRYPTO_KEYCACHE_WC_POS              ((uint8)5U)
#define WRAPCRYPTO_KEYCACHE_CID0_POS            ((uint8)8U)
#define WRAPCRYPTO_KEYCACHE_CID1_POS            ((uint8)9U)
#define WRAPCRYPTO_KEYCACHE_CID2_POS            ((uint8)10U)
#define WRAPCRYPTO_KEYCACHE_CID3_POS            ((uint8)11U)
#define WRAPCRYPTO_KEYCACHE_KEYDATA_POS         ((uint8)16U)
#endif
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_VAR
#include <WrapCrypto_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(WrapCrypto_JobInfoType, WRAPCRYPTO_VAR_CLEARED) WrapCrypto_JobInfo;
static VAR(uint8, WRAPCRYPTO_VAR_CLEARED) WrapCrypto_MaskPattern[WRAPCRYPTO_MASK_NEST_MAX];
static VAR(uint8, WRAPCRYPTO_VAR_CLEARED) WrapCrypto_MaskIndex;
/*===== Sample ===============================================================*/

#define WRAPCRYPTO_STOP_SEC_VAR
#include <WrapCrypto_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_CST
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_STOP_SEC_CST
#include <WrapCrypto_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define WRAPCRYPTO_START_SEC_CODE
#include <WrapCrypto_MemMap.h>

/******************************************************************************/
/* Function Name | WrapCrypto_Init                                            */
/* Description   | Initializes                                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | - Please implement processing to Init according to Crypto  */
/*               |   package.                                                 */
/*               | - If WDG timeout can occur, please call the following      */
/*               |   function. Also, include WdgM.h.                          */
/*               |    - WdgM_SetTriggerCondition();                           */
/*               |    - WdgM_Trigger();                                       */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Init (void)
{
/*===== Sample ===============================================================*/
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) NextJob;

    Crypto_83_sw_Init(NULL_PTR);
    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    CryIf_Init(NULL_PTR);
    Csm_Init(NULL_PTR);

    NextJob.Result = WRAPCRYPTO_JOB_FAILED;
    NextJob.Status = WRAPCRYPTO_STAT_IDLE;
    WrapCrypto_UpdateJobInfo(&NextJob);

    WrapCrypto_MaskIndex = 0U;
    Rpg_MemSet(WrapCrypto_MaskPattern, 0U, sizeof(WrapCrypto_MaskPattern));
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | WrapCrypto_MainFunction                                    */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | Please implement processing to MainFuction according to    */
/*               | Crypto package.                                            */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_MainFunction (void)
{
/*===== Sample ===============================================================*/
    Crypto_83_sw_Ab_MainFunctionOut();
    Csm_MainFunction();
    Crypto_83_sw_Ab_MainFunctionIn();
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | WrapCrypto_Set_UID                                         */
/* Description   | UID registration                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] KeyId   : KeyId                                       */
/*               | [IN] Uid     : UID                                         */
/*               | [IN] UidSize : UID Size                                    */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | - Please implement processing to set UID according to      */
/*               |   Crypto_sw_83.                                            */
/*               | - If not Crypto_sw_83, implement an empty function (return */
/*               |   value = E_OK).                                           */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_UID
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Uid,
    VAR(uint32, AUTOMATIC) UidSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

#if (WRAPCRYPTO_USE_CRYPTO_SW_83 == STD_ON)
    Ret = Csm_KeyElementSet(KeyId, CRYPTO_83_SW_AB_KE_UID, Uid, UidSize);
    if( Ret != (Std_ReturnType)E_OK )
    {
        Ret = E_NOT_OK;
    }
#else
    Ret = E_OK;
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_Set_ToolAuthKey                                 */
/* Description   | Tool Authentication Key registration                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] KeyId           : KeyId                               */
/*               | [IN] ToolAuthKey     : Tool Authentication Key             */
/*               | [IN] ToolAuthKeySize : Tool Authentication Key size        */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | - Please implement processing to set Tool Authentication   */
/*               |   Key according to Crypto_sw_83.                           */
/*               | - If not Crypto_sw_83, implement an empty function (return */
/*               |   value = E_OK).                                           */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_ToolAuthKey
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) ToolAuthKey,
    VAR(uint32, AUTOMATIC) ToolAuthKeySize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

#if (WRAPCRYPTO_USE_CRYPTO_SW_83_ENCRYPT == STD_ON)
    VAR(uint8, AUTOMATIC) KeyCache[WRAPCRYPTO_CACHEKEY_DATA_SIZE];

    Rpg_MemSet(KeyCache, 0U, sizeof(KeyCache));

    KeyCache[WRAPCRYPTO_KEYCACHE_KID_POS]  = WRAPCRYPTO_KEYCACHE_KID_ENCRYPT_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_WP_POS]   = WRAPCRYPTO_KEYCACHE_WP_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_KU_POS]   = WRAPCRYPTO_KEYCACHE_KU_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_WC_POS]   = WRAPCRYPTO_KEYCACHE_WC_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID0_POS] = WRAPCRYPTO_KEYCACHE_CID0_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID1_POS] = WRAPCRYPTO_KEYCACHE_CID1_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID2_POS] = WRAPCRYPTO_KEYCACHE_CID2_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID3_POS] = WRAPCRYPTO_KEYCACHE_CID3_VAL;

    Rpg_MemCopy(&KeyCache[WRAPCRYPTO_KEYCACHE_KEYDATA_POS], ToolAuthKey, ToolAuthKeySize);

    Ret = Csm_KeyElementSet(KeyId, CRYPTO_83_SW_AB_KE_KEYCACHE, KeyCache, sizeof(KeyCache));
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = Csm_KeySetValid(KeyId);
    }

    Rpg_MemSet(KeyCache, 0U, sizeof(KeyCache));
#else
    Ret = E_OK;
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_Set_SystemKey                                   */
/* Description   | System Key registration                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] KeyId         : KeyId                                 */
/*               | [IN] SystemKey     : System Key                            */
/*               | [IN] SystemKeySize : System Key size                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | - Please implement processing to set System Key according  */
/*               |   to Crypto_sw_83.                                         */
/*               | - If not Crypto_sw_83, implement an empty function (return */
/*               |   value = E_OK).                                           */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_SystemKey
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) SystemKey,
    VAR(uint32, AUTOMATIC) SystemKeySize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT == STD_ON)
    VAR(uint8, AUTOMATIC) KeyCache[WRAPCRYPTO_CACHEKEY_DATA_SIZE];

    Rpg_MemSet(KeyCache, 0U, sizeof(KeyCache));

    KeyCache[WRAPCRYPTO_KEYCACHE_KID_POS]  = WRAPCRYPTO_KEYCACHE_KID_DECRYPT_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_WP_POS]   = WRAPCRYPTO_KEYCACHE_WP_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_KU_POS]   = WRAPCRYPTO_KEYCACHE_KU_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_WC_POS]   = WRAPCRYPTO_KEYCACHE_WC_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID0_POS] = WRAPCRYPTO_KEYCACHE_CID0_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID1_POS] = WRAPCRYPTO_KEYCACHE_CID1_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID2_POS] = WRAPCRYPTO_KEYCACHE_CID2_VAL;
    KeyCache[WRAPCRYPTO_KEYCACHE_CID3_POS] = WRAPCRYPTO_KEYCACHE_CID3_VAL;

    Rpg_MemCopy(&KeyCache[WRAPCRYPTO_KEYCACHE_KEYDATA_POS], SystemKey, SystemKeySize);

    Ret = Csm_KeyElementSet(KeyId, CRYPTO_83_SW_AB_KE_KEYCACHE, KeyCache, sizeof(KeyCache));
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = Csm_KeySetValid(KeyId);
    }

    Rpg_MemSet(KeyCache, 0U, sizeof(KeyCache));
#else
    Ret = E_OK;
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_Set_SigVerifyKey                                */
/* Description   | Signature Verification Key registration                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] KeyId            : KeyId                              */
/*               | [IN] SigVerifyKey     : Signature Verification Key         */
/*               | [IN] SigVerifyKeySize : Signature Verification Key size    */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | - Please implement processing to set Signature             */
/*               |   Verification Key according to Crypto_sw_83.              */
/*               | - If not Crypto_sw_83, implement an empty function (return */
/*               |   value = E_OK).                                           */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_SigVerifyKey
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) SigVerifyKey,
    VAR(uint32, AUTOMATIC) SigVerifyKeySize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

#if (WRAPCRYPTO_USE_CRYPTO_SW_83_SIGVERIFY == STD_ON)
    VAR(uint8, AUTOMATIC) KeyMaterial[WRAPCRYPTO_KEYMATERIAL_SIZE];
    VAR(uint32, AUTOMATIC) SigVerifyKeyAddr;

    SigVerifyKeyAddr = (uint32)SigVerifyKey;
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_0]  = (uint8)(SigVerifyKeyAddr >> WRAPCRYPTO_BIT_SHIFT_24);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_1]  = (uint8)(SigVerifyKeyAddr >> WRAPCRYPTO_BIT_SHIFT_16);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_2]  = (uint8)(SigVerifyKeyAddr >> WRAPCRYPTO_BIT_SHIFT_8);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_3]  = (uint8)(SigVerifyKeyAddr & WRAPCRYPTO_BIT_MASK_8);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_4]  = (uint8)(SigVerifyKeySize >> WRAPCRYPTO_BIT_SHIFT_24);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_5]  = (uint8)(SigVerifyKeySize >> WRAPCRYPTO_BIT_SHIFT_16);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_6]  = (uint8)(SigVerifyKeySize >> WRAPCRYPTO_BIT_SHIFT_8);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_7]  = (uint8)(SigVerifyKeySize & WRAPCRYPTO_BIT_MASK_8);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_8]  = (uint8)(WRAPCRYPTO_RSA_PUBLIC_EXPONENT >> WRAPCRYPTO_BIT_SHIFT_24);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_9]  = (uint8)(WRAPCRYPTO_RSA_PUBLIC_EXPONENT >> WRAPCRYPTO_BIT_SHIFT_16);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_10] = (uint8)((WRAPCRYPTO_RSA_PUBLIC_EXPONENT & WRAPCRYPTO_BIT_MASK_16) >> WRAPCRYPTO_BIT_SHIFT_8);
    KeyMaterial[WRAPCRYPTO_KEYMATERIAL_POS_11] = (uint8)(WRAPCRYPTO_RSA_PUBLIC_EXPONENT & WRAPCRYPTO_BIT_MASK_8);

    Ret = Csm_KeyElementSet(KeyId, CRYPTO_83_SW_AB_KE_KEY, KeyMaterial, sizeof(KeyMaterial));
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = Csm_KeySetValid(KeyId);
    }

    Rpg_MemSet(KeyMaterial, 0U, sizeof(KeyMaterial));
#else
    Ret = E_OK;
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_Set_Nonce                                       */
/* Description   | Nonce registration                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] KeyId     : KeyId                                     */
/*               | [IN] Nonce     : Nonce                                     */
/*               | [IN] NonceSize : Nonce size                                */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement processing to set Nonce according to    */
/*               |   Crypto package.                                          */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/*               | - The pointer arguments are arranged as follows.           */
/*               |    Nonce : ".B_RAM_DIAGSRV_NONCE_SHARED"                   */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_Nonce
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Nonce,
    VAR(uint32, AUTOMATIC) NonceSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint32, AUTOMATIC) KeyElementId;

#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT == STD_ON)
    KeyElementId = CRYPTO_83_SW_AB_KE_DEC_CIPHER_IV;
#else
    /* Sample                */
    /* If keyElementId is 0. */
    KeyElementId = 0UL;
#endif

    Ret = Csm_KeyElementSet(KeyId, KeyElementId, Nonce, NonceSize);
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = Csm_KeySetValid(KeyId);
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_SchM_Enter                                      */
/* Description   | Enter exclusive control area                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | - Please implement the process to enter the exclusive      */
/*               |   control area.                                            */
/*               | - This function is called from SchM_Enter_Csm_xxx().       */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SchM_Enter (void)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Mask;
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    Mask = MaskInterruptAll();

    if( WrapCrypto_MaskIndex < WRAPCRYPTO_MASK_NEST_MAX )
    {
        WrapCrypto_MaskPattern[WrapCrypto_MaskIndex] = Mask;
        WrapCrypto_MaskIndex++;
    }
    else
    {
        Error.ModuleId = ECUM_MODULE_WRAPCRYPTO;
        Error.ApiId = WRAPCRYPTO_API_ID_SCHM_ENTER;
        Error.ErrorId = WrapCrypto_MaskIndex;

        EcuM_ReportError(&Error);
    }
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | WrapCrypto_SchM_Exit                                       */
/* Description   | Exit exclusive control area                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | - Please implement the process to exit the exclusive       */
/*               |   control area.                                            */
/*               | - This function is called from SchM_Exit_Csm_xxx().        */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SchM_Exit (void)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Mask;
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    if( (WrapCrypto_MaskIndex != (uint8)0U) && (WrapCrypto_MaskIndex <= WRAPCRYPTO_MASK_NEST_MAX) )
    {
        WrapCrypto_MaskIndex--;
        Mask = WrapCrypto_MaskPattern[WrapCrypto_MaskIndex];
        UnMaskInterruptAll(Mask);
    }
    else
    {
        Error.ModuleId = ECUM_MODULE_WRAPCRYPTO;
        Error.ApiId = WRAPCRYPTO_API_ID_SCHM_EXIT;
        Error.ErrorId = WrapCrypto_MaskIndex;

        EcuM_ReportError(&Error);
    }
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | WrapCrypto_ErrorCallout                                    */
/* Description   | Error notification                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] udErrorStatus : Error Status                          */
/* Return Value  | None                                                       */
/* Notes         | - Please implement to call EcuM_ReportError().             */
/*               | - This function is set to Csm_Ab_CsmErrorCalloutFunc in    */
/*               |   Csm config.                                              */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_ErrorCallout
(
    VAR(Csm_Ab_ErrorStatusType, AUTOMATIC) udErrorStatus
)
{
/*===== Sample ===============================================================*/
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = ECUM_MODULE_WRAPCRYPTO;
    Error.ApiId = WRAPCRYPTO_API_ID_CSM_ERRORCALLOUT;
    Error.ErrorId = (uint8)udErrorStatus;

    EcuM_ReportError(&Error);
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | WrapCrypto_TimeoutCallout                                  */
/* Description   | Timeout notification                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] u4ChannelId : Channel id                              */
/* Return Value  | None                                                       */
/* Notes         | - Please implement to call EcuM_ReportError().             */
/*               | - This function is set to Csm_Ab_CsmTimeOutCalloutFunc in  */
/*               |   Csm config.                                              */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_TimeoutCallout
(
    VAR(uint32, AUTOMATIC) u4ChannelId
)
{
/*===== Sample ===============================================================*/
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = ECUM_MODULE_WRAPCRYPTO;
    Error.ApiId = WRAPCRYPTO_API_ID_CSM_TIMEOUTCALLOUT;
    Error.ErrorId = (uint8)u4ChannelId;

    EcuM_ReportError(&Error);
/*===== Sample ===============================================================*/

    return;
}

/*===== Sample ===============================================================*/
#if (WRAPCRYPTO_USE_CRYPTO_SW_83 == STD_ON)
/******************************************************************************/
/* Function Name | WrapCrypto_83_sw_ErrorCallout                              */
/* Description   | Error notification                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] udErrorStatus : Error Status                          */
/* Return Value  | None                                                       */
/* Notes         | - Crypto_sw_83-specific function.                          */
/*               | - Please implement to call EcuM_ReportError().             */
/*               | - This function is set to Crypto_Ab_ErrorCalloutFunc in    */
/*               |   Crypto_sw_83 config                                      */
/*               | - If not Crypto_sw_83 and unnecessary, please delete. Also */
/*               |   delete the definition of WrapCrypto.h.                   */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_83_sw_ErrorCallout
(
    VAR(Crypto_83_sw_Ab_ErrorStatusType, AUTOMATIC) udErrorStatus
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = ECUM_MODULE_WRAPCRYPTO;
    Error.ApiId = WRAPCRYPTO_API_ID_CRYPTO_ERRORCALLOUT;
    Error.ErrorId = (uint8)udErrorStatus;

    EcuM_ReportError(&Error);

    return;
}

/******************************************************************************/
/* Function Name | WrapCrypto_83_sw_IntervalCallout                           */
/* Description   | Interval notification                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | - Crypto_sw_83-specific function.                          */
/*               | - Please implement to call the following function. Also,   */
/*               |   include WdgM.h.                                          */
/*               |    - (void)WdgM_CheckpointReached(WDGM_ENTITYID_BASE,      */
/*               |                                   WDGM_CHKPNTID_0);        */
/*               |    - WdgM_MainFunction();                                  */
/*               | - This function is set to Crypto_Ab_IntervalCalloutFunc in */
/*               |   Crypto_sw_83 config.                                     */
/*               | - If not Crypto_sw_83 and unnecessary, please delete. Also */
/*               |   delete the definition of WrapCrypto.h.                   */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_83_sw_IntervalCallout (void)
{
    (void)WdgM_CheckpointReached(WDGM_ENTITYID_BASE, WDGM_CHKPNTID_0);  /* No need to check return value */
    WdgM_MainFunction();

    return;
}
#endif
/*===== Sample ===============================================================*/

/*===== Sample ===============================================================*/
/******************************************************************************/
/* Function Name | WrapCrypto_UpdateJobInfo                                   */
/* Description   | Updates JobInfo                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobInfo : Job information                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_FAST) WrapCrypto_UpdateJobInfo
(
    P2CONST(WrapCrypto_JobInfoType, AUTOMATIC, WRAPCRYPTO_APPL_CONST) JobInfo
)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = MaskInterruptAll();   /* for JobResult/JobStatus */
    WrapCrypto_JobInfo.Result = JobInfo->Result;
    WrapCrypto_JobInfo.Status = JobInfo->Status;
    UnMaskInterruptAll(MaskPattern);    /* for JobResult/JobStatus */

    return;
}

/******************************************************************************/
/* Function Name | WrapCrypto_GetJobInfo                                      */
/* Description   | Gets JobInfo                                               */
/* Preconditions |                                                            */
/* Parameters    | [OUT] JobInfo : Job information                            */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_FAST) WrapCrypto_GetJobInfo
(
    P2VAR(WrapCrypto_JobInfoType, AUTOMATIC, WRAPCRYPTO_APPL_DATA) JobInfo
)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = MaskInterruptAll();   /* for JobResult/JobStatus */
    JobInfo->Result = WrapCrypto_JobInfo.Result;
    JobInfo->Status = WrapCrypto_JobInfo.Status;
    UnMaskInterruptAll(MaskPattern);    /* for JobResult/JobStatus */

    return;
}
/*===== Sample ===============================================================*/

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


#define WRAPCRYPTO_STOP_SEC_CODE
#include <WrapCrypto_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/12/06 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

