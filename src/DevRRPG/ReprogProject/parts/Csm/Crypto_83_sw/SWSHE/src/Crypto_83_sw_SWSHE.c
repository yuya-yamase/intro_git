/* Crypto_83_sw_SWSHE_c_v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | swshe/CODE                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Crypto_83_sw_SWSHE.h"
#include "../inc/Crypto_83_sw_SWSHE_ifcache.h"
#include "../inc/Crypto_83_sw_SWSHE_ifcrypto.h"
#include "../../SecStd/inc/Crypto_83_sw_SecStd_String.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_SW_SWSHE_ID_KEY_NUM            ((uint8)15U)
#define CRYPTO_83_SW_SWSHE_M1_SIZE               ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_M2_SIZE               ((uint8)32U)
#define CRYPTO_83_SW_SWSHE_M3_SIZE               ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_M4_SIZE               ((uint8)32U)
#define CRYPTO_83_SW_SWSHE_M5_SIZE               ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_CID_SIZE              ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_CMAC_SIZE             ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_CMAC_SIZE_BIT         ((uint8)128U)

#define CRYPTO_83_SW_SWSHE_SREG_CLEAR            ((uint8)0xF0U)
#define CRYPTO_83_SW_SWSHE_SREG_SET              ((uint8)0xE1U)

#define CRYPTO_83_SW_SWSHE_BIT_1                 (1U)
#define CRYPTO_83_SW_SWSHE_BIT_2                 (2U)
#define CRYPTO_83_SW_SWSHE_BIT_3                 (3U)
#define CRYPTO_83_SW_SWSHE_BIT_4                 (4U)
#define CRYPTO_83_SW_SWSHE_BIT_7                 (7U)
#define CRYPTO_83_SW_SWSHE_BIT_8                 (8U)
#define CRYPTO_83_SW_SWSHE_BIT_16                (16U)
#define CRYPTO_83_SW_SWSHE_BIT_24                (24U)
#define CRYPTO_83_SW_SWSHE_BIT_TO_BYTE_SHIFT     (3U)


#define CRYPTO_83_SW_SWSHE_MASK_1BIT             ((uint8)0x01U)
#define CRYPTO_83_SW_SWSHE_MASK_4BIT             ((uint8)0x0FU)
#define CRYPTO_83_SW_SWSHE_MASK_1BYTE            ((uint8)0xFFU)

#define CRYPTO_83_SW_SWSHE_CBC_MAXBLK_NUM        ((uint32)0x0FFFFFFFU)
#define CRYPTO_83_SW_SWSHE_CMAC_MINBIT_NUM       ((uint32)0x8U)
#define CRYPTO_83_SW_SWSHE_CMAC_MAXBIT_NUM       ((uint32)0xFFFFFF80U)
#define CRYPTO_83_SW_SWSHE_CMAC_MAX_MACSIZE_NUM  ((uint8)0x7FU)

#define CRYPTO_83_SW_SWSHE_KEYUPDATE_ENCC        ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_KEYUPDATE_MACC        ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_M1_ID                 ((uint8)15U)
#define CRYPTO_83_SW_SWSHE_M2_CHK_BLOCK_SIZE     ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_M2_PAD_POSITION       ((uint8)5U)
#define CRYPTO_83_SW_SWSHE_M2_PAD_MASK           ((uint8)0x7FU)
#define CRYPTO_83_SW_SWSHE_M2_CID_1BYTE_POS      ((uint8)0U)
#define CRYPTO_83_SW_SWSHE_M2_CID_2BYTE_POS      ((uint8)1U)
#define CRYPTO_83_SW_SWSHE_M2_CID_3BYTE_POS      ((uint8)2U)
#define CRYPTO_83_SW_SWSHE_M2_CID_4BYTE_POS      ((uint8)3U)
#define CRYPTO_83_SW_SWSHE_M2_FID_1BYTE_POS      ((uint8)3U)
#define CRYPTO_83_SW_SWSHE_M2_FID_2BYTE_POS      ((uint8)4U)
#define CRYPTO_83_SW_SWSHE_M2_CHK_KEY_POS        ((uint8)16U)

#define CRYPTO_83_SW_SWSHE_M4_AES_POSITION       ((uint8)16U)
#define CRYPTO_83_SW_SWSHE_M4_CID_1BYTE_POS      ((uint8)0U)
#define CRYPTO_83_SW_SWSHE_M4_CID_2BYTE_POS      ((uint8)1U)
#define CRYPTO_83_SW_SWSHE_M4_CID_3BYTE_POS      ((uint8)2U)
#define CRYPTO_83_SW_SWSHE_M4_CID_4BYTE_POS      ((uint8)3U)
#define CRYPTO_83_SW_SWSHE_CID_PADDING           ((uint8)0x08U)

#define CRYPTO_83_SW_SWSHE_CID_U4_TO_1BYTE_SIFT  ((uint8)20U)
#define CRYPTO_83_SW_SWSHE_CID_U4_TO_2BYTE_SIFT  ((uint8)12U)
#define CRYPTO_83_SW_SWSHE_CID_U4_TO_3BYTE_SIFT  ((uint8)4U)
#define CRYPTO_83_SW_SWSHE_CID_U4_TO_4BYTE_SIFT  ((uint8)4U)

#define CRYPTO_83_SW_SWSHE_M4_ID_POSITION        ((uint8)15U)

#define CRYPTO_83_SW_SWSHE_M5_KEYINFO_SIZE       ((uint32)32U)
#define CRYPTO_83_SW_SWSHE_M5_KEYINFO_POSITION   (CRYPTO_83_SW_SWSHE_M5_SIZE)
#define CRYPTO_83_SW_SWSHE_M5_FID_WP_POSITION    (CRYPTO_83_SW_SWSHE_M5_SIZE + (uint32)1U)
#define CRYPTO_83_SW_SWSHE_M5_FID_BP_POSITION    (CRYPTO_83_SW_SWSHE_M5_SIZE + (uint32)2U)
#define CRYPTO_83_SW_SWSHE_M5_FID_DP_POSITION    (CRYPTO_83_SW_SWSHE_M5_SIZE + (uint32)3U)
#define CRYPTO_83_SW_SWSHE_M5_FID_KU_POSITION    (CRYPTO_83_SW_SWSHE_M5_SIZE + (uint32)4U)
#define CRYPTO_83_SW_SWSHE_M5_FID_WC_POSITION    (CRYPTO_83_SW_SWSHE_M5_SIZE + (uint32)5U)
#define CRYPTO_83_SW_SWSHE_M5_FID_PL_POSITION    (CRYPTO_83_SW_SWSHE_M5_SIZE + (uint32)6U)
#define CRYPTO_83_SW_SWSHE_M5_FID_RSV_POSITION   (CRYPTO_83_SW_SWSHE_M5_SIZE + (uint32)7U)
#define CRYPTO_83_SW_SWSHE_M5_KI_CID_1BYTE_POS   (CRYPTO_83_SW_SWSHE_M5_FID_RSV_POSITION + (uint32)1U)
#define CRYPTO_83_SW_SWSHE_M5_KI_CID_2BYTE_POS   (CRYPTO_83_SW_SWSHE_M5_KI_CID_1BYTE_POS + (uint32)1U)
#define CRYPTO_83_SW_SWSHE_M5_KI_CID_3BYTE_POS   (CRYPTO_83_SW_SWSHE_M5_KI_CID_2BYTE_POS + (uint32)1U)
#define CRYPTO_83_SW_SWSHE_M5_KI_CID_4BYTE_POS   (CRYPTO_83_SW_SWSHE_M5_KI_CID_3BYTE_POS + (uint32)1U)
#define CRYPTO_83_SW_SWSHE_M5_KI_DATA_POS        (CRYPTO_83_SW_SWSHE_M5_KI_CID_4BYTE_POS  + (uint32)5U)

/* bit shift macro */
#define CRYPTO_83_SW_SWSHE_NO_PERMISSION         ((uint8)0U)

#define CRYPTO_83_SW_SWSHE_BITSIZE_MASK          ((uint8)0x07U)
#define CRYPTO_83_SW_SWSHE_BITCMP_MASK           ((uint8)0x01U)
#define CRYPTO_83_SW_SWSHE_BITCMP_SHIFT_CNT      ((uint8)0x08U)

#define CRYPTO_83_SW_SWSHE_KU_ENABLE             ((uint8)0x01U)
#define CRYPTO_83_SW_SWSHE_WP_ENABLE             ((uint8)0x01U)
#define CRYPTO_83_SW_SWSHE_WC_ENABLE             ((uint8)0x01U)
#define CRYPTO_83_SW_SWSHE_PLN_ENABLE            ((uint8)0x01U)
#define CRYPTO_83_SW_SWSHE_BYTECMP_OK            ((sint32)0x00)
#define CRYPTO_83_SW_SWSHE_UID_ADD_ALIGNED_SIZE  ((uint8)CRYPTO_83_SW_SWSHE_UID_SIZE + (uint8)1U)
#define CRYPTO_83_SW_SWSHE_M2_PAD_TOP_POSITION   ((CRYPTO_83_SW_SWSHE_M2_PAD_POSITION - (uint8)1U))

#define CRYPTO_83_SW_SWSHE_RAMKEY_EMPTY          ((uint8)0xF0U)
#define CRYPTO_83_SW_SWSHE_RAMKEY_STORED         ((uint8)0xE1U)

#define CRYPTO_83_SW_SWSHE_U1_ZERO               ((uint8)0U)
#define CRYPTO_83_SW_SWSHE_U4_ZERO               ((uint32)0UL)

#define CRYPTO_83_SW_SWSHE_NEXTINDEX             (1UL)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    P2CONST(uint8, TYPEDEF, CRYPTO_83_sw_APPL_DATA) ptM1;
    P2CONST(uint8, TYPEDEF, CRYPTO_83_sw_APPL_DATA) ptM2;
    P2CONST(uint8, TYPEDEF, CRYPTO_83_sw_APPL_DATA) ptM3;
    uint8                      u1KeyId;
    uint8                      u1AuthId;
    uint8                      u1K1[CRYPTO_83_SW_SWSHE_KEY_SIZE];
    uint8                      u1K2[CRYPTO_83_SW_SWSHE_KEY_SIZE];
    uint8                      u1K3[CRYPTO_83_SW_SWSHE_KEY_SIZE];
    uint8                      u1K4[CRYPTO_83_SW_SWSHE_KEY_SIZE];
    uint8                      u1IsWildCard;
    uint8                      u1Uid[CRYPTO_83_SW_SWSHE_UID_ADD_ALIGNED_SIZE]; /* aligned */
} Crypto_83_sw_Swshe_MemUpdate;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_KeyDerive
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptInput1,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptInput2,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptOutput
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_MiyaguchiPreneel
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptInput,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptKey,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptOutput
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ParseM1
(
    P2VAR(Crypto_83_sw_Swshe_MemUpdate, AUTOMATIC, AUTOMATIC) ptMUP,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyTmp
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ParseM2
(
    P2VAR(Crypto_83_sw_Swshe_MemUpdate, AUTOMATIC, AUTOMATIC) ptMUP,
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyTmp,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyNew
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ParseM3
(
    P2VAR(Crypto_83_sw_Swshe_MemUpdate, AUTOMATIC, AUTOMATIC) ptMUP,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyTmp
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CheckM1
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM1,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) authId,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) keyId,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptIsWc
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CheckM2
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM2,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK1,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CheckM3
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM1,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM2,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK2,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM3
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GenerateM4
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptUid,
    Crypto_83_sw_ConstR uint8 u1KeyId,
    Crypto_83_sw_ConstR uint8 u1AuthId,
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK3,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM4
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GenerateM5
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM4,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK4,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM5
);

static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_LoadRamKey
(
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey
);

static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_StoreRamKey
(
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey
);

static FUNC(sint32, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_BitCmp
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptS1,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptS2,
    uint32 u4Num
);

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_u1SregBusy;
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_u1SregRndInit;
static VAR(Crypto_83_sw_Swshe_KeyInfoType, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_stRamKey;
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_u1RamKeyStatus;

#define CRYPTO_83_sw_STOP_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CONST
#include <Crypto_83_sw_MemMap.h>

static CONST(uint8, CRYPTO_83_sw_CONST) Crypto_83_sw_Swshe_u1KeyUpdateEncC[CRYPTO_83_SW_SWSHE_KEYUPDATE_ENCC] = { 0x01U, 0x01U, 0x53U, 0x48U, 0x45U, 0x00U, 0x80U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xb0U};
static CONST(uint8, CRYPTO_83_sw_CONST) Crypto_83_sw_Swshe_u1KeyUpdateMacC[CRYPTO_83_SW_SWSHE_KEYUPDATE_MACC] = { 0x01U, 0x02U, 0x53U, 0x48U, 0x45U, 0x00U, 0x80U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xb0U};


static CONST(AB_83_ConstV uint16, CRYPTO_83_sw_CONST) Crypto_83_sw_Swshe_u2KeyUpdatePolicy[CRYPTO_83_SW_SWSHE_ID_KEY_NUM] = {
        0x0001U, /* 00: SECRET */
        0x0002U, /* 01: MASTER_ECU_KEY */
        0x0006U, /* 02: BOOT_MAC_KEY */
        0x0006U, /* 03: BOOT_MAC */
        0x0012U, /* 04: KEY01 */
        0x0022U, /* 05: KEY02 */
        0x0042U, /* 06: KEY03 */
        0x0082U, /* 07: KEY05 */
        0x0102U, /* 08: KEY05 */
        0x0202U, /* 09: KEY06 */
        0x0402U, /* 10: KEY07 */
        0x0802U, /* 11: KEY08 */
        0x1002U, /* 12: KEY09 */
        0x2002U, /* 13: KEY10 */
        0x3ff1U, /* 14: RAM  */
    };
#define CRYPTO_83_sw_STOP_SEC_CONST
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_Init                                  */
/* Description   | SWSHE initialization                                     */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_Init
(
    void
)
{
    Crypto_83_sw_Swshe_u1SregBusy    = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    Crypto_83_sw_Swshe_u1SregRndInit = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    Crypto_83_sw_SWSHE_CacheInit();
    Crypto_83_sw_SWSHE_IfcryptoInit();
    Crypto_83_sw_Swshe_stRamKey.u1Id = CRYPTO_83_SW_SWSHE_KID_RAM_KEY;
    Crypto_83_sw_Swshe_stRamKey.u1Flag_wp = (uint8)0x00U;
    Crypto_83_sw_Swshe_stRamKey.u1Flag_bp = (uint8)0x00U;
    Crypto_83_sw_Swshe_stRamKey.u1Flag_dp = (uint8)0x00U;
    Crypto_83_sw_Swshe_stRamKey.u1Flag_ku = (uint8)0x00U;
    Crypto_83_sw_Swshe_stRamKey.u1Flag_wc = (uint8)0x00U;
    Crypto_83_sw_Swshe_stRamKey.u1Flag_plain =  (uint8)0x01U;       /* PLAIN */
    Crypto_83_sw_Swshe_stRamKey.u1Flag_rsv1  =  (uint8)0x00U;
    (void)Crypto_83_sw_SecStd_MemSet( &Crypto_83_sw_Swshe_stRamKey.u1Data, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE ); /* no return check required */
    Crypto_83_sw_Swshe_u1RamKeyStatus = CRYPTO_83_SW_SWSHE_RAMKEY_EMPTY;

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdEncEcb                             */
/* Description   | ECB Encryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  u1keyId  : Key ID(4 - 14)                          */
/*               | (in)  ptPlain  : Plain text start address (16byte)       */
/*               | (out) ptCipher : Cipher test start address (16byte)      */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_KEY_NOT_AVAILABLE                          */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CRYPTO_E_KEY_EMPTY                                      */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdEncEcb
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
)
{
    Crypto_83_sw_Swshe_KeyInfoType    st_Info;
    Std_ReturnType                    u1_Ret = (Std_ReturnType)E_OK;

    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( (ptPlain != NULL_PTR) && (ptCipher != NULL_PTR) )
        {
            /* Confirmation of the use key ID */
            if( (CRYPTO_83_SW_SWSHE_KID_BT_MAC < u1KeyId) && (u1KeyId < CRYPTO_83_SW_SWSHE_ID_KEY_NUM) )
            {
                if( u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
                {
                    if( Crypto_83_sw_Swshe_u1RamKeyStatus == CRYPTO_83_SW_SWSHE_RAMKEY_STORED )
                    {
                        Crypto_83_sw_SWSHE_LoadRamKey( &st_Info );
                    }
                    else
                    {
                        u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                    }
                }
                else
                {
                    u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( u1KeyId, &st_Info );
                    if( u1_Ret == (Std_ReturnType)E_OK )
                    {
                        /* Key slot counter, KU Flag check. 0:Encryption,1:MAC */
                        if( st_Info.u4Counter == (uint32)0x00000000U )
                        {
                            u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                        }
                        else if( st_Info.u1Flag_ku != (uint8)0x00U )
                        {
                            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
                        }
                        else
                        {
                            /* No Processing */
                        }
                    }
                }
                if( u1_Ret == (Std_ReturnType)E_OK )
                {
                    u1_Ret = Crypto_83_sw_SWSHE_AES128_EncEcb( &st_Info.u1Data[0], ptPlain, ptCipher );
                }
                (void)Crypto_83_sw_SecStd_MemSet( &st_Info, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    /* 0 sets of output parameters. */
    if( (u1_Ret != (Std_ReturnType)E_OK) && (ptCipher != NULL_PTR) )
    {
        (void)Crypto_83_sw_SecStd_MemSet( ptCipher, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_BLOCK_SIZE ); /* no return check required */
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdDecEcb                             */
/* Description   | ECB Decryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  u1KeyId  : Key ID(4 - 14)                          */
/*               | (in)  ptCipher : Cipher test start address (16byte)      */
/*               | (out) ptPlain  : Plain text start address (16byte)       */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_KEY_NOT_AVAILABLE                          */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CRYPTO_E_KEY_EMPTY                                      */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdDecEcb
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
)
{
    Crypto_83_sw_Swshe_KeyInfoType    st_Info;
    Std_ReturnType                    u1_Ret = (Std_ReturnType)E_OK;

    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( (ptCipher != NULL_PTR) && (ptPlain != NULL_PTR) )
        {
            /* Confirmation of the use key ID */
            if( (CRYPTO_83_SW_SWSHE_KID_BT_MAC < u1KeyId) && (u1KeyId < CRYPTO_83_SW_SWSHE_ID_KEY_NUM) )
            {
                if( u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
                {
                    if( Crypto_83_sw_Swshe_u1RamKeyStatus == CRYPTO_83_SW_SWSHE_RAMKEY_STORED )
                    {
                        Crypto_83_sw_SWSHE_LoadRamKey( &st_Info );
                    }
                    else
                    {
                        u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                    }
                }
                else
                {
                    u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( u1KeyId, &st_Info );
                    if( u1_Ret == (Std_ReturnType)E_OK )
                    {
                        /* Key slot counter, KU Flag  check. 0:Encryption,1:MAC */
                        if( st_Info.u4Counter == (uint32)0x00000000U )
                        {
                            u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                        }
                        else if( st_Info.u1Flag_ku != (uint8)0x00U )
                        {
                            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
                        }
                        else
                        {
                            /* No Processing */
                        }
                    }
                }
                if( u1_Ret == (Std_ReturnType)E_OK )
                {
                    u1_Ret = Crypto_83_sw_SWSHE_AES128_DecEcb( &st_Info.u1Data[0], ptCipher, ptPlain );
                }
                (void)Crypto_83_sw_SecStd_MemSet( &st_Info, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    /* 0 sets of output parameters. */
    if( (u1_Ret != (Std_ReturnType)E_OK) && (ptPlain != NULL_PTR) )
    {
        (void)Crypto_83_sw_SecStd_MemSet( ptPlain, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_BLOCK_SIZE ); /* no return check required */
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdEncCbc                             */
/* Description   | CBC Encryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  u1KeyId    : Key ID(4 - 14)                        */
/*               | (in)  ptIvdata   : IV start address(16byte)              */
/*               | (in)  u4PlainLen : Plain text Block size                 */
/*               | (in)  ptPlain    : Plain text start address              */
/*               | (out) ptCipher   : Cipher test start address             */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_KEY_NOT_AVAILABLE                          */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CRYPTO_E_KEY_EMPTY                                      */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdEncCbc
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4PlainLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
)
{
    Crypto_83_sw_Swshe_KeyInfoType  st_Info;
    uint32                          u4_Length;
    Std_ReturnType                  u1_Ret = (Std_ReturnType)E_OK;

    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( (ptIvdata != NULL_PTR)
          && (ptPlain != NULL_PTR)
          && (ptCipher != NULL_PTR)
          && (u4PlainLen > (uint8)0x00U)
          && (u4PlainLen <= CRYPTO_83_SW_SWSHE_CBC_MAXBLK_NUM) )
        {
            /* Confirmation of the use key ID */
            if( (CRYPTO_83_SW_SWSHE_KID_BT_MAC < u1KeyId) && (u1KeyId < CRYPTO_83_SW_SWSHE_ID_KEY_NUM) )
            {
                if( u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
                {
                    if( Crypto_83_sw_Swshe_u1RamKeyStatus == CRYPTO_83_SW_SWSHE_RAMKEY_STORED )
                    {
                        Crypto_83_sw_SWSHE_LoadRamKey( &st_Info );
                    }
                    else
                    {
                        u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                    }
                }
                else
                {
                    u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( u1KeyId, &st_Info );
                    if( u1_Ret == (Std_ReturnType)E_OK )
                    {
                        /* Key slot counter, KU Flag  check. 0:Encryption,1:MAC */
                        if( st_Info.u4Counter == (uint32)0x00000000U )
                        {
                            u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                        }
                        else if( st_Info.u1Flag_ku != (uint8)0x00U )
                        {
                            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
                        }
                        else
                        {
                            /* No Processing */
                        }
                    }
                }
                if( u1_Ret == (Std_ReturnType)E_OK )
                {
                    u4_Length = u4PlainLen << CRYPTO_83_SW_SWSHE_BIT_4;
                    u1_Ret = Crypto_83_sw_SWSHE_AES128_EncCbc( &st_Info.u1Data[0], ptIvdata, u4_Length, ptPlain, ptCipher );
                }
                (void)Crypto_83_sw_SecStd_MemSet( &st_Info, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdDecCbc                             */
/* Description   | CBC Decryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  u1KeyId     : Key ID(4 - 14)                       */
/*               | (in)  ptIvdata    : IV start address(16byte)             */
/*               | (in)  u4CipherLen : Cipher text Block size               */
/*               | (in)  ptCipher    : Cipher text start address            */
/*               | (out) ptPlain     : Plain text start address             */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_KEY_NOT_AVAILABLE                          */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CRYPTO_E_KEY_EMPTY                                      */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdDecCbc
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4CipherLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
)
{
    Crypto_83_sw_Swshe_KeyInfoType  st_Info;
    uint32                          u4_Length;
    Std_ReturnType                  u1_Ret = (Std_ReturnType)E_OK;

    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( (ptIvdata != NULL_PTR)
          && (ptCipher != NULL_PTR)
          && (ptPlain != NULL_PTR)
          && (u4CipherLen > (uint8)0x00U)
          && (u4CipherLen <= CRYPTO_83_SW_SWSHE_CBC_MAXBLK_NUM) )
        {
            /* Confirmation of the use key ID */
            if( (CRYPTO_83_SW_SWSHE_KID_BT_MAC < u1KeyId) && (u1KeyId < CRYPTO_83_SW_SWSHE_ID_KEY_NUM) )
            {
                if( u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
                {
                    if( Crypto_83_sw_Swshe_u1RamKeyStatus == CRYPTO_83_SW_SWSHE_RAMKEY_STORED )
                    {
                        Crypto_83_sw_SWSHE_LoadRamKey( &st_Info );
                    }
                    else
                    {
                        u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                    }
                }
                else
                {
                    u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( u1KeyId, &st_Info );
                    if( u1_Ret == (Std_ReturnType)E_OK )
                    {
                        /* Key slot counter, KU Flag  check. 0:Encryption,1:MAC */
                        if( st_Info.u4Counter == (uint32)0x00000000U )
                        {
                            u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                        }
                        else if( st_Info.u1Flag_ku != (uint8)0x00U )
                        {
                            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
                        }
                        else
                        {
                            /* No Processing */
                        }
                    }
                }
                if( u1_Ret == (Std_ReturnType)E_OK )
                {
                    u4_Length = u4CipherLen << CRYPTO_83_SW_SWSHE_BIT_4;
                    u1_Ret = Crypto_83_sw_SWSHE_AES128_DecCbc( &st_Info.u1Data[0], ptIvdata, u4_Length, ptCipher, ptPlain );
                }
                (void)Crypto_83_sw_SecStd_MemSet( &st_Info, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdGenerateMac                        */
/* Description   | CMAC Generate                                            */
/* Preconditions | -                                                        */
/* Parameters    | (in)  u1KeyId  : Key ID(4 - 14)                          */
/*               | (in)  u4MsgLen : Message data length (bit)               */
/*               | (in)  ptMsg    : Message start address                   */
/*               | (out) ptMac    : MAC start address(16byte)               */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_KEY_NOT_AVAILABLE                          */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CRYPTO_E_KEY_EMPTY                                      */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdGenerateMac
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    Crypto_83_sw_ConstR uint32 u4MsgLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMsg,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMac

)
{
    Crypto_83_sw_Swshe_KeyInfoType    st_Info;
    Std_ReturnType                    u1_Ret = (Std_ReturnType)E_OK;

    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( (ptMsg != NULL_PTR)
          && (ptMac != NULL_PTR)
          && (u4MsgLen >= CRYPTO_83_SW_SWSHE_CMAC_MINBIT_NUM)
          && (u4MsgLen <= CRYPTO_83_SW_SWSHE_CMAC_MAXBIT_NUM) )
        {
            /* Confirmation of the use key ID */
            if( (CRYPTO_83_SW_SWSHE_KID_BT_MAC < u1KeyId) && (u1KeyId < CRYPTO_83_SW_SWSHE_ID_KEY_NUM) )
            {
                if( u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
                {
                    if( Crypto_83_sw_Swshe_u1RamKeyStatus == CRYPTO_83_SW_SWSHE_RAMKEY_STORED )
                    {
                        Crypto_83_sw_SWSHE_LoadRamKey( &st_Info );
                    }
                    else
                    {
                        u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                    }
                }
                else
                {
                    u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( u1KeyId, &st_Info );
                    if( u1_Ret == (Std_ReturnType)E_OK )
                    {
                        /* Key slot counter, KU Flag  check. 0:Encryption,1:MAC */
                        if( st_Info.u4Counter == (uint32)0x00000000U )
                        {
                            u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                        }
                        else if( st_Info.u1Flag_ku != CRYPTO_83_SW_SWSHE_KU_ENABLE )
                        {
                            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
                        }
                        else
                        {
                            /* No Processing */
                        }
                    }
                }
                if( u1_Ret == (Std_ReturnType)E_OK )
                {
                    u1_Ret = Crypto_83_sw_SWSHE_AES128_CMac( &st_Info.u1Data[0], ptMsg, u4MsgLen >> CRYPTO_83_SW_SWSHE_BIT_TO_BYTE_SHIFT, ptMac );
                }
                (void)Crypto_83_sw_SecStd_MemSet( &st_Info, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    /* 0 sets of output parameters. */
    if( (u1_Ret != (Std_ReturnType)E_OK) && (ptMac != NULL_PTR) )
    {
        (void)Crypto_83_sw_SecStd_MemSet( ptMac, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_BLOCK_SIZE ); /* no return check required */
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdVerifyMac                          */
/* Description   | CMAC Verify                                              */
/* Preconditions | -                                                        */
/* Parameters    | (in)  u1KeyId  : Key ID(2,4 - 14)                        */
/*               | (in)  u4MsgLen : Message data length (bit)               */
/*               | (in)  ptMsg    : Message start address                   */
/*               | (in)  u1MacLen : MAC verify length(7bit)(0x00 = 128bit)  */
/*               | (in)  ptMac    : MAC start address                       */
/*               | (out) ptStat   : Verify result                           */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_KEY_NOT_AVAILABLE                          */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CRYPTO_E_KEY_EMPTY                                      */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdVerifyMac
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    Crypto_83_sw_ConstR uint32 u4MsgLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMsg,
    uint8 u1MacLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMac,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptStat
)
{
    Crypto_83_sw_Swshe_KeyInfoType  st_Info;
    uint8                           u1_CmpMac[CRYPTO_83_SW_SWSHE_CMAC_SIZE];
    sint32                          s4_CmpRet;
    Std_ReturnType                  u1_Ret = (Std_ReturnType)E_OK;
    uint8                           u1_Count;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_CMAC_SIZE; u1_Count++ )
    {
        u1_CmpMac[u1_Count] = (uint8)0x00U;
    }
    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( (ptMsg != NULL_PTR)
          && (ptMac != NULL_PTR)
          && (ptStat != NULL_PTR)
          && (u4MsgLen >= CRYPTO_83_SW_SWSHE_CMAC_MINBIT_NUM)
          && (u4MsgLen <= CRYPTO_83_SW_SWSHE_CMAC_MAXBIT_NUM)
          && (u1MacLen <= CRYPTO_83_SW_SWSHE_CMAC_MAX_MACSIZE_NUM) )
        {
            /* Confirmation of the use key ID */
            if( ((CRYPTO_83_SW_SWSHE_KID_BT_MAC < u1KeyId) && (u1KeyId < CRYPTO_83_SW_SWSHE_ID_KEY_NUM)) || (u1KeyId == CRYPTO_83_SW_SWSHE_KID_BT_MAC_KEY) )
            {
                if( u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
                {
                    if( Crypto_83_sw_Swshe_u1RamKeyStatus == CRYPTO_83_SW_SWSHE_RAMKEY_STORED )
                    {
                        Crypto_83_sw_SWSHE_LoadRamKey( &st_Info );
                    }
                    else
                    {
                        u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                    }
                }
                else
                {
                    u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( u1KeyId, &st_Info );
                    if( u1KeyId == CRYPTO_83_SW_SWSHE_KID_BT_MAC_KEY )
                    {
                        /* In BOOT_MAC_KEY, KU flag does not exist, but Mac inspection is possible. */
                        st_Info.u1Flag_ku = CRYPTO_83_SW_SWSHE_KU_ENABLE;
                    }
                    if( u1_Ret == (Std_ReturnType)E_OK )
                    {
                        /* Key slot counter, KU Flag  check. 0:Encryption,1:MAC */
                        if( st_Info.u4Counter == (uint32)0x00000000U )
                        {
                            u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                        }
                        else if( st_Info.u1Flag_ku != CRYPTO_83_SW_SWSHE_KU_ENABLE )
                        {
                            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
                        }
                        else
                        {
                            /* No Processing */
                        }
                    }
                }
                if( u1_Ret == (Std_ReturnType)E_OK )
                {
                    u1_Ret = Crypto_83_sw_SWSHE_AES128_CMac( &st_Info.u1Data[0], ptMsg,  u4MsgLen >> CRYPTO_83_SW_SWSHE_BIT_TO_BYTE_SHIFT, &u1_CmpMac[0] );
                }
                if( u1_Ret == (Std_ReturnType)E_OK )
                {

                     /* The number of bits to compare, starting from the leftmost bit of the MAC, */
                     /* are given in the parameter MAC_LENGTH, */
                     /* the value 0 is not allowed and is interpreted by SHE as tocompare all bits of the MAC. */

                    if( u1MacLen == (uint8)0x00U )
                    {
                        s4_CmpRet = Crypto_83_sw_SWSHE_BitCmp( ptMac, &u1_CmpMac[0], CRYPTO_83_SW_SWSHE_CMAC_SIZE_BIT );
                    }
                    else
                    {
                        s4_CmpRet = Crypto_83_sw_SWSHE_BitCmp( ptMac, &u1_CmpMac[0], (uint32)u1MacLen );
                    }
                    if( s4_CmpRet != (sint32)E_OK )
                    {
                        *ptStat = (uint8)CRYPTO_83_SW_SWSHE_CMAC_VER_NG;
                    }
                    else
                    {
                        *ptStat = (uint8)CRYPTO_83_SW_SWSHE_CMAC_VER_OK;
                    }
                }
                (void)Crypto_83_sw_SecStd_MemSet( &st_Info, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    /* 0 sets of output parameters. */
    if( (u1_Ret != (Std_ReturnType)E_OK) && (ptStat != NULL_PTR) )
    {
        *ptStat = (uint8)0x00U;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdLoadKey                            */
/* Description   | CMD_LOAD_KEY                                             */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptM1 : M1 data start address(16byte)               */
/*               | (in)  ptM2 : M2 data start address(32byte)               */
/*               | (in)  ptM3 : M3 data start address(16byte)               */
/*               | (out) ptM4 : M4 data start address(32byte)               */
/*               | (out) ptM5 : M5 data start address(16byte)               */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_KEY_NOT_AVAILABLE                          */
/*               |  CSM_AB_E_SHE_KEY_INVALID                                */
/*               |  CRYPTO_E_KEY_EMPTY                                      */
/*               |  CSM_AB_E_SHE_KEY_WRITE_PROTECTED                        */
/*               |  CSM_AB_E_SHE_KEY_UPDATE_ERROR                           */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdLoadKey
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM1,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM2,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM3,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM4,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM5
)
{
    Crypto_83_sw_Swshe_KeyInfoType   st_KeyTmp;
    Crypto_83_sw_Swshe_KeyInfoType   st_KeyNew;
    Crypto_83_sw_Swshe_MemUpdate     st_ConstructMup;
    Std_ReturnType                   u1_Ret;
    uint8                            u1_Count;

    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( (ptM1 != NULL_PTR)
          && (ptM2 != NULL_PTR)
          && (ptM3 != NULL_PTR)
          && (ptM4 != NULL_PTR)
          && (ptM5 != NULL_PTR) )
        {
            st_KeyTmp.u1Id         = (uint8)0x00U;
            st_KeyTmp.u1Flag_wp    = (uint8)0x00U;
            st_KeyTmp.u1Flag_bp    = (uint8)0x00U;
            st_KeyTmp.u1Flag_dp    = (uint8)0x00U;
            st_KeyTmp.u1Flag_ku    = (uint8)0x00U;
            st_KeyTmp.u1Flag_wc    = (uint8)0x00U;
            st_KeyTmp.u1Flag_plain = (uint8)0x00U;
            st_KeyTmp.u1Flag_rsv1  = (uint8)0x00U;
            st_KeyTmp.u4Counter    = (uint32)0x00U;

            st_KeyNew.u1Id         = (uint8)0x00U;
            st_KeyNew.u1Flag_wp    = (uint8)0x00U;
            st_KeyNew.u1Flag_bp    = (uint8)0x00U;
            st_KeyNew.u1Flag_dp    = (uint8)0x00U;
            st_KeyNew.u1Flag_ku    = (uint8)0x00U;
            st_KeyNew.u1Flag_wc    = (uint8)0x00U;
            st_KeyNew.u1Flag_plain = (uint8)0x00U;
            st_KeyNew.u1Flag_rsv1  = (uint8)0x00U;
            st_KeyNew.u4Counter    = (uint32)0x00U;

            st_ConstructMup.ptM1         = ptM1;
            st_ConstructMup.ptM2         = ptM2;
            st_ConstructMup.ptM3         = ptM3;
            st_ConstructMup.u1KeyId      = (uint8)0x00U;
            st_ConstructMup.u1AuthId     = (uint8)0x00U;
            st_ConstructMup.u1IsWildCard = (uint8)0x00U;

            for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE; u1_Count++ )
            {
                st_KeyTmp.u1Data[u1_Count] = (uint8)0x00U;
                st_KeyNew.u1Data[u1_Count] = (uint8)0x00U;
                st_ConstructMup.u1K1[u1_Count] = (uint8)0x00U;
                st_ConstructMup.u1K2[u1_Count] = (uint8)0x00U;
                st_ConstructMup.u1K3[u1_Count] = (uint8)0x00U;
                st_ConstructMup.u1K4[u1_Count] = (uint8)0x00U;
            }

            for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_UID_ADD_ALIGNED_SIZE; u1_Count++ )
            {
                st_ConstructMup.u1Uid[u1_Count] = (uint8)0x00U;
            }

            /* Parse M1 */
            u1_Ret = Crypto_83_sw_SWSHE_ParseM1( &st_ConstructMup, &st_KeyTmp );
            if( u1_Ret == (Std_ReturnType)E_OK )
            {
                /* Parse M3 */
                u1_Ret = Crypto_83_sw_SWSHE_ParseM3( &st_ConstructMup, &st_KeyTmp );
            }
            if( u1_Ret == (Std_ReturnType)E_OK )
            {
                /* Parse M2 */
                u1_Ret = Crypto_83_sw_SWSHE_ParseM2( &st_ConstructMup, (Crypto_83_sw_ConstR Crypto_83_sw_Swshe_KeyInfoType*)&st_KeyTmp, &st_KeyNew );
            }
            /* Generate M4 */
            if( u1_Ret == (Std_ReturnType)E_OK )
            {
                u1_Ret = Crypto_83_sw_SWSHE_GenerateM4( &st_ConstructMup.u1Uid[0], st_ConstructMup.u1KeyId, st_ConstructMup.u1AuthId, &st_KeyNew, &st_ConstructMup.u1K3[0], ptM4 );
                /* Generate M5 */
                if( u1_Ret == (Std_ReturnType)E_OK )
                {
                    u1_Ret = Crypto_83_sw_SWSHE_GenerateM5( ptM4, &st_ConstructMup.u1K4[0], ptM5 );
                    (void)Crypto_83_sw_SecStd_MemSet( &ptM5[CRYPTO_83_SW_SWSHE_M5_KEYINFO_POSITION], (uint8)0x00U, CRYPTO_83_SW_SWSHE_M5_KEYINFO_SIZE ); /* no return check required */
                    ptM5[CRYPTO_83_SW_SWSHE_M5_KEYINFO_POSITION] = st_KeyNew.u1Id;
                    ptM5[CRYPTO_83_SW_SWSHE_M5_FID_WP_POSITION]  = st_KeyNew.u1Flag_wp;
                    ptM5[CRYPTO_83_SW_SWSHE_M5_FID_BP_POSITION]  = st_KeyNew.u1Flag_bp;
                    ptM5[CRYPTO_83_SW_SWSHE_M5_FID_DP_POSITION]  = st_KeyNew.u1Flag_dp;
                    ptM5[CRYPTO_83_SW_SWSHE_M5_FID_KU_POSITION]  = st_KeyNew.u1Flag_ku;
                    ptM5[CRYPTO_83_SW_SWSHE_M5_FID_WC_POSITION]  = st_KeyNew.u1Flag_wc;
                    ptM5[CRYPTO_83_SW_SWSHE_M5_FID_PL_POSITION]  = st_KeyNew.u1Flag_plain;
                    ptM5[CRYPTO_83_SW_SWSHE_M5_FID_RSV_POSITION] = st_KeyNew.u1Flag_rsv1;

                    ptM5[CRYPTO_83_SW_SWSHE_M5_KI_CID_1BYTE_POS] = (uint8)((st_KeyNew.u4Counter >> CRYPTO_83_SW_SWSHE_BIT_24));
                    ptM5[CRYPTO_83_SW_SWSHE_M5_KI_CID_2BYTE_POS] = (uint8)((st_KeyNew.u4Counter >> CRYPTO_83_SW_SWSHE_BIT_16) & CRYPTO_83_SW_SWSHE_MASK_1BYTE);
                    ptM5[CRYPTO_83_SW_SWSHE_M5_KI_CID_3BYTE_POS] = (uint8)((st_KeyNew.u4Counter >> CRYPTO_83_SW_SWSHE_BIT_8 ) & CRYPTO_83_SW_SWSHE_MASK_1BYTE);
                    ptM5[CRYPTO_83_SW_SWSHE_M5_KI_CID_4BYTE_POS] = (uint8)(st_KeyNew.u4Counter & CRYPTO_83_SW_SWSHE_MASK_1BYTE);

                    (void)Crypto_83_sw_SecStd_MemCpy(&ptM5[CRYPTO_83_SW_SWSHE_M5_KI_DATA_POS], &st_KeyNew.u1Data, (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE); /* no return check required */
                }
                else
                {
                    u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
                }
            }
            /* Clear KeyInfo */
            (void)Crypto_83_sw_SecStd_MemSet( &st_ConstructMup, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_MemUpdate) ); /* no return check required */
            (void)Crypto_83_sw_SecStd_MemSet( &st_KeyTmp, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            (void)Crypto_83_sw_SecStd_MemSet( &st_KeyNew, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    /* 0 sets of output parameters. */
    if( u1_Ret != (Std_ReturnType)E_OK )
    {
        if( ptM4 != NULL_PTR )
        {
            (void)Crypto_83_sw_SecStd_MemSet( ptM4, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_M4_SIZE ); /* no return check required */
        }
        if( ptM5 != NULL_PTR )
        {
            (void)Crypto_83_sw_SecStd_MemSet( ptM5, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_M5_SIZE + CRYPTO_83_SW_SWSHE_M5_KEYINFO_SIZE ); /* no return check required */
        }
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdLoadPlainKey                       */
/* Description   | RAM Key Load                                             */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptKey : Key data start address(16byte)             */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdLoadPlainKey
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey
)
{
    Crypto_83_sw_Swshe_KeyInfoType   st_Key;
    Std_ReturnType                   u1_Ret = (Std_ReturnType)E_OK;

    /* Check SWSHE status */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        /* Set SREG=BUSY */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;

        /* Parameter check */
        if( ptKey != NULL_PTR )
        {
            (void)Crypto_83_sw_SecStd_MemSet( &st_Key, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
            st_Key.u1Flag_plain = CRYPTO_83_SW_SWSHE_PLN_ENABLE;
            (void)Crypto_83_sw_SecStd_MemCpy( &st_Key.u1Data[0], ptKey, (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE ); /* no return check required */
            Crypto_83_sw_SWSHE_StoreRamKey( &st_Key );
            (void)Crypto_83_sw_SecStd_MemSet( &st_Key, (uint8)0x00U, sizeof(Crypto_83_sw_Swshe_KeyInfoType) ); /* no return check required */
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
        }

        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;

    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdInitRng                            */
/* Description   | Random number generator initialization                   */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdInitRng
(
    void
)
{
    Std_ReturnType       u1_Ret;

    /* External random */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;
        u1_Ret = Crypto_83_sw_SWSHE_InitRandom();
        if( u1_Ret == (Std_ReturnType)E_OK )
        {
            Crypto_83_sw_Swshe_u1SregRndInit = CRYPTO_83_SW_SWSHE_SREG_SET;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdExtendSeed                         */
/* Description   | Random number seed setting                               */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptEntropy : Seed start address(16byte)             */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_RNG_SEED                                   */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdExtendSeed
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptEntropy
)
{
    Std_ReturnType   u1_Ret;

    /* External random */
    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;
        if( Crypto_83_sw_Swshe_u1SregRndInit == CRYPTO_83_SW_SWSHE_SREG_SET )
        {
            /* NULL check */
            if( ptEntropy != NULL_PTR )
            {
                u1_Ret = Crypto_83_sw_SWSHE_ReseedRandom( ptEntropy );
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_RNG_SEED;
        }

        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CmdRnd                                */
/* Description   | Random number generation                                 */
/* Preconditions | -                                                        */
/* Parameters    | (out)  ptRnd : Random number start address(16byte)       */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_SEQUENCE_ERROR                             */
/*               |  CSM_AB_E_SHE_RNG_SEED                                   */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/*               |  CRYPTO_E_BUSY                                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdRnd
(
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptRnd
)
{
    Std_ReturnType   u1_Ret;

    if( Crypto_83_sw_Swshe_u1SregBusy == CRYPTO_83_SW_SWSHE_SREG_CLEAR )
    {
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_SET;
        if( Crypto_83_sw_Swshe_u1SregRndInit == CRYPTO_83_SW_SWSHE_SREG_SET )
        {
            /* NULL check */
            if( ptRnd != NULL_PTR )
            {
                u1_Ret = Crypto_83_sw_SWSHE_GenerateRandom( ptRnd );
            }
            else
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_RNG_SEED;
        }
        /* Clear BUSY of SREG */
        Crypto_83_sw_Swshe_u1SregBusy = CRYPTO_83_SW_SWSHE_SREG_CLEAR;
    }
    else
    {
        u1_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }

    /* 0 sets of output parameters. */
    if( (u1_Ret != (Std_ReturnType)E_OK) && (ptRnd != NULL_PTR) )
    {
        (void)Crypto_83_sw_SecStd_MemSet( ptRnd, (uint8)0x00U, (uint32)CRYPTO_83_SW_SWSHE_BLOCK_SIZE ); /* no return check required */
    }

    return u1_Ret;
}

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_GetErrorStatus                        */
/* Description   | Check ram data.                                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GetErrorStatus
(
    void
)
{
    Std_ReturnType              u1_Ret;
    uint8                       u1_SregBusyTmp;
    uint8                       u1_SregRndInitTmp;

    u1_Ret = Crypto_83_sw_SWSHE_CacheGetErrorStatus();

    if ( u1_Ret == (Std_ReturnType)E_OK )
    {
        u1_SregBusyTmp    = Crypto_83_sw_Swshe_u1SregBusy;
        u1_SregRndInitTmp = Crypto_83_sw_Swshe_u1SregRndInit;

        if ( ((u1_SregBusyTmp    != CRYPTO_83_SW_SWSHE_SREG_CLEAR) && (u1_SregBusyTmp    != CRYPTO_83_SW_SWSHE_SREG_SET) ) ||
             ((u1_SregRndInitTmp != CRYPTO_83_SW_SWSHE_SREG_CLEAR) && (u1_SregRndInitTmp != CRYPTO_83_SW_SWSHE_SREG_SET) ) )
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_MEMORY_FAILURE;
        }
    }

    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        u1_Ret = Crypto_83_sw_SWSHE_IfCryptoGetErrorStatus();
    }

    return u1_Ret;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_KeyDerive                             */
/* Description   | Key Derive Miyaguchi-Preneel                             */
/* Preconditions | -                                                        */
/* Parameters    | ptInput1 :                                               */
/*               | ptInput2 :                                               */
/*               | ptOutput :                                               */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_KeyDerive
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptInput1,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptInput2,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptOutput
)
{
    Std_ReturnType               u1_Ret;
    uint8                        u1_Zero[CRYPTO_83_SW_SWSHE_KEY_SIZE];
    uint8                        u1_Count;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE; u1_Count++ )
    {
        u1_Zero[u1_Count] = (uint8)0x00U;
    }

    u1_Ret = Crypto_83_sw_SWSHE_MiyaguchiPreneel( ptInput1, &u1_Zero[0], &u1_Zero[0] );
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        u1_Ret = Crypto_83_sw_SWSHE_MiyaguchiPreneel( ptInput2, &u1_Zero[0], ptOutput );
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_MiyaguchiPreneel                      */
/* Description   | MiyaguchiPreneel Compression                             */
/* Preconditions | -                                                        */
/* Parameters    | ptInput1 :                                               */
/*               | ptKey    :                                               */
/*               | ptOutput :                                               */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_MiyaguchiPreneel
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptInput,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptKey,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptOutput
)
{
    uint8                        u1_Num;
    Std_ReturnType               u1_Ret;
    uint8                        u1_Buff[CRYPTO_83_SW_SWSHE_KEY_SIZE];
    uint8                        u1_Count;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE; u1_Count++ )
    {
        u1_Buff[u1_Count] = (uint8)0x00U;
    }

    u1_Ret = Crypto_83_sw_SWSHE_AES128_EncEcb( ptKey, ptInput, &u1_Buff[0] );
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        for( u1_Num = (uint8)0x00U; u1_Num < (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE; u1_Num++ )
        {
            ptOutput[u1_Num] = ptKey[u1_Num] ^ ptInput[u1_Num] ^ u1_Buff[u1_Num];
        }
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_ParseM1                               */
/* Description   | Parse M1                                                 */
/* Preconditions | -                                                        */
/* Parameters    | ptMUP    :                                               */
/*               | ptKeyTmp :                                               */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ParseM1
(
    P2VAR(Crypto_83_sw_Swshe_MemUpdate, AUTOMATIC, AUTOMATIC) ptMUP,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyTmp
)
{
    Std_ReturnType u1_Ret;

    /* Check M1 */
    u1_Ret = Crypto_83_sw_SWSHE_CheckM1( (Crypto_83_sw_ConstR uint8*) ptMUP->ptM1, &ptMUP->u1AuthId, &ptMUP->u1KeyId, &ptMUP->u1IsWildCard );
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        /* Check UpdateKey slot */
        if( ptMUP->u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
        {
            Crypto_83_sw_SWSHE_LoadRamKey( ptKeyTmp );
        }
        else
        {
            u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( ptMUP->u1KeyId, ptKeyTmp );
        }
        if( u1_Ret == (Std_ReturnType)E_OK )
        {
            /* Check write protect */
            if( ptKeyTmp->u1Flag_wp == CRYPTO_83_SW_SWSHE_WP_ENABLE )
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_WRITE_PROTECTED;
            }
        }
        /* Check AuthKey slot */
        if( u1_Ret == (Std_ReturnType)E_OK )
        {
            u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( ptMUP->u1AuthId, ptKeyTmp );
            if( u1_Ret == (Std_ReturnType)E_OK )
            {
                /* Registration check of the Auth key */
                if( (ptKeyTmp->u4Counter == (uint32)0x00000000U) && (ptMUP->u1AuthId != ptMUP->u1KeyId) )
                {
                    u1_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
                }
            }
        }
        if( u1_Ret == (Std_ReturnType)E_OK )
        {
            /* Derive K1 */
            u1_Ret = Crypto_83_sw_SWSHE_KeyDerive( &ptKeyTmp->u1Data[0], &Crypto_83_sw_Swshe_u1KeyUpdateEncC[0], &ptMUP->u1K1[0] );
            /* Derive K2 */
            if( u1_Ret == (Std_ReturnType)E_OK )
            {
                u1_Ret = Crypto_83_sw_SWSHE_KeyDerive( &ptKeyTmp->u1Data[0], &Crypto_83_sw_Swshe_u1KeyUpdateMacC[0], &ptMUP->u1K2[0] );
            }
        }
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_ParseM2                               */
/* Description   | Parse M2                                                 */
/* Preconditions | -                                                        */
/* Parameters    | ptMUP    :                                               */
/*               | ptKeyTmp :                                               */
/*               | ptKeyNew :                                               */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ParseM2
(
    P2VAR(Crypto_83_sw_Swshe_MemUpdate, AUTOMATIC, AUTOMATIC) ptMUP,
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyTmp,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyNew
)
{
    Std_ReturnType u1_Ret;

    /* Check M2 */
    u1_Ret = Crypto_83_sw_SWSHE_CheckM2( (Crypto_83_sw_ConstR uint8*) ptMUP->ptM2, (Crypto_83_sw_ConstR uint8*) &ptMUP->u1K1[0], ptKeyNew );
    /* Check CID */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        if( ptKeyTmp->u4Counter >= ptKeyNew->u4Counter )
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_UPDATE_ERROR;
        }
        else
        {
            /* Flag filter */
            if( ptMUP->u1KeyId < CRYPTO_83_SW_SWSHE_KID_KEY_1 )
            {
                ptKeyNew->u1Flag_ku = CRYPTO_83_SW_SWSHE_U1_ZERO;
                if( ptMUP->u1KeyId > CRYPTO_83_SW_SWSHE_KID_MASTER_ECU_KEY )
                {
                    ptKeyNew->u1Flag_bp = CRYPTO_83_SW_SWSHE_U1_ZERO;
                }
            }
        }
    }
    /* Write Update key */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        ptKeyNew->u1Id = ptMUP->u1KeyId;
        if( ptMUP->u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
        {
            /* Disable PLAIN FLAG */
            ptKeyNew->u1Flag_plain = CRYPTO_83_SW_SWSHE_U1_ZERO;
            Crypto_83_sw_SWSHE_StoreRamKey( ptKeyNew );
        }
    }
    /* Derive K3 */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        u1_Ret = Crypto_83_sw_SWSHE_KeyDerive( &ptKeyNew->u1Data[0], &Crypto_83_sw_Swshe_u1KeyUpdateEncC[0], &ptMUP->u1K3[0] );
        /* Derive K4 */
        if( u1_Ret == (Std_ReturnType)E_OK )
        {
            u1_Ret = Crypto_83_sw_SWSHE_KeyDerive( &ptKeyNew->u1Data[0], &Crypto_83_sw_Swshe_u1KeyUpdateMacC[0], &ptMUP->u1K4[0] );
        }
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_ParseM3                               */
/* Description   | Parse M3                                                 */
/* Preconditions | -                                                        */
/* Parameters    | ptMUP    :                                               */
/*               | ptKeyTmp :                                               */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ParseM3
(
    P2VAR(Crypto_83_sw_Swshe_MemUpdate, AUTOMATIC, AUTOMATIC) ptMUP,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKeyTmp
)
{
    sint32                       s4_CmpRet;
    Std_ReturnType               u1_Ret;

    /* Check M3 */
    u1_Ret = Crypto_83_sw_SWSHE_CheckM3( (Crypto_83_sw_ConstR uint8*) ptMUP->ptM1, (Crypto_83_sw_ConstR uint8*) ptMUP->ptM2, (Crypto_83_sw_ConstR uint8*) &ptMUP->u1K2[0], (Crypto_83_sw_ConstR uint8*) ptMUP->ptM3 );
    /* Get UID */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        /* Check wildcard and UID */
        u1_Ret = Crypto_83_sw_SWSHE_CacheLoadUid( &ptMUP->u1Uid[0] );
    }
    /* Check wildcard and UID */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        if( ptMUP->u1KeyId == CRYPTO_83_SW_SWSHE_KID_RAM_KEY )
        {
            Crypto_83_sw_SWSHE_LoadRamKey( ptKeyTmp );
        }
        else
        {
            u1_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( ptMUP->u1KeyId, ptKeyTmp );
        }
        if( u1_Ret == (Std_ReturnType)E_OK )
        {
            /* Check wildcard */
            if( ptMUP->u1IsWildCard == CRYPTO_83_SW_SWSHE_WC_ENABLE )
            {
                if( ptKeyTmp->u1Flag_wc == CRYPTO_83_SW_SWSHE_WC_ENABLE )
                {
                    u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_UPDATE_ERROR;
                }
                else
                {
                    /* Skip UID Comparison */
                }
            }
            else
            {
                /* Check UID */
                s4_CmpRet = Crypto_83_sw_SecStd_MemCmp( (Crypto_83_sw_ConstR void*) ptMUP->ptM1, (Crypto_83_sw_ConstR void*) &ptMUP->u1Uid[0], (uint32)CRYPTO_83_SW_SWSHE_UID_SIZE );
                if( s4_CmpRet != (sint32)CRYPTO_83_SW_SWSHE_MEMCMP_OK )
                {
                    u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_UPDATE_ERROR;
                }
            }
        }
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CheckM1                               */
/* Description   | Check M1                                                 */
/* Preconditions | -                                                        */
/* Parameters    | ptM1   :                                                 */
/*               | authId :                                                 */
/*               | keyId  :                                                 */
/*               | ptIsWc :                                                 */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CheckM1
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM1,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) authId,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) keyId,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptIsWc
)
{
    sint32                       s4_CmpRet;
    uint8                        u1_Aid = (uint8)(ptM1[CRYPTO_83_SW_SWSHE_M1_ID] & CRYPTO_83_SW_SWSHE_MASK_4BIT);
    uint8                        u1_Kid = ptM1[CRYPTO_83_SW_SWSHE_M1_ID] >> CRYPTO_83_SW_SWSHE_BIT_4;
    uint8                        u1_WcFlg = (uint8)0x00U;
    Std_ReturnType               u1_Ret = (Std_ReturnType)E_OK;
    uint8                        u1WildCard[CRYPTO_83_SW_SWSHE_UID_SIZE];
    uint8                        u1_Count;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_UID_SIZE; u1_Count++ )
    {
        u1WildCard[u1_Count] = (uint8)0x00U;
    }
    if( (u1_Kid < CRYPTO_83_SW_SWSHE_ID_KEY_NUM) && (u1_Aid < CRYPTO_83_SW_SWSHE_ID_KEY_NUM) )
    {
        if( (Crypto_83_sw_Swshe_u2KeyUpdatePolicy[u1_Kid] & ((uint32)CRYPTO_83_SW_SWSHE_MASK_1BIT << u1_Aid)) == (uint16)CRYPTO_83_SW_SWSHE_NO_PERMISSION )
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
        }
    }
    else
    {
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_INVALID;
    }
    /* UID compare */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        /* UID , ALL0 compare */
        s4_CmpRet = Crypto_83_sw_SecStd_MemCmp( ptM1, &u1WildCard[0], (uint32)CRYPTO_83_SW_SWSHE_UID_SIZE );
        if( s4_CmpRet == (sint32)CRYPTO_83_SW_SWSHE_MEMCMP_OK )
        {
            u1_WcFlg = CRYPTO_83_SW_SWSHE_WC_ENABLE;
        }
    }
    /* Store AuthID, KeyID and wildcard */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        *authId = u1_Aid;
        *keyId  = u1_Kid;
        *ptIsWc = u1_WcFlg;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CheckM2                               */
/* Description   | Check M2                                                 */
/* Preconditions | -                                                        */
/* Parameters    | ptM2   :                                                 */
/*               | ptK1   :                                                 */
/*               | ptKey  :                                                 */
/*               | ptIsWc :                                                 */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CheckM2
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM2,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK1,
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey
)
{
    sint32                       s4_CmpRet;
    Std_ReturnType               u1_Ret;
    uint8                        u1_Mout[CRYPTO_83_SW_SWSHE_M2_SIZE];
    uint8                        u1_Zero[CRYPTO_83_SW_SWSHE_M2_CHK_BLOCK_SIZE];
    uint8                        u1_Count;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_M2_SIZE; u1_Count++ )
    {
        u1_Mout[u1_Count] = (uint8)0x00U;
    }
    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_M2_CHK_BLOCK_SIZE; u1_Count++ )
    {
        u1_Zero[u1_Count] = (uint8)0x00U;
    }

    /* M2 decrypto */
    u1_Ret = Crypto_83_sw_SWSHE_AES128_DecCbc( ptK1, &u1_Zero[0], CRYPTO_83_SW_SWSHE_M2_SIZE, ptM2, &u1_Mout[0] );

    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        /* Padding check */
        if( (u1_Mout[CRYPTO_83_SW_SWSHE_M2_PAD_TOP_POSITION] & CRYPTO_83_SW_SWSHE_M2_PAD_MASK) == (uint8)0x00U )
        {
            s4_CmpRet = Crypto_83_sw_SecStd_MemCmp( &u1_Mout[CRYPTO_83_SW_SWSHE_M2_PAD_POSITION], &u1_Zero[0], (uint32)(CRYPTO_83_SW_SWSHE_M2_CHK_BLOCK_SIZE - CRYPTO_83_SW_SWSHE_M2_PAD_POSITION) );
            if( s4_CmpRet != (sint32)CRYPTO_83_SW_SWSHE_MEMCMP_OK )
            {
                u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_UPDATE_ERROR;
            }
        }
        else
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_UPDATE_ERROR;
        }

        if( u1_Ret == (Std_ReturnType)E_OK )
        {
            /* Get CID and FID from M2 */
            ptKey->u4Counter |= ((uint32)u1_Mout[CRYPTO_83_SW_SWSHE_M2_CID_1BYTE_POS] << CRYPTO_83_SW_SWSHE_BIT_24);
            ptKey->u4Counter |= ((uint32)u1_Mout[CRYPTO_83_SW_SWSHE_M2_CID_2BYTE_POS] << CRYPTO_83_SW_SWSHE_BIT_16);
            ptKey->u4Counter |= ((uint32)u1_Mout[CRYPTO_83_SW_SWSHE_M2_CID_3BYTE_POS] << CRYPTO_83_SW_SWSHE_BIT_8);
            ptKey->u4Counter |= (uint32)u1_Mout[CRYPTO_83_SW_SWSHE_M2_CID_4BYTE_POS];
            ptKey->u4Counter = ptKey->u4Counter >> CRYPTO_83_SW_SWSHE_BIT_4;
            ptKey->u1Flag_wp = (uint8)(u1_Mout[CRYPTO_83_SW_SWSHE_M2_FID_1BYTE_POS] >> CRYPTO_83_SW_SWSHE_BIT_3) & CRYPTO_83_SW_SWSHE_MASK_1BIT;
            ptKey->u1Flag_bp = (uint8)(u1_Mout[CRYPTO_83_SW_SWSHE_M2_FID_1BYTE_POS] >> CRYPTO_83_SW_SWSHE_BIT_2) & CRYPTO_83_SW_SWSHE_MASK_1BIT;
            ptKey->u1Flag_dp = (uint8)(u1_Mout[CRYPTO_83_SW_SWSHE_M2_FID_1BYTE_POS] >> CRYPTO_83_SW_SWSHE_BIT_1) & CRYPTO_83_SW_SWSHE_MASK_1BIT;
            ptKey->u1Flag_ku = (uint8)(u1_Mout[CRYPTO_83_SW_SWSHE_M2_FID_1BYTE_POS] & CRYPTO_83_SW_SWSHE_MASK_1BIT);
            ptKey->u1Flag_wc = (uint8)(u1_Mout[CRYPTO_83_SW_SWSHE_M2_FID_2BYTE_POS] >> CRYPTO_83_SW_SWSHE_BIT_7);
            (void)Crypto_83_sw_SecStd_MemCpy( &ptKey->u1Data[0], &u1_Mout[CRYPTO_83_SW_SWSHE_M2_CHK_KEY_POS], (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE ); /* no return check required */
        }
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_CheckM3                               */
/* Description   | Check M3                                                 */
/* Preconditions | -                                                        */
/* Parameters    | ptM1 :                                                   */
/*               | ptM2 :                                                   */
/*               | ptK2 :                                                   */
/*               | ptM3 :                                                   */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CheckM3
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM1,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM2,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK2,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptM3
)
{
    sint32                       s4_CmpRet;
    Std_ReturnType               u1_Ret;
    uint8                        u1_Data[(CRYPTO_83_SW_SWSHE_M1_SIZE + CRYPTO_83_SW_SWSHE_M2_SIZE)];
    uint8                        u1_CmpMac[CRYPTO_83_SW_SWSHE_CMAC_SIZE];
    uint8                        u1_Count;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)(CRYPTO_83_SW_SWSHE_M1_SIZE + CRYPTO_83_SW_SWSHE_M2_SIZE); u1_Count++ )
    {
        u1_Data[u1_Count] = (uint8)0x00U;
    }
    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_CMAC_SIZE; u1_Count++ )
    {
        u1_CmpMac[u1_Count] = (uint8)0x00U;
    }

    /* Data connection of M1 and the M2 */
    (void)Crypto_83_sw_SecStd_MemCpy( &u1_Data[0], ptM1, (uint32)CRYPTO_83_SW_SWSHE_M1_SIZE ); /* no return check required */
    (void)Crypto_83_sw_SecStd_MemCpy( &u1_Data[(CRYPTO_83_SW_SWSHE_M1_SIZE)], ptM2, (uint32)CRYPTO_83_SW_SWSHE_M2_SIZE ); /* no return check required */

    /* Generate MAC from connection data and K2 */
    u1_Ret = Crypto_83_sw_SWSHE_AES128_CMac( ptK2, &u1_Data[0], (CRYPTO_83_SW_SWSHE_M1_SIZE + CRYPTO_83_SW_SWSHE_M2_SIZE), &u1_CmpMac[0] );

    /* Compare the M3 with CMAC */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        s4_CmpRet = Crypto_83_sw_SecStd_MemCmp( ptM3, &u1_CmpMac[0], (uint32)CRYPTO_83_SW_SWSHE_M3_SIZE );
        if( s4_CmpRet != (sint32)CRYPTO_83_SW_SWSHE_MEMCMP_OK )
        {
            u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_KEY_UPDATE_ERROR;
        }
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_GenerateM4                            */
/* Description   | M4 Generate                                              */
/* Preconditions | -                                                        */
/* Parameters    | ptUid    :                                               */
/*               | u1KeyId  :                                               */
/*               | u1AuthId :                                               */
/*               | ptKey    :                                               */
/*               | ptK3     :                                               */
/*               | ptM4     :                                               */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GenerateM4
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptUid,
    Crypto_83_sw_ConstR uint8 u1KeyId,
    Crypto_83_sw_ConstR uint8 u1AuthId,
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK3,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM4
)
{
   /* Padding Array */
    uint8                        u1_CidPad[CRYPTO_83_SW_SWSHE_CID_SIZE];
    uint8                        u1_Count;
    Std_ReturnType               u1_Ret;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_CID_SIZE; u1_Count++ )
    {
        u1_CidPad[u1_Count] = (uint8)0x00U;
    }

   /* CID Padding */
    u1_CidPad[CRYPTO_83_SW_SWSHE_M4_CID_4BYTE_POS] = CRYPTO_83_SW_SWSHE_CID_PADDING;
    u1_CidPad[CRYPTO_83_SW_SWSHE_M4_CID_1BYTE_POS] |= (uint8)((ptKey->u4Counter >> CRYPTO_83_SW_SWSHE_CID_U4_TO_1BYTE_SIFT ) & CRYPTO_83_SW_SWSHE_MASK_1BYTE);
    u1_CidPad[CRYPTO_83_SW_SWSHE_M4_CID_2BYTE_POS] |= (uint8)((ptKey->u4Counter >> CRYPTO_83_SW_SWSHE_CID_U4_TO_2BYTE_SIFT ) & CRYPTO_83_SW_SWSHE_MASK_1BYTE);
    u1_CidPad[CRYPTO_83_SW_SWSHE_M4_CID_3BYTE_POS] |= (uint8)((ptKey->u4Counter >> CRYPTO_83_SW_SWSHE_CID_U4_TO_3BYTE_SIFT ) & CRYPTO_83_SW_SWSHE_MASK_1BYTE);
    u1_CidPad[CRYPTO_83_SW_SWSHE_M4_CID_4BYTE_POS] |= (uint8)((ptKey->u4Counter << CRYPTO_83_SW_SWSHE_CID_U4_TO_4BYTE_SIFT ) & CRYPTO_83_SW_SWSHE_MASK_1BYTE);

    /* Encrypt ECB by K3 and Padding data */
    u1_Ret = Crypto_83_sw_SWSHE_AES128_EncEcb( ptK3, &u1_CidPad[0], &ptM4[CRYPTO_83_SW_SWSHE_M4_AES_POSITION] );

    /* Connect encrypt data with UID, and stored to M4 */
    if( u1_Ret == (Std_ReturnType)E_OK )
    {
        ptM4[CRYPTO_83_SW_SWSHE_M4_ID_POSITION] = ( (uint8)(u1KeyId << CRYPTO_83_SW_SWSHE_BIT_4) | u1AuthId );
        (void)Crypto_83_sw_SecStd_MemCpy( ptM4, ptUid, (uint32)CRYPTO_83_SW_SWSHE_UID_SIZE ); /* no return check required */
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_GenerateM5                            */
/* Description   | M5 Generate                                              */
/* Preconditions | -                                                        */
/* Parameters    | ptM4 :                                                   */
/*               | ptK4 :                                                   */
/*               | ptM5 :                                                   */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GenerateM5
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM4,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptK4,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM5
)
{
    Std_ReturnType   u1_Ret;

    /* M4 and K4 are stored away in CMAC to certification child generation, M5 */
    u1_Ret = Crypto_83_sw_SWSHE_AES128_CMac( ptK4, ptM4, CRYPTO_83_SW_SWSHE_M4_SIZE, ptM5 );

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_LoadRamKey                            */
/* Description   | RAMKEY load                                              */
/* Preconditions | -                                                        */
/* Parameters    | ptKey :                                                  */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_LoadRamKey
(
    P2VAR(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey
)
{
    ptKey->u1Id = CRYPTO_83_SW_SWSHE_KID_RAM_KEY;
    ptKey->u1Flag_wp = CRYPTO_83_SW_SWSHE_U1_ZERO;
    ptKey->u1Flag_bp = CRYPTO_83_SW_SWSHE_U1_ZERO;
    ptKey->u1Flag_dp = CRYPTO_83_SW_SWSHE_U1_ZERO;
    ptKey->u1Flag_ku = CRYPTO_83_SW_SWSHE_U1_ZERO;
    ptKey->u1Flag_wc = CRYPTO_83_SW_SWSHE_U1_ZERO;
    ptKey->u1Flag_rsv1 = CRYPTO_83_SW_SWSHE_U1_ZERO;
    ptKey->u1Flag_plain = Crypto_83_sw_Swshe_stRamKey.u1Flag_plain;
    ptKey->u4Counter = CRYPTO_83_SW_SWSHE_U4_ZERO;
    (void)Crypto_83_sw_SecStd_MemCpy( &ptKey->u1Data[0], (uint8*)(&Crypto_83_sw_Swshe_stRamKey.u1Data[0]), (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE ); /* no return check required */
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_StoreRamKey                           */
/* Description   | RAMKEY store                                             */
/* Preconditions | -                                                        */
/* Parameters    | ptKey :                                                  */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_StoreRamKey
(
    P2CONST(Crypto_83_sw_Swshe_KeyInfoType, AUTOMATIC, AUTOMATIC) ptKey
)
{
    Crypto_83_sw_Swshe_stRamKey.u1Id = CRYPTO_83_SW_SWSHE_KID_RAM_KEY;
    Crypto_83_sw_Swshe_stRamKey.u1Flag_plain = ptKey->u1Flag_plain;
    (void)Crypto_83_sw_SecStd_MemCpy( &Crypto_83_sw_Swshe_stRamKey.u1Data[0], (const uint8*)(&ptKey->u1Data[0]), (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE ); /* no return check required */
    Crypto_83_sw_Swshe_u1RamKeyStatus = CRYPTO_83_SW_SWSHE_RAMKEY_STORED;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_BitCmp                                */
/* Description   | Bit compare from MSB.                                    */
/* Preconditions | -                                                        */
/* Parameters    | ptS1  :                                                  */
/*               | ptS2  :                                                  */
/*               | u4Num :                                                  */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(sint32, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_BitCmp
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptS1,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptS2,
    uint32 u4Num
)
{
    uint32                       u4_Byte;
    uint8                        u1_Bit;
    uint8                        u1_Mask;
    uint8                        u1_BitRet;
    sint32                       s4_Ret = (sint32)E_OK;
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_Cmp1;
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_Cmp2;

    pt_Cmp1 = ptS1;
    pt_Cmp2 = ptS2;
    u4_Byte = u4Num >> CRYPTO_83_SW_SWSHE_BIT_TO_BYTE_SHIFT;
    u1_Bit = (uint8)(u4Num & CRYPTO_83_SW_SWSHE_BITSIZE_MASK);

    while( u4_Byte > CRYPTO_83_SW_SWSHE_U4_ZERO )
    {
        if( *pt_Cmp1 != *pt_Cmp2 )
        {
            s4_Ret = (sint32)*pt_Cmp1 - (sint32)*pt_Cmp2;
            break;
        }
        pt_Cmp1 = &pt_Cmp1[CRYPTO_83_SW_SWSHE_NEXTINDEX];
        pt_Cmp2 = &pt_Cmp2[CRYPTO_83_SW_SWSHE_NEXTINDEX];
        u4_Byte--;
    }
    if( (s4_Ret == CRYPTO_83_SW_SWSHE_BYTECMP_OK) && (u1_Bit != (uint8)0x00U) )
    {
        u1_Mask = (uint8)(~(uint8)((uint8)(CRYPTO_83_SW_SWSHE_BITCMP_MASK << (CRYPTO_83_SW_SWSHE_BITCMP_SHIFT_CNT - u1_Bit)) - CRYPTO_83_SW_SWSHE_BITCMP_MASK));
        u1_BitRet = (*pt_Cmp1 & u1_Mask) - (*pt_Cmp2 & u1_Mask);
        s4_Ret = (sint32)u1_BitRet;
    }

    return s4_Ret;
}

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
