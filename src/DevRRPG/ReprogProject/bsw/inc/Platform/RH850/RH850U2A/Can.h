/* Can_h */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Can/HEADER                                       */
/******************************************************************************/
#ifndef CAN_H
#define CAN_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* CAN ID Format Type */
#define CAN_ID_STANDARD                 ((U1)0U)                        /* Standard CAN ID                   */
#define CAN_ID_EXTEND                   ((U1)1U)                        /* Extended CAN ID                   */
#define CAN_FD_ID_STANDARD              ((U1)2U)                        /* CAN FD frame with Standard CAN ID */
#define CAN_FD_ID_EXTEND                ((U1)3U)                        /* CAN FD frame with Extended CAN ID */

/* Mailbox Type */
#define CAN_NOUSE                       ((U1)0U)                        /* Unused Mailbox                   */
#define CAN_TX                          ((U1)1U)                        /* Mailbox for Transmission         */
#define CAN_RX                          ((U1)2U)                        /* Mailbox for Reception            */

/* Configuration Number Type */
#define CAN_HARDWAREOBJ_NUM             (16U)                           /* Maximum Number of Virtual Mailbox for RPG */

/* Product Type */
#define CAN_PRODUCT_PIN144              ((U4)(144UL << 16UL))
#define CAN_PRODUCT_PIN156              ((U4)(156UL << 16UL))
#define CAN_PRODUCT_PIN176              ((U4)(176UL << 16UL))
#define CAN_PRODUCT_PIN292              ((U4)(292UL << 16UL))
#define CAN_PRODUCT_PIN373              ((U4)(373UL << 16UL))
#define CAN_PRODUCT_PIN516              ((U4)(516UL << 16UL))
#define CAN_PRODUCT_U2A8                ((U4)(  8UL << 8UL))
#define CAN_PRODUCT_U2A16               ((U4)( 16UL << 8UL))
#define CAN_PRODUCT_U2A6                ((U4)(  6UL << 8UL))
#define CAN_PRODUCT_CH9                 ((U4)   9UL)
#define CAN_PRODUCT_CH12                ((U4)  12UL)
#define CAN_PRODUCT_CH16                ((U4)  16UL)
#define CAN_PRODUCT_MASK_PIN            ((U4)0xFFFF0000UL)
#define CAN_PRODUCT_MASK_MICON          ((U4)0x0000FF00UL)
#define CAN_PRODUCT_MASK_CH             ((U4)0x000000FFUL)

#define CAN_PRODUCT_U2A8_292PIN         (CAN_PRODUCT_PIN292 | CAN_PRODUCT_U2A8  | CAN_PRODUCT_CH16)     /* U2A8   292pin(16ch)  */
#define CAN_PRODUCT_U2A8_373PIN         (CAN_PRODUCT_PIN373 | CAN_PRODUCT_U2A8  | CAN_PRODUCT_CH16)     /* U2A8   373pin(16ch)  */
#define CAN_PRODUCT_U2A16_292PIN        (CAN_PRODUCT_PIN292 | CAN_PRODUCT_U2A16 | CAN_PRODUCT_CH16)     /* U2A16  292pin(16ch)  */
#define CAN_PRODUCT_U2A16_373PIN        (CAN_PRODUCT_PIN373 | CAN_PRODUCT_U2A16 | CAN_PRODUCT_CH16)     /* U2A16  272pin(16ch)  */
#define CAN_PRODUCT_U2A16_516PIN        (CAN_PRODUCT_PIN516 | CAN_PRODUCT_U2A16 | CAN_PRODUCT_CH16)     /* U2A16  516pin(16ch)  */
#define CAN_PRODUCT_U2A6_144PIN         (CAN_PRODUCT_PIN144 | CAN_PRODUCT_U2A6  | CAN_PRODUCT_CH9 )     /* U2A6   144pin( 9ch)  */
#define CAN_PRODUCT_U2A6_156PIN         (CAN_PRODUCT_PIN156 | CAN_PRODUCT_U2A6  | CAN_PRODUCT_CH12)     /* U2A6   156pin(12ch)  */
#define CAN_PRODUCT_U2A6_176PIN         (CAN_PRODUCT_PIN176 | CAN_PRODUCT_U2A6  | CAN_PRODUCT_CH12)     /* U2A6   176pin(12ch)  */
#define CAN_PRODUCT_U2A6_292PIN         (CAN_PRODUCT_PIN292 | CAN_PRODUCT_U2A6  | CAN_PRODUCT_CH12)     /* U2A6   292pin(12ch)  */

#define CAN_GET_PRODUCT_PIN             (CAN_DEVCFG_DATA.ProductSetting->ProductType & CAN_PRODUCT_MASK_PIN)
#define CAN_GET_PRODUCT_MICON           (CAN_DEVCFG_DATA.ProductSetting->ProductType & CAN_PRODUCT_MASK_MICON)
#define CAN_GET_PRODUCT_MAXCH           ((U1)(CAN_DEVCFG_DATA.ProductSetting->ProductType & CAN_PRODUCT_MASK_CH))

/* Module ID */
#define CAN_MODULE_ID                   ((U2)0x0001U)                   /* Module ID for CAN Driver         */

/* API ID */
#define CAN_API_ID_INIT                 ((U1)0x00U)                     /* API ID for Can_Init              */
#define CAN_API_ID_CANCEL               ((U1)0x01U)                     /* API ID for Can_Cancel            */
#define CAN_API_ID_DEINIT               ((U1)0x02U)                     /* API ID for Can_DeInit            */
#define CAN_API_ID_INTERRUPT            ((U1)0x03U)                     /* API ID for Can_Interrupt         */
#define CAN_API_ID_MAINFUNCTION_MODE    ((U1)0x04U)                     /* API ID for Can_MainFunction_Mode */

/* Error Code for CAN Driver */
#define CAN_E_CONFIG                    ((U1)0x01U)                     /* Config Error                     */
#define CAN_E_PARAM                     ((U1)0x02U)                     /* Parameter Error                  */
#define CAN_E_UNINIT                    ((U1)0x03U)                     /* Non-initialization Error         */
#define CAN_E_STOP                      ((U1)0x04U)                     /* Stop Error                       */
#define CAN_E_INIT_FAILURE              ((U1)0x05U)                     /* Can_Init Error                   */
#define CAN_E_DEINIT_FAILURE            ((U1)0x06U)                     /* Can_DeInit Error                 */

/* Interrupt Factor Type */
#define CAN_INT_TX                      ((U4)0x00000000UL)              /* Transmit Interrupt               */
#define CAN_INT_RX                      ((U4)0x00000001UL)              /* Receive Interrupt                */

/* CAN State Transition Type */
#define CAN_T_STOP                      ((U1)0U)                        /* CAN controller transition value to request state STOPPED */
#define CAN_T_START                     ((U1)1U)                        /* CAN controller transition value to request state STARTED */

/* CAN Return Type */
#define CAN_OK                          ((U1)0U)                        /* Success                          */
#define CAN_NOT_OK                      ((U1)1U)                        /* Failure                          */
#define CAN_BUSY                        ((U1)2U)                        /* Busy                             */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* CAN Hardware Object Handle Type */
typedef     U2                  Can_HwHandleType;

/* CAN ID Type */
typedef     U4                  Can_IdType;

/* CAN State Transition Type */
typedef     U1                  Can_StateTransitionType;

/* CAN Return Type */
typedef     U1                  Can_ReturnType;

/* CAN Hardware Object Type */
typedef struct
{
    Can_IdType          CanId;                          /* CAN ID Type                      */
    Can_HwHandleType    Hoh;                            /* CAN Hardware Object Handle Type  */
    U1                  ControllerId;                   /* CAN Controller ID                */
} Can_HwType;

/* CAN PDU Type */
typedef struct
{
    PduIdType   swPduHandle;                            /* PDU ID                           */
    U1          length;                                 /* Data Length                      */
    Can_IdType  id;                                     /* CAN ID Type                      */
    U1*         sdu;                                    /* Start Address of Data            */
} Can_PduType;

/* CAN Controller Setting Configuration Type */
typedef struct
{
    U1          Enable;                                 /* Use of Controller                    */
    U1          DefaultBaudrateConfigId;                /* Default Baudrate Configuration ID    */
    U2          CanTimeoutDuration;                     /* CAN Timeout Duration[1 to 65535[ms]] */
} Can_ControllerSettingConfigType;

/* CAN Controller Configuration Type */
typedef struct
{
    U1                                      CanControllerNum;       /* Number of CAN Controller Channel Setting                     */
    const Can_ControllerSettingConfigType*  CanControllerSetting;   /* Start Address of CAN Controller Setting Configuration Table  */
} Can_ControllerConfigType;

/* CAN Controller Baudrate Setting Configuration Type */
typedef struct
{
    U2          Baudrate;                               /* Controller Baudrate              */
    U1          PropSeg;                                /* Propagation Time Segment         */
    U1          Seg1;                                   /* Phase Buffer Segment1            */
    U1          Seg2;                                   /* Phase Buffer Segment2            */
    U1          SyncJumpWidth;                          /* Synchronization Jump Width       */
    U1          SampleTime;                             /* Sampling Times                   */
} Can_ControllerBaudRateSettingConfigType;

/* CAN Controller Baudrate Configuration Type */
typedef struct
{
    U1                                              BaudRateNum;        /* Number of CAN Controller Baudrate Setting                            */
    const Can_ControllerBaudRateSettingConfigType*  BaudRateSetting;    /* Start Address of CAN Controller Baudrate Setting Configuration Table */
} Can_ControllerBaudRateConfigType;

/* CAN Hardware Object Configuration Type */
typedef struct
{
    U1          Use;                                    /* Use              */
    U1          Channel;                                /* Channel          */
    U2          Mb;                                     /* Mailbox          */
    U4          CanId;                                  /* CAN ID           */
    U1          CanIdType;                              /* CAN ID Format    */
} Can_HardwareObjConfigType;

/* CAN Configuration Type */
typedef struct
{
    const Can_ControllerConfigType*         Control;        /* Start Address of CAN Controller Configuration Table          */
    const Can_ControllerBaudRateConfigType* BaudRate;       /* Start Address of CAN Controller Baudrate Configuration Table */
    const Can_HardwareObjConfigType*        HardwareObj;    /* Start Address of CAN Hardware Object Configuration Table     */
} Can_ConfigType;

/* [Device Individuality Config] CAN Product Setting Configuration Type */
typedef struct
{
    U4      ProductType;                                /* Product Type       */
} Can_DevProductSettingConfigType;

/* [Device Individuality Config] CAN Device Individuality Configuration Type */
typedef struct
{
    const Can_ControllerBaudRateSettingConfigType*  BaudRateSetting2;   /* Start Address of CAN Controller Baudrate Setting Configuration Table [DataBitRate]   */
    const Can_DevProductSettingConfigType*          ProductSetting;     /* Start Address of CAN Product Setting Configuration Table                             */
} Can_DevConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#pragma ghs callmode = far
#pragma ghs section text = ".P_CAN"
void            Can_Init(const Can_ConfigType* Config);
Can_ReturnType  Can_SetControllerMode(U1 Controller, Can_StateTransitionType Transition);
Can_ReturnType  Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo);
void            Can_Cancel(Can_HwHandleType Hth);
Std_ReturnType  Can_CheckBaudrate(U1 Controller, U2 BaudRateConfigId);
Std_ReturnType  Can_SetBaudrate(U1 Controller, U2 BaudRateConfigId);
void            Can_DeInit(void);
void            Can_Interrupt(U1 Controller, U4 InterruptSource);
void            Can_MainFunction_Mode(void);
#pragma ghs section text = default
#pragma ghs callmode = default


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#pragma ghs section rosdata = ".C_CAN"
extern const Can_ConfigType CAN_CFG_DATA;
extern const Can_DevConfigType CAN_DEVCFG_DATA;
#pragma ghs section rosdata = default


#endif  /* CAN_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/05/31 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

