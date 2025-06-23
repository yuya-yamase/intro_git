/**
 * \file  TestApp.c
 * \copyright  DENSO Corporation 2023
*/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "Csm.h"

#include "TestApp.h"

#ifdef TESTAPP_ENABLE_SWLIB
#include "Crypto_83_sw.h"
#endif /* TESTAPP_ENABLE_SWLIB */
#ifdef TESTAPP_ENABLE_CYCURHSM
#include "Crypto_82_Hsm.h"
#endif /* TESTAPP_ENABLE_CYCURHSM */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define TESTAPP_VERSION_INFO_SYMBOL(id)     const volatile uint16 TestApp_Version_## id ## = ## id

/* Key ID */
#define TESTAPP_CSM_KEYID_MASTER                     (0U)
#define TESTAPP_CSM_KEYID_1                          (1U)
#define TESTAPP_CSM_KEYID_UID                        (2U)
#define TP_KEY_SET_M1M2M3                   (1U)
#define TP_KEY_SET_UID                      (1002)
#define TP_KEY_GET_M4M5                     (1003)

#define TP_UID_SIZE                         (15)
#define SQT_MUPKEY_SIZE                     (64)
#define TP_KEY_ASYNC_BUFFER_SIZE            (120)
#define TP_KEY_M4_M5_SIZE                   0x30

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static FUNC(Std_ReturnType, SECOC_CODE) TestApp_InitKey(uint8 testSwitch);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CRYPTO_82_HSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

uint32 TestApp_MainFunction_count = 0;

/* UIDデータ */
uint8  TestApp_TP_Uid[TP_UID_SIZE] = {
    0x00U, 0xa7U, 0xd3U, 0x2eU, 0x78U, 0x00U, 0xcfU, 0x85U, 0x00U, 0x10U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};

/* 鍵更新用に使用する変数 */
uint32 TestApp_KeySet_Time = 0;
uint32 TestApp_KeySet_Switch = 0; /* 鍵登録時にのみ1を設定ください */
uint32 TestApp_KeySet_KeySetElement_Rtn = 0;
uint32 TestApp_KeySet_KeySetValid_Rtn = 0;

#define CRYPTO_82_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Crypto_82_Hsm_MemMap.h"

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CRYPTO_82_HSM_START_SEC_CONST_8BIT
#include "Crypto_82_Hsm_MemMap.h"

/* 鍵情報(M1+M2+M3 の連結データ) */
/* 認証鍵 MASTER_ECU_KEY(1)：00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 */
/* 登録鍵 MASTER_ECU_KEY(1)：00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff */
/* フラグ：DISABLE_WILDCARD */
/* UID：00000000:00000000:00000000:000000 */
/* Cid：1 */
const uint8  TestApp_MasterEcuKey[SQT_MUPKEY_SIZE] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
0x7a, 0x91, 0x5c, 0x89, 0xf5, 0xcc, 0x30, 0x94, 0xbb, 0xe3, 0x33, 0xef, 0xa9, 0x26, 0x0b, 0x69,
0xa8, 0x4f, 0x06, 0x16, 0xf1, 0xc5, 0xa1, 0x3f, 0xe7, 0x62, 0x05, 0xf6, 0x30, 0x42, 0xbc, 0x28,
0xde, 0xa1, 0xce, 0x11, 0x33, 0x06, 0xbc, 0x0b, 0x6b, 0xbf, 0xdb, 0x0b, 0x77, 0xea, 0xf6, 0x26
};
/* 認証鍵 MASTER_ECU_KEY(1)：00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff */
/* 登録鍵 KEY_1(4)         ：0f 0e 0d 0c 0b 0a 09 08 07 06 05 04 03 02 01 00 */
/* フラグ：KEY_USAGE */
/* UID：00000000:00000000:00000000:000000 */
/* Cid：1 */
const uint8  TestApp_Key_4[SQT_MUPKEY_SIZE] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41,
0x4c, 0x4b, 0x34, 0x6f, 0xc4, 0xe8, 0x15, 0x0d, 0xf9, 0x16, 0x25, 0x59, 0xc2, 0x6b, 0x0c, 0xfb,
0x35, 0x5a, 0x15, 0x3e, 0x46, 0x6b, 0xb9, 0x08, 0xa2, 0xba, 0xf9, 0xb6, 0x4a, 0xc6, 0xf3, 0x61,
0x99, 0xb1, 0xe5, 0xb5, 0xff, 0xaf, 0xf6, 0xda, 0xe6, 0xed, 0x28, 0x26, 0x0e, 0xf2, 0xac, 0xf7
};

#define CRYPTO_82_HSM_STOP_SEC_CONST_8BIT
#include "Crypto_82_Hsm_MemMap.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

void TestApp_Init(void){
    TestApp_MainFunction_count = 0UL;

    #ifdef TESTAPP_ENABLE_SWLIB
    TestApp_InitKey(0);
    #endif /* TESTAPP_ENABLE_SWLIB */
}

void TestApp_MainFunction(void){

    if (TestApp_KeySet_Switch == 1){
        if (TestApp_KeySet_Time == 100){
            TestApp_InitKey(1);
        }else if (TestApp_KeySet_Time == 200){
            TestApp_InitKey(3); /* 鍵更新失敗 */
        }else if (TestApp_KeySet_Time == 300){
            TestApp_InitKey(2);
            TestApp_KeySet_Switch = 0;
        }

        TestApp_KeySet_Time++;
    }

    if (TestApp_KeySet_Switch == 2){
        TestApp_InitKey(3); /* 鍵更新失敗 */
        TestApp_KeySet_Switch = 0;
    }

    TestApp_MainFunction_count++;
}

FUNC(Std_ReturnType, SECOC_CODE) TestApp_InitKey(uint8 testSwitch){
    Std_ReturnType retSec;
#ifdef TESTAPP_ENABLE_SWLIB
    /* 鍵要素設定(UID) */
    // Std_ReturnType retSec;
    retSec = Csm_KeyElementSet (TESTAPP_CSM_KEYID_UID, TP_KEY_SET_UID, (const uint8 *)TestApp_TP_Uid, TP_UID_SIZE);
    if( retSec == E_OK ){
        /* 鍵要素設定(KeyMaterial(SHE仕様) M1+M2+M3 の連結データ) */
        retSec = Csm_KeyElementSet (TESTAPP_CSM_KEYID_MASTER, TP_KEY_SET_M1M2M3, (const uint8 *)TestApp_MasterEcuKey, SQT_MUPKEY_SIZE);
        if( retSec == E_OK ){
            /* 鍵有効化 */
            retSec = Csm_KeySetValid (TESTAPP_CSM_KEYID_MASTER);
            if( retSec == E_OK ){
                /* 鍵要素取得(Proof(SHE) M4+M5 の連結データ) */
                TestApp_ui_size_L = TP_KEY_M4_M5_SIZE;
                retSec = Csm_KeyElementGet (TESTAPP_CSM_KEYID_MASTER, TP_KEY_GET_M4M5, TestApp_uc_buffer, &TestApp_ui_size_L);
            }
        }
    }

    if(retSec == E_OK ){
        /* SECテスト SQT_Scenario_020向け鍵登録 */
        /* 鍵要素設定(KeyMaterial(SHE仕様) M1+M2+M3 の連結データ) */
        retSec = Csm_KeyElementSet (TESTAPP_CSM_KEYID_1, TP_KEY_SET_M1M2M3, (const uint8 *)TestApp_Key_4, SQT_MUPKEY_SIZE);
        if( retSec == E_OK ){
            /* 鍵有効化 */
            retSec = Csm_KeySetValid (TESTAPP_CSM_KEYID_1);
            if( retSec == E_OK ){
                /* 鍵要素取得(Proof(SHE) M4+M5 の連結データ) */
                TestApp_ui_size_L = TP_KEY_M4_M5_SIZE;
                retSec = Csm_KeyElementGet (TESTAPP_CSM_KEYID_1, TP_KEY_GET_M4M5, TestApp_uc_buffer, &TestApp_ui_size_L);
            }
        }
    }
#endif /* TESTAPP_ENABLE_SWLIB */

#ifdef TESTAPP_ENABLE_CYCURHSM
    if (testSwitch == 1){
        /*CsmConf_CsmKey_CsmKey00_MasterEcuKey*/
        retSec = Csm_KeyElementSet(CsmConf_CsmKey_CsmKey00_MasterEcuKey, 1u, &TestApp_MasterEcuKey[0], 64);
        TestApp_KeySet_KeySetElement_Rtn = retSec;
        // if(E_OK != retSec){    		while(1){}    	}
        retSec = Csm_JobKeySetValid(CsmConf_CsmJob_CsmJob43_KeySetValid_MasterEcuKey, CsmConf_CsmKey_CsmKey00_MasterEcuKey); // 非同期ジョブ

        TestApp_KeySet_KeySetValid_Rtn = retSec;
        // if(E_OK != retSec){    		while(1){}    	}

        testSwitch = 0;
    }

    if (testSwitch == 2){
        /*CsmConf_CsmKey_CsmKey_1_Mac*/
        retSec = Csm_KeyElementSet(CsmConf_CsmKey_CsmKey01_MacKey,       1u, &TestApp_Key_4[0], 64);
        TestApp_KeySet_KeySetElement_Rtn = retSec;
        // if(E_OK != retSec){    		while(1){}    	}
        retSec = Csm_JobKeySetValid(CsmConf_CsmJob_CsmJob44_KeySetValid_MacKey, CsmConf_CsmKey_CsmKey01_MacKey); // 非同期ジョブ
        TestApp_KeySet_KeySetValid_Rtn = retSec;
        // if(E_OK != retSec){    		while(1){}    	}

        testSwitch = 0;
    }

#endif /* TESTAPP_ENABLE_CYCURHSM */

    return E_OK;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/*--------------------------------------------------------------------------*/
/* History                                                                  */
/*  Version    :Date       :Description                                     */
/*  1.0.0      :2023/10/12 :Create new                PFSW hontani          */
/*--------------------------------------------------------------------------*/
/**** End of File ***********************************************************/
