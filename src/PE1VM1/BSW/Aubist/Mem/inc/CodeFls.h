/* CodeFls_h                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/HEADER                                 */
/****************************************************************************/
#ifndef CODEFLS_H
#define CODEFLS_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CODEFLS Information */
#define CODEFLS_AUTHID_SIZE                 ((uint8)32U)            /* Authentication ID Size                   */
#define CODEFLS_CUSTOMERID_A                ((uint8)0U)             /* CustomerID A                             */
#define CODEFLS_CUSTOMERID_B                ((uint8)1U)             /* CustomerID B                             */
#define CODEFLS_CUSTOMERID_C                ((uint8)2U)             /* CustomerID C                             */
#define CODEFLS_PRODUCT_U2A8                ((uint8)0U)             /* RH850 U2A8                               */
#define CODEFLS_PRODUCT_U2A16               ((uint8)1U)             /* RH850 U2A16                              */
#define CODEFLS_PRODUCT_U2A6                ((uint8)2U)             /* RH850 U2A6                               */

/* CPU clock frequency */
#define CODEFLS_CPU_CLOCK_240               ((uint16)240U)          /* CPU Clock Time 240MHz                    */
#define CODEFLS_CPU_CLOCK_320               ((uint16)320U)          /* CPU Clock Time 320MHz                    */
#define CODEFLS_CPU_CLOCK_400               ((uint16)400U)          /* CPU Clock Time 400MHz                    */

#define CODEFLS_WRITE_SIZE                  ((uint32)0x00000200UL)  /* Code Flash Write Size                    */

/* Job Status */
#define CODEFLS_UNINIT                      ((uint8)0x00U)          /* Non-initialization                       */
#define CODEFLS_IDLE                        ((uint8)0x01U)          /* Idle                                     */
#define CODEFLS_BUSY                        ((uint8)0x02U)          /* Busy                                     */

/* Request Type */
#define CODEFLS_REQ_WRITE                   ((uint8)0x00U)          /* Request: Write                           */
#define CODEFLS_REQ_ERASE                   ((uint8)0x01U)          /* Request: Erase                           */
#define CODEFLS_REQ_WRITABLECHECK           ((uint8)0x02U)          /* Request: Check to be Possible Writing    */
#define CODEFLS_REQ_SWITCHVALIDAREA         ((uint8)0x03U)          /* Request: Switch Valid Area               */
#define CODEFLS_REQ_BLANKCHECK              ((uint8)0x04U)          /* Request: Blank Check                     */

/* Job Result */
#define CODEFLS_JOB_OK                      ((uint8)0x00U)          /* OK                                       */
#define CODEFLS_JOB_FAILED                  ((uint8)0x01U)          /* Failed                                   */
#define CODEFLS_JOB_PENDING                 ((uint8)0x02U)          /* Pending                                  */
#define CODEFLS_INCONSISTENT                ((uint8)0x03U)          /* Blank check error                        */

/* For blank check-alignment determination */
#define CODEFLS_U4_BLANKCHECK_ALIGN_SIZE    ((uint32)512U)

/* ECC Error Determination Value */
#define CODEFLS_U1_ECC_CHECK_OK             ((uint8)0U)             /* ECC check result - no error              */
#define CODEFLS_U1_ECC_CHECK_ERROR_1BIT     ((uint8)1U)             /* ECC check result - 1bit error            */
#define CODEFLS_U1_ECC_CHECK_ERROR_2BIT     ((uint8)2U)             /* ECC check result - 2bit error            */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* CODEFLS Block Information Type */
typedef struct
{
    uint32 Addr;                                                    /* Block Start Address                      */
    uint32 Size;                                                    /* Block Size                               */
} CodeFls_BlockInfoType;

/* [Device Individuality Config] CODEFLS Information Configuration Type */
typedef struct
{
    uint32 Addr;                                            /* CODEFLS Start Address        */
    uint32 Size;                                            /* CODEFLS Size                 */
} CodeFls_DevCodeFlsInfoConfigType;

/* [Device Individuality Config] CODEFLS Setting Configuration Type */
typedef struct
{
    uint8 CodeFlsInfoNum;                                   /* Number of CODEFLS Bank       */
    /* Start Address of CODEFLS Information Configuration Table                             */
    P2CONST(AB_83_ConstV CodeFls_DevCodeFlsInfoConfigType, TYPEDEF, MEM_CONFIG_DATA) CodeFlsInfo;
} CodeFls_DevCodeFlsSettingConfigType;

/* [Device Individuality Config] CODEFLS Authentication ID Information Configuration Type */
typedef struct
{
    uint8 AuthIdType;                                       /* Authentication ID Type       */
    uint8 AuthId[CODEFLS_AUTHID_SIZE];                      /* Authentication ID            */
} CodeFls_DevAuthIdInfoConfigType;

/* [Device Individuality Config] CODEFLS Authentication ID Information Configuration Type */
typedef struct
{
    uint8 AuthIdInfoNum;                                    /* Number of Authentication ID  */
    /* Start Address of CODEFLS Authentication ID Infomation Configuration Table            */
    P2CONST(AB_83_ConstV CodeFls_DevAuthIdInfoConfigType, TYPEDEF, MEM_CONFIG_DATA) AuthIdInfo;
} CodeFls_DevAuthIdSettingConfigType;

/* [Device Individuality Config] CODEFLS Product Setting Configuration Type */
typedef struct
{
    uint8 ProductType;                                      /* Product Type                 */
    uint16 Clock;                                           /* CPU clock frequency          */
} CodeFls_DevProductSettingConfigType;

/* [Device Individuality Config] CODEFLS CODEFLS Valid Area Permit Type */
typedef struct
{
    uint8 Permit;                                           /* Permit                       */
} CodeFls_DevValidAreaPermitType;

/* [Device Individuality Config] CODEFLS Device Individuality Configuration Type */
typedef struct
{
    /* Start Address of CODEFLS Setting Configuration Table                                 */
    P2CONST(AB_83_ConstV CodeFls_DevCodeFlsSettingConfigType, TYPEDEF, MEM_CONFIG_DATA) CodeFlsSetting;
    /* Start Address of CODEFLS Authentication ID Setting Configuration Table               */
    P2CONST(AB_83_ConstV CodeFls_DevAuthIdSettingConfigType, TYPEDEF, MEM_CONFIG_DATA) AuthIdSetting;
    /* Start Address of CODEFLS Product Setting Configuration Table                         */
    P2CONST(AB_83_ConstV CodeFls_DevProductSettingConfigType, TYPEDEF, MEM_CONFIG_DATA) ProductSetting;
    /* Start Address of CODEFLS Valid Area Permit Table                                     */
    P2CONST(AB_83_ConstV CodeFls_DevValidAreaPermitType, TYPEDEF, MEM_CONFIG_DATA) PermitSetting;
} CodeFls_DevConfigType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
FUNC(void, MEM_CODE) CodeFls_Init(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(CodeFls_BlockInfoType, AUTOMATIC, MEM_APPL_DATA) BlockInfo
);
FUNC(void, MEM_CODE) CodeFls_DeInit(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_StartCtrl
(
    VAR(uint8, AUTOMATIC) ReqKind,
    VAR(uint32, AUTOMATIC) Addr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(void, MEM_CODE) CodeFls_EndCtrl(void);
FUNC(void, MEM_CODE) CodeFls_Erase
(
    VAR(uint32, AUTOMATIC) EraseAddr,
    VAR(uint32, AUTOMATIC) EraseSize
);
FUNC(void, MEM_CODE) CodeFls_Write
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) SourceAddr,
    VAR(uint32, AUTOMATIC) DataSize
);
FUNC(uint8, MEM_CODE) CodeFls_GetJobStatus(void);
FUNC(uint8, MEM_CODE) CodeFls_GetJobResult(void);
FUNC(void, MEM_CODE) CodeFls_MainFunction(void);
#if 0   /* Nbr1503 */
FUNC(void, MEM_CODE) CodeFls_WritableCheck
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) SourceAddr,
    VAR(uint32, AUTOMATIC) DataSize
);
#endif
FUNC(void, MEM_CODE) CodeFls_SwitchValidArea(void);
FUNC(void, MEM_CODE) CodeFls_BlankCheck
(
    VAR(uint32, AUTOMATIC) targetAddress,
    VAR(uint32, AUTOMATIC) length
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_CheckSwitchValidArea(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Suspend(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Resume(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_CheckInvalidArea
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
);
FUNC(uint8, MEM_CODE) CodeFls_GetEccErrorAddressRom
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);
FUNC(void, MEM_CODE) CodeFls_ClearJobStatus(void);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>

extern CONST(AB_83_ConstV CodeFls_DevConfigType, MEM_CONFIG_DATA) CODEFLS_DEVCFG_DATA;

#define MEM_STOP_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>


#endif  /* CODEFLS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

