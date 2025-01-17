/* CodeFls_h */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/HEADER                                   */
/******************************************************************************/
#ifndef CODEFLS_H
#define CODEFLS_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* CODEFLS Information */
#define CODEFLS_WRITE_SIZE          ((U4)0x00000200UL)          /* Code Flash Write Size                    */
#define CODEFLS_AUTHID_SIZE         ((U1)32U)                   /* Authentication ID Size                   */
#define CODEFLS_CUSTOMERID_A        ((U1)0U)                    /* CustomerID A                             */
#define CODEFLS_CUSTOMERID_B        ((U1)1U)                    /* CustomerID B                             */
#define CODEFLS_CUSTOMERID_C        ((U1)2U)                    /* CustomerID C                             */
#define CODEFLS_PRODUCT_U2A8        ((U1)0U)                    /* RH850 U2A8                               */
#define CODEFLS_PRODUCT_U2A16       ((U1)1U)                    /* RH850 U2A16                              */
#define CODEFLS_PRODUCT_U2A6        ((U1)2U)                    /* RH850 U2A6                               */

/* Job Status */
#define CODEFLS_UNINIT              ((U1)0x00U)                 /* Non-initialization                       */
#define CODEFLS_IDLE                ((U1)0x01U)                 /* Idle                                     */
#define CODEFLS_BUSY                ((U1)0x02U)                 /* Busy                                     */

/* Request Type */
#define CODEFLS_REQ_WRITE           ((U1)0x00U)                 /* Request: Write                           */
#define CODEFLS_REQ_ERASE           ((U1)0x01U)                 /* Request: Erase                           */
#define CODEFLS_REQ_WRITABLECHECK   ((U1)0x02U)                 /* Request: Check to be Possible Writing    */
#define CODEFLS_REQ_SWITCHVALIDAREA ((U1)0x03U)                 /* Request: Switch Valid Area               */

/* Job Result */
#define CODEFLS_JOB_OK              ((U1)0x00U)                 /* OK                                       */
#define CODEFLS_JOB_FAILED          ((U1)0x01U)                 /* Failed                                   */
#define CODEFLS_JOB_PENDING         ((U1)0x02U)                 /* Pending                                  */

/* Module ID */
#define CODEFLS_MODULE_ID           ((U2)0x0000U)               /* Module ID for CODEFLS Driver             */

/* API ID */
#define CODEFLS_API_ID_INIT         ((U1)0x00U)                 /* API ID for CodeFls_Init                  */
#define CODEFLS_API_ID_ENDCTRL      ((U1)0x01U)                 /* API ID for CodeFls_EndCtrl               */
#define CODEFLS_API_ID_DEINIT       ((U1)0x02U)                 /* API ID for CodeFls_DeInit                */

/* Error Code for CODEFLS Driver */
#define CODEFLS_E_UNINIT            ((U1)0x01U)                 /* Non-initialization Error                 */
#define CODEFLS_E_BUSY              ((U1)0x02U)                 /* Busy Error                               */
#define CODEFLS_E_SELFPRG           ((U1)0x03U)                 /* Self Programming Error [Unused]          */
#define CODEFLS_E_TIMEOUT           ((U1)0x04U)                 /* Time Out Error                           */
#define CODEFLS_E_FCUFIRM           ((U1)0x05U)                 /* FCU Firmware Transmission Error [Unused] */
#define CODEFLS_E_AUTHID            ((U1)0x06U)                 /* Authentication Error                     */
#define CODEFLS_E_CONFIG            ((U1)0x07U)                 /* Config Error                             */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* CODEFLS Block Information Type */
typedef struct
{
    U4      Addr;                                       /* Block Start Address          */
    U4      Size;                                       /* Block Size                   */
} CodeFls_BlockInfoType;

/* [Device Individuality Config] CODEFLS Information Configuration Type */
typedef struct
{
    U4      Addr;                                       /* CODEFLS Start Address          */
    U4      Size;                                       /* CODEFLS Size                   */
} CodeFls_DevCodeFlsInfoConfigType;

/* [Device Individuality Config] CODEFLS Setting Configuration Type */
typedef struct
{
    U1                                          CodeFlsInfoNum;  /* Number of CODEFLS Bank                                                      */
    const CodeFls_DevCodeFlsInfoConfigType*     CodeFlsInfo;     /* Start Address of CODEFLS Information Configuration Table                    */
} CodeFls_DevCodeFlsSettingConfigType;

/* [Device Individuality Config] CODEFLS Authentication ID Information Configuration Type */
typedef struct
{
    U1      AuthIdType;                                 /* Authentication ID Type       */
    U1      AuthId[CODEFLS_AUTHID_SIZE];                /* Authentication ID            */
} CodeFls_DevAuthIdInfoConfigType;

/* [Device Individuality Config] CODEFLS Authentication ID Information Configuration Type */
typedef struct
{
    U1                                          AuthIdInfoNum;  /* Number of Authentication ID                                                  */
    const CodeFls_DevAuthIdInfoConfigType*      AuthIdInfo;     /* Start Address of CODEFLS Authentication ID Infomation Configuration Table    */
} CodeFls_DevAuthIdSettingConfigType;

/* [Device Individuality Config] CODEFLS Product Setting Configuration Type */
typedef struct
{
    U1                                          ProductType;      /* Product Type       */
} CodeFls_DevProductSettingConfigType;

/* [Device Individuality Config] CODEFLS CODEFLS Valid Area Permit Type */
typedef struct
{
    U1                                          Permit;           /* Permit             */
} CodeFls_DevValidAreaPermitType;


/* [Device Individuality Config] CODEFLS Device Individuality Configuration Type */
typedef struct
{
    const CodeFls_DevCodeFlsSettingConfigType*  CodeFlsSetting; /* Start Address of CODEFLS Setting Configuration Table                         */
    const CodeFls_DevAuthIdSettingConfigType*   AuthIdSetting;  /* Start Address of CODEFLS Authentication ID Setting Configuration Table       */
    const CodeFls_DevProductSettingConfigType*  ProductSetting; /* Start Address of CODEFLS Product Setting Configuration Table                 */
    const CodeFls_DevValidAreaPermitType*       PermitSetting;  /* Start Address of CODEFLS Valid Area Permit Table                             */
} CodeFls_DevConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#pragma ghs callmode = far
#pragma ghs section text = ".P_CODEFLS"
void            CodeFls_Init(void);
Std_ReturnType  CodeFls_GetBlockInfo(U4 Addr, CodeFls_BlockInfoType* BlockInfo);
void            CodeFls_DeInit(void);
#pragma ghs section text = default
#pragma ghs section text = ".P_CODEFLS_NORESIDE"
Std_ReturnType  CodeFls_StartCtrl(U1 ReqKind, U4 Addr, U4 Size);
void            CodeFls_EndCtrl(void);
void            CodeFls_Erase(U4 EraseAddr, U4 EraseSize);
void            CodeFls_Write(U4 TargetAddr, const U1* SourceAddr, U4 DataSize);
U1              CodeFls_GetJobStatus(void);
U1              CodeFls_GetJobResult(void);
void            CodeFls_MainFunction(void);
void            CodeFls_WritableCheck(U4 TargetAddr, const U1* SourceAddr, U4 DataSize);
void            CodeFls_SwitchValidArea(void);
#pragma ghs section text = default
#pragma ghs callmode = default


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#pragma ghs section rosdata = ".C_CODEFLS"
extern const CodeFls_DevConfigType CODEFLS_DEVCFG_DATA;
#pragma ghs section rosdata = default


#endif  /* CODEFLS_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/05/31 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

