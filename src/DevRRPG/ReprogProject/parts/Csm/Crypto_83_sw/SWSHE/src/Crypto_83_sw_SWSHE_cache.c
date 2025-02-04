/* Crypto_83_sw_SWSHE_cache_c_v2-0-0                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | swshe/cache/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Crypto_83_sw_SWSHE.h"
#include "../inc/Crypto_83_sw_SWSHE_cache.h"
#include "../inc/Crypto_83_sw_SWSHE_ifcache.h"
#include "../../SecStd/inc/Crypto_83_sw_SecStd_String.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_SW_SWSHE_NVMKEY_NUM            ((uint8)14U)
#define CRYPTO_83_SW_SWSHE_UID_CACHE_STATE       ((uint8)14U)
#define CRYPTO_83_SW_SWSHE_CID_MAX               ((uint32)0x0FFFFFFFU)
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
#define CRYPTO_83_SW_SWSHE_UID_CACHE_SIZE        ((uint8)CRYPTO_83_SW_SWSHE_UID_SIZE + (uint8)1U)
#define CRYPTO_83_SW_SWSHE_UID_CACHE_CHECKSUM    ((uint8)CRYPTO_83_SW_SWSHE_UID_SIZE)
#else
#define CRYPTO_83_SW_SWSHE_UID_CACHE_SIZE        ((uint8)CRYPTO_83_SW_SWSHE_UID_SIZE)
#endif

#define CRYPTO_83_SW_SWSHE_KI_KEYID_POS          ((uint8)0U)
#define CRYPTO_83_SW_SWSHE_KI_FLWP_POS           ((uint8)1U)
#define CRYPTO_83_SW_SWSHE_KI_FLBP_POS           ((uint8)2U)
#define CRYPTO_83_SW_SWSHE_KI_FLDP_POS           ((uint8)3U)
#define CRYPTO_83_SW_SWSHE_KI_FLKU_POS           ((uint8)4U)
#define CRYPTO_83_SW_SWSHE_KI_FLWC_POS           ((uint8)5U)
#define CRYPTO_83_SW_SWSHE_KI_FLPL_POS           ((uint8)6U)
#define CRYPTO_83_SW_SWSHE_KI_RSV_POS            ((uint8)7U)
#define CRYPTO_83_SW_SWSHE_KI_CID_1B_POS         ((uint8)8U)
#define CRYPTO_83_SW_SWSHE_KI_CID_2B_POS         ((uint8)9U)
#define CRYPTO_83_SW_SWSHE_KI_CID_3B_POS         ((uint8)10U)
#define CRYPTO_83_SW_SWSHE_KI_CID_4B_POS         ((uint8)11U)
#define CRYPTO_83_SW_SWSHE_KI_CID_2B_SHIFT       ((uint8)8U)
#define CRYPTO_83_SW_SWSHE_KI_CID_3B_SHIFT       ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_KI_CID_4B_SHIFT       ((uint8)24U)
#define CRYPTO_83_SW_SWSHE_KI_KEYDATA_POS        ((uint8)16U)
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
#define CRYPTO_83_SW_SWSHE_KI_MASK_1BYTE         ((uint8)0xFF)

/* Cache status macro */
#define CRYPTO_83_SW_SWSHE_CACHE_UNINIT          ((uint8)0x00U)
#endif
#define CRYPTO_83_SW_SWSHE_CACHE_UNLOAD          ((uint8)0xE1U)
#define CRYPTO_83_SW_SWSHE_CACHE_LOAD            ((uint8)0xD2U)

#define CRYPTO_83_SW_SWSHE_CACHE_LENGTH          (CRYPTO_83_SW_SWSHE_NVMKEY_NUM + (uint8)1U)

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
#define CRYPTO_83_SW_SWSHE_U1_CHECKSUM_INIT_VAL  ((uint8)0xFF)
#define CRYPTO_83_SW_SWSHE_CACHE_ZERO            ((uint8)0U)
#endif


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Crypto_83_sw_Swshe_KeyInfoType stKeyInfo;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    uint8             u1Checksum;
#endif
} Crypto_83_sw_Swshe_CachedKeyInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_KeyInfoCpy
(
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptDestKey,
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptSrcKey
);

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
static FUNC(uint8, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CalcKeyChecksum
(
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKeyData
);

static FUNC(uint8, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CalcUidChecksum
(
    void
);
#endif

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>
static VAR(Crypto_83_sw_Swshe_CachedKeyInfoType, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_KeyInfoCache[CRYPTO_83_SW_SWSHE_NVMKEY_NUM];
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_u1NvmUid[CRYPTO_83_SW_SWSHE_UID_CACHE_SIZE];
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_u1CacheState[CRYPTO_83_SW_SWSHE_CACHE_LENGTH];   /* NVM KEY ,UID */
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT)  Crypto_83_sw_Swshe_u1CacheChkCounter;
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_u1CacheErrorCounter;
#endif
#define CRYPTO_83_sw_STOP_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CacheInit                             */
/* Description   | Cash initialization                                      */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CacheInit
(
    void
)
{
    uint8 i;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    /* All cache clear */
    Crypto_83_sw_Swshe_u1CacheErrorCounter = (uint8)0U;
    Crypto_83_sw_Swshe_u1CacheChkCounter = (uint8)0U;
#endif

    /* KeyInfo cache clear */
    for( i = (uint8)0x00U; i < CRYPTO_83_SW_SWSHE_NVMKEY_NUM; i++)
    {
        (void)Crypto_83_sw_SecStd_MemSet( &Crypto_83_sw_Swshe_KeyInfoCache[i].stKeyInfo, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
        Crypto_83_sw_Swshe_u1CacheState[i] = CRYPTO_83_SW_SWSHE_CACHE_UNLOAD;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        Crypto_83_sw_Swshe_KeyInfoCache[i].u1Checksum = CRYPTO_83_SW_SWSHE_U1_CHECKSUM_INIT_VAL;
#endif
    }
    /* Uid cache clear */
    (void)Crypto_83_sw_SecStd_MemSet( &Crypto_83_sw_Swshe_u1NvmUid, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_UID_SIZE ); /* no return check required */
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    Crypto_83_sw_Swshe_u1NvmUid[CRYPTO_83_SW_SWSHE_UID_CACHE_CHECKSUM]  = CRYPTO_83_SW_SWSHE_U1_CHECKSUM_INIT_VAL;
#endif
    Crypto_83_sw_Swshe_u1CacheState[CRYPTO_83_SW_SWSHE_UID_CACHE_STATE] = CRYPTO_83_SW_SWSHE_CACHE_UNLOAD;

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CacheLoadKey                          */
/* Description   | KeyInfo reading                                          */
/* Preconditions | -                                                        */
/* Parameters    | (in)  u1KeyId : Key ID(0 - 13)                           */
/*               | (out) ptKey   : KeyInfo start address                    */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CacheLoadKey
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey
)
{
    Std_ReturnType   u1_Ret = (Std_ReturnType)E_OK;

    /* Param check */
    if(ptKey != NULL_PTR)
    {
        /* Cache load check */
        if( (Crypto_83_sw_Swshe_u1CacheState[u1KeyId] == CRYPTO_83_SW_SWSHE_CACHE_LOAD) && (u1KeyId < CRYPTO_83_SW_SWSHE_KID_RAM_KEY) )
        {
            /* Load KeyInfo from KeyInfoCache */
            Crypto_83_sw_SWSHE_KeyInfoCpy(ptKey, &(Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo));
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_MEMORY_FAILURE;
        }
    }
    else
    {
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_MEMORY_FAILURE;
    }


    return u1_Ret;
}


/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CacheLoadUid                          */
/* Description   | UID reading                                              */
/* Preconditions | -                                                        */
/* Parameters    | (out) ptUid  : UID start address(15byte)                 */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CacheLoadUid
(
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptUid
)
{
    Std_ReturnType   u1_Ret = (Std_ReturnType)E_OK;

    /* Param check */
    if(ptUid != NULL_PTR)
    {
        /* Cache load check */
        if(Crypto_83_sw_Swshe_u1CacheState[CRYPTO_83_SW_SWSHE_UID_CACHE_STATE] == CRYPTO_83_SW_SWSHE_CACHE_LOAD)
        {
            /* Load UID from UIDCache */
            (void)Crypto_83_sw_SecStd_MemCpy( ptUid, &Crypto_83_sw_Swshe_u1NvmUid[0], (uint32)CRYPTO_83_SW_SWSHE_UID_SIZE ); /* no return check required */
        }
        else
        {
            /* Cache unload */
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_MEMORY_FAILURE;
        }
    }
    else
    {
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_MEMORY_FAILURE;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CacheUpdateUid                        */
/* Description   | UID cache update                                         */
/* Preconditions | -                                                        */
/* Parameters    | (in) ptUid  : UID start address(15byte)                  */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CacheUpdateUid
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptUid
)
{
    Std_ReturnType   u1_Ret = (Std_ReturnType)E_OK;

    /* Param check */
    if(ptUid != NULL_PTR)
    {
        /* UID cache state check */
        if( (Crypto_83_sw_Swshe_u1CacheState[CRYPTO_83_SW_SWSHE_UID_CACHE_STATE] == CRYPTO_83_SW_SWSHE_CACHE_LOAD)
            || (Crypto_83_sw_Swshe_u1CacheState[CRYPTO_83_SW_SWSHE_UID_CACHE_STATE] == CRYPTO_83_SW_SWSHE_CACHE_UNLOAD) )
        {
            /* Copy cache */
            (void)Crypto_83_sw_SecStd_MemCpy( Crypto_83_sw_Swshe_u1NvmUid, ptUid, (uint32)CRYPTO_83_SW_SWSHE_UID_SIZE ); /* no return check required */

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
            /* Caluclate and store checksum value */
            Crypto_83_sw_Swshe_u1NvmUid[CRYPTO_83_SW_SWSHE_UID_CACHE_CHECKSUM] = Crypto_83_sw_SWSHE_CalcUidChecksum();
#endif

            /* Set cache state */
            Crypto_83_sw_Swshe_u1CacheState[CRYPTO_83_SW_SWSHE_UID_CACHE_STATE] = CRYPTO_83_SW_SWSHE_CACHE_LOAD;
        }
        else
        {
            /* UID cache not init */
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
    }
    else
    {
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CacheUpdateKeyInfo                    */
/* Description   | KeyInfo cache update                                     */
/* Preconditions | -                                                        */
/* Parameters    | (in) u1KeyId         : Key ID(0-13)                      */
/*               | (in) pt_u1KeyInfo    : Key info start address(32byte)    */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CacheUpdateKeyInfo
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u1KeyInfo
)
{
    Std_ReturnType   u1_Ret = (Std_ReturnType)E_OK;
    uint32 cid;

    /* Param check */
    if(pt_u1KeyInfo != NULL_PTR)
    {
        /* KeyId range check */
        if((u1KeyId < CRYPTO_83_SW_SWSHE_KID_RAM_KEY) && (pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_KEYID_POS] < CRYPTO_83_SW_SWSHE_KID_RAM_KEY))
        {
            cid =   ((uint32)pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_CID_1B_POS] << CRYPTO_83_SW_SWSHE_KI_CID_4B_SHIFT)
                  | ((uint32)pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_CID_2B_POS] << CRYPTO_83_SW_SWSHE_KI_CID_3B_SHIFT)
                  | ((uint32)pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_CID_3B_POS] << CRYPTO_83_SW_SWSHE_KI_CID_2B_SHIFT)
                  | ((uint32)pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_CID_4B_POS]);

            if(cid <= CRYPTO_83_SW_SWSHE_CID_MAX)
            {
                if( (Crypto_83_sw_Swshe_u1CacheState[u1KeyId] == CRYPTO_83_SW_SWSHE_CACHE_LOAD)
                    || (Crypto_83_sw_Swshe_u1CacheState[u1KeyId] == CRYPTO_83_SW_SWSHE_CACHE_UNLOAD) )
                {
                    /* Copy cache */
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Id         = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_KEYID_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Flag_wp    = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_FLWP_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Flag_bp    = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_FLBP_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Flag_dp    = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_FLDP_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Flag_ku    = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_FLKU_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Flag_wc    = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_FLWC_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Flag_plain = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_FLPL_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Flag_rsv1  = pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_RSV_POS];
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u4Counter    = cid;
                    (void)Crypto_83_sw_SecStd_MemCpy( Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo.u1Data, &pt_u1KeyInfo[CRYPTO_83_SW_SWSHE_KI_KEYDATA_POS], (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE ); /* no return check required */

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
                    /* Caluclate and store checksum value */
                    Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].u1Checksum = Crypto_83_sw_SWSHE_CalcKeyChecksum( &Crypto_83_sw_Swshe_KeyInfoCache[u1KeyId].stKeyInfo );
#endif

                    /* Set cache state */
                    Crypto_83_sw_Swshe_u1CacheState[u1KeyId] = CRYPTO_83_SW_SWSHE_CACHE_LOAD;
                }
                else
                {
                    /* cache state check NG */
                    u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
                }
            }
            else
            {
                /* KeyInfo check CID NG */
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
            }
        }
        else
        {
            /* KeyId range check NG */
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
        }
    }
    else
    {
        /* Param check NG */
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
    }

    return u1_Ret;
}

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CacheGetErrorStatus                   */
/* Description   | Check ram                                                */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CacheGetErrorStatus
(
    void
)
{

    Std_ReturnType u1_Ret;
    uint8 u1_RetChecksum;
    uint8 u1_StoredChecksum;
    uint8 u1_TmpCacheState;
    uint8 u1_CacheChkCounter = Crypto_83_sw_Swshe_u1CacheChkCounter;

    u1_Ret = (Std_ReturnType)E_OK;

    if ( u1_CacheChkCounter >= CRYPTO_83_SW_SWSHE_CACHE_LENGTH )
    {
        u1_CacheChkCounter = CRYPTO_83_SW_SWSHE_CACHE_ZERO;
    }

    /* Error check for Crypto_83_sw_Swshe_KeyInfoCache */
    u1_TmpCacheState = Crypto_83_sw_Swshe_u1CacheState[u1_CacheChkCounter];

    if ( u1_TmpCacheState == CRYPTO_83_SW_SWSHE_CACHE_UNINIT )
    {
        /* If SWSHE has not been initialized, */
        /* All Ram errror check will be skipped */
        u1_Ret = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        if (u1_TmpCacheState == CRYPTO_83_SW_SWSHE_CACHE_LOAD)
        {

            if ( u1_CacheChkCounter == CRYPTO_83_SW_SWSHE_UID_CACHE_STATE )
            {
                /* Caluclate and validate checksum value of UID */
                u1_RetChecksum    = Crypto_83_sw_SWSHE_CalcUidChecksum();
                u1_StoredChecksum = Crypto_83_sw_Swshe_u1NvmUid[CRYPTO_83_SW_SWSHE_UID_CACHE_CHECKSUM];

                if ( u1_StoredChecksum != u1_RetChecksum )
                {
                    Crypto_83_sw_Swshe_u1CacheErrorCounter = CRYPTO_83_SW_SWSHE_CACHE_LENGTH;
                }
            }
            else
            {
                /* Caluclate and validate checksum value of KeyData */
                u1_RetChecksum    = Crypto_83_sw_SWSHE_CalcKeyChecksum( &Crypto_83_sw_Swshe_KeyInfoCache[u1_CacheChkCounter].stKeyInfo );
                u1_StoredChecksum = Crypto_83_sw_Swshe_KeyInfoCache[u1_CacheChkCounter].u1Checksum;

                if ( u1_StoredChecksum != u1_RetChecksum )
                {
                    Crypto_83_sw_Swshe_u1CacheErrorCounter = CRYPTO_83_SW_SWSHE_CACHE_LENGTH;
                }
            }
        }
        else if (u1_TmpCacheState != CRYPTO_83_SW_SWSHE_CACHE_UNLOAD)
        {
            /* detect memory failure */
            Crypto_83_sw_Swshe_u1CacheErrorCounter = CRYPTO_83_SW_SWSHE_CACHE_LENGTH;
        }
        else
        {
            /* CacheState is UNLOAD */
            /* Nothing to do */
        }

        /* SWSHE returns MEMORY_FAILURE error, while at least one of cache has ram error */
        if ( Crypto_83_sw_Swshe_u1CacheErrorCounter > (uint8)0U)
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_MEMORY_FAILURE;
            Crypto_83_sw_Swshe_u1CacheErrorCounter--;
        }

        u1_CacheChkCounter++;
    }

    Crypto_83_sw_Swshe_u1CacheChkCounter = u1_CacheChkCounter;

    return u1_Ret;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_KeyInfoCpy                            */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | ptDestKey :                                              */
/*               | ptSrcKey  :                                              */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_KeyInfoCpy
(
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptDestKey,
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptSrcKey
)
{
    ptDestKey->u1Id = ptSrcKey->u1Id;
    ptDestKey->u1Flag_wp = ptSrcKey->u1Flag_wp;
    ptDestKey->u1Flag_bp = ptSrcKey->u1Flag_bp;
    ptDestKey->u1Flag_dp = ptSrcKey->u1Flag_dp;
    ptDestKey->u1Flag_ku = ptSrcKey->u1Flag_ku;
    ptDestKey->u1Flag_wc = ptSrcKey->u1Flag_wc;
    ptDestKey->u1Flag_plain = ptSrcKey->u1Flag_plain;
    ptDestKey->u1Flag_rsv1 = ptSrcKey->u1Flag_rsv1;
    ptDestKey->u4Counter = ptSrcKey->u4Counter;
    (void)Crypto_83_sw_SecStd_MemCpy( ptDestKey->u1Data, &ptSrcKey->u1Data[0], (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE ); /* no return check required */
}

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CalcKeyChecksum                       */
/* Description   | Calculate Checksum Value of KeyData                      */
/* Preconditions | -                                                        */
/* Parameters    | ptKeyData : Key Information                              */
/* Return Value  | Checksum Value                                           */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CalcKeyChecksum
(
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKeyData
)
{
    uint8 u1_Ret;   /* This code assumes a wraparound */
    uint8 u1_Cnt;

    u1_Ret  = ptKeyData->u1Id;
    u1_Ret += ptKeyData->u1Flag_wp;
    u1_Ret += ptKeyData->u1Flag_bp;
    u1_Ret += ptKeyData->u1Flag_dp;
    u1_Ret += ptKeyData->u1Flag_ku;
    u1_Ret += ptKeyData->u1Flag_wc;
    u1_Ret += ptKeyData->u1Flag_plain;
    u1_Ret += ptKeyData->u1Flag_rsv1;

    u1_Ret += (uint8)((ptKeyData->u4Counter >> CRYPTO_83_SW_SWSHE_KI_CID_4B_SHIFT));
    u1_Ret += (uint8)((ptKeyData->u4Counter >> CRYPTO_83_SW_SWSHE_KI_CID_3B_SHIFT) & CRYPTO_83_SW_SWSHE_KI_MASK_1BYTE); /* This code assumes a wraparound */
    u1_Ret += (uint8)((ptKeyData->u4Counter >> CRYPTO_83_SW_SWSHE_KI_CID_2B_SHIFT) & CRYPTO_83_SW_SWSHE_KI_MASK_1BYTE); /* This code assumes a wraparound */
    u1_Ret += (uint8)( ptKeyData->u4Counter &  CRYPTO_83_SW_SWSHE_KI_MASK_1BYTE);   /* This code assumes a wraparound */

    for ( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE; u1_Cnt++ )
    {
        u1_Ret += ptKeyData->u1Data[u1_Cnt];    /* This code assumes a wraparound */
    }

    u1_Ret = (uint8)(~u1_Ret);

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CalcUidChecksum                       */
/* Description   | Calculate Checksum Value of UID                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Checksum Value                                           */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CalcUidChecksum(
    void
)
{
    uint8 u1_Ret = (uint8)0U;   /* This code assumes a wraparound */
    uint8 u1_Cnt;

    for ( u1_Cnt = (uint8)0U; u1_Cnt < (uint8)CRYPTO_83_SW_SWSHE_UID_SIZE; u1_Cnt++ )
    {
        u1_Ret += Crypto_83_sw_Swshe_u1NvmUid[u1_Cnt];  /* This code assumes a wraparound */
    }

    u1_Ret = (uint8)(~u1_Ret);

    return u1_Ret;
}
#endif

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
