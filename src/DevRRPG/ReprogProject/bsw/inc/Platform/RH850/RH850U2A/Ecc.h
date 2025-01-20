/* Ecc_h */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Ecc/HEADER                                       */
/******************************************************************************/
#ifndef ECC_H
#define ECC_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Target Area Type */
#define ECC_AREA_RPG                ((U4)0x00000001UL)          /* RPG Software Area                */
#define ECC_AREA_USR                ((U4)0x00000002UL)          /* USR Software Area                */

/* Module ID */
#define ECC_MODULE_ID               ((U2)0x0008U)               /* Module ID for ECC Driver         */

/* API ID */
#define ECC_API_ID_INIT             ((U1)0x00U)                 /* API ID for Ecc_Init              */
#define ECC_API_ID_CLEARERRORINFO   ((U1)0x01U)                 /* API ID for Ecc_ClearErrorInfo    */
#define ECC_API_ID_CHECKERROR       ((U1)0x02U)                 /* API ID for Ecc_CheckError        */
#define ECC_API_ID_DEINIT           ((U1)0x03U)                 /* API ID for Ecc_DeInit            */

/* Error Code for ECC Driver */
#define ECC_E_CONFIG                ((U1)0x01U)                 /* Configuration Error              */
#define ECC_E_PARAM                 ((U1)0x02U)                 /* Parameter Error                  */
#define ECC_E_UNINIT                ((U1)0x03U)                 /* Non-initialization Error         */

/* Ecc Information */
#define ECC_PRODUCT_U2A8            ((U1)0U)                    /* RH850 U2A8                       */
#define ECC_PRODUCT_U2A16           ((U1)1U)                    /* RH850 U2A16                      */
#define ECC_PRODUCT_U2A6            ((U1)2U)                    /* RH850 U2A6                       */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* ECC Setting Configuration Type */
typedef struct
{
    U4      Addr;                                       /* ECC Error Detection Start Address                    */
    U4      Size;                                       /* ECC Error Detection Size                             */
    U1      EccEnable;                                  /* ECC Enable     STD_OFF: Disable     STD_ON: Enable   */
    U1      Ecc1bitCorrect;                             /* 1-Bit Correct  STD_OFF: Not Detect  STD_ON: Detect   */
    U1      Ecc1bitDetect;                              /* 1-Bit Detect   STD_OFF: Not Detect  STD_ON: Detect   */
    U1      Ecc2bitDetect;                              /* 2-Bit Detect   STD_OFF: Not Detect  STD_ON: Detect   */
} Ecc_SettingConfigType;

/* ECC Target Area Configuration Type */
typedef struct
{
    U1                              SettingNum;         /* Number of Setting                                    */
    const Ecc_SettingConfigType*    Setting;            /* Start Address of ECC Setting Configuration Table     */
} Ecc_TargetAreaConfigType;

/* ECC Target Memory Configuration Type */
typedef struct
{
    const Ecc_TargetAreaConfigType* RpgArea;            /* Start Address of ECC Target Area Configuration Table [RPG Software Area] */
    const Ecc_TargetAreaConfigType* UsrArea;            /* Start Address of ECC Target Area Configuration Table [USR Software Area] */
} Ecc_TargetMemoryConfigType;

/* ECC Configuration Type */
typedef struct
{
    const Ecc_TargetMemoryConfigType*   EccRom;         /* Start Address of ECC Target Memory Configuration Table [ROM] */
    const Ecc_TargetAreaConfigType*     EccRam;         /* Start Address of ECC Target Area Configuration Table [RAM]   */
} Ecc_ConfigType;

/* [Device Individuality Config] ECC Product Setting Configuration Type */
typedef struct
{
    U1                                      ProductType;    /* Product Type       */
} Ecc_DevProductSettingConfigType;

/* [Device Individuality Config] ECC Device Individuality Configuration Type */
typedef struct
{
    const Ecc_DevProductSettingConfigType*  ProductSetting; /* Start Address of ECC Product Setting Configuration Table */
} Ecc_DevConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#pragma ghs callmode = far
#pragma ghs section text = ".P_ECC"
void    Ecc_Init(void);
void    Ecc_ClearErrorInfo(U4 TargetArea);
U4      Ecc_CheckError(void);
void    Ecc_DeInit(void);
#pragma ghs section text = default
#pragma ghs callmode = default


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#pragma ghs section rosdata = ".C_ECC"
extern const Ecc_ConfigType ECC_CFG_DATA;
extern const Ecc_DevConfigType ECC_DEVCFG_DATA;
#pragma ghs section rosdata = default


#endif  /* ECC_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/05/31 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

