/* Crypto_83_sw_SWSHE_h_v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SWSHE/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_SWSHE_H
#define CRYPTO_83_SW_SWSHE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Rte_Csm_Type.h>
#include "../../Crypto/inc/Crypto_83_sw_Internal.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_SW_SWSHE_SEED_SIZE                (16U)
#define CRYPTO_83_SW_SWSHE_BLOCK_SIZE               (16U)
#define CRYPTO_83_SW_SWSHE_UID_SIZE                 (15U)
#define CRYPTO_83_SW_SWSHE_CMAC_VER_OK              (0U)
#define CRYPTO_83_SW_SWSHE_CMAC_VER_NG              (1U)

#define CRYPTO_83_SW_SWSHE_KEY_SIZE                 (16U)

#ifndef Crypto_83_sw_ConstR
#define Crypto_83_sw_ConstR const
#endif

/* KeyID */
#define CRYPTO_83_SW_SWSHE_KID_MASTER_ECU_KEY       ((uint8)0x01U)
#define CRYPTO_83_SW_SWSHE_KID_BT_MAC_KEY           ((uint8)0x02U)
#define CRYPTO_83_SW_SWSHE_KID_BT_MAC               ((uint8)0x03U)
#define CRYPTO_83_SW_SWSHE_KID_KEY_1                ((uint8)0x04U)
#define CRYPTO_83_SW_SWSHE_KID_RAM_KEY              ((uint8)0x0EU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint8   u1Id;
    uint8   u1Flag_wp;
    uint8   u1Flag_bp;
    uint8   u1Flag_dp;
    uint8   u1Flag_ku;
    uint8   u1Flag_wc;
    uint8   u1Flag_plain;
    uint8   u1Flag_rsv1;
    uint32  u4Counter;
    uint8   u1Data[CRYPTO_83_SW_SWSHE_KEY_SIZE];
} Crypto_83_sw_Swshe_KeyInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_Init
(
    void
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdEncEcb
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdDecEcb
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdEncCbc
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4PlainLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdDecCbc
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4CipherLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdGenerateMac
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    Crypto_83_sw_ConstR uint32 u4MsgLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMsg,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMac

);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdVerifyMac
(
    Crypto_83_sw_ConstR uint8 u1KeyId,
    Crypto_83_sw_ConstR uint32 u4MsgLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMsg,
    uint8 u1MacLen,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptMac,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptStat
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdLoadKey
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM1,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM2,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM3,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM4,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptM5
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdLoadPlainKey
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdInitRng
(
    void
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdExtendSeed
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptEntropy
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_CmdRnd
(
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptRnd
);

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GetErrorStatus
(
    void
);
#endif

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* CRYPTO_83_SW_SWSHE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
