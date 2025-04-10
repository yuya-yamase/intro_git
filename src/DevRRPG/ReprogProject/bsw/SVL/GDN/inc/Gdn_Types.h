/* Gdn_Types_h_00_0001 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | GUARDIAN Œ^’è‹`                                              */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  ##_####   yyyy/mm/dd   DNXXX    Header File Template                      */
/*  00_0001   2019/12/03   AUBASS   Update                                    */
/*  00_0002   2021/09/14   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_TYPES_H
#define GDN_TYPES_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/****************************** STANDARD  MACROS ******************************/
#define GDN_NULL_PTR    (NULL_PTR)

#define GdnConst        volatile GdnFar const

#define GdnFar
#define GdnNear

#define GDN_E_OK                    ((Gdn_Std_ReturnType)0U)
#define GDN_E_NOT_OK                ((Gdn_Std_ReturnType)1U)
#define GDN_E_PENDING               ((Gdn_Std_ReturnType)2U)
#define GDN_E_REQUEST_NOT_ACCEPTED  ((Gdn_Std_ReturnType)3U)
#define GDN_E_NO_MEMORY             ((Gdn_Std_ReturnType)4U)
#define GDN_E_BUFFER_OVERFLOW       ((Gdn_Std_ReturnType)5U)
#define GDN_E_SUBMICON_GATEWAY      ((Gdn_Std_ReturnType)6U)
#define GDN_E_CANTP_RX_ON           ((Gdn_Std_ReturnType)10U)
#define GDN_E_CANTP_WRONG_PARAMETER ((Gdn_Std_ReturnType)11U)
#define GDN_E_CANTP_WRONG_VALUE     ((Gdn_Std_ReturnType)12U)
#define GDN_E_OK_QUEUED             ((Gdn_Std_ReturnType)20U)  /* For Queueing */
#define GDN_E_OK_THINNED            ((Gdn_Std_ReturnType)21U)  /* For Queueing */
#define GDN_E_REJECTED              ((Gdn_Std_ReturnType)22U)  /* For Queueing */

#define GDN_TRUE        ((gdn_bool)1U)
#define GDN_FALSE       ((gdn_bool)0U)

#define GDN_ON          (1U)
#define GDN_OFF         (0U)

#define GDN_BIT0        (0x1U)
#define GDN_BIT1        (0x2U)
#define GDN_BIT2        (0x4U)
#define GDN_BIT3        (0x8U)
#define GDN_BIT4        (0x10U)
#define GDN_BIT5        (0x20U)
#define GDN_BIT6        (0x40U)
#define GDN_BIT7        (0x80U)
#define GDN_BIT8        (0x100U)
#define GDN_BIT9        (0x200U)
#define GDN_BIT10       (0x400U)
#define GDN_BIT11       (0x800U)
#define GDN_BIT12       (0x1000U)
#define GDN_BIT13       (0x2000U)
#define GDN_BIT14       (0x4000U)
#define GDN_BIT15       (0x8000U)
#define GDN_BIT16       (0x10000U)
#define GDN_BIT17       (0x20000U)
#define GDN_BIT18       (0x40000U)
#define GDN_BIT19       (0x80000U)
#define GDN_BIT20       (0x100000U)
#define GDN_BIT21       (0x200000U)
#define GDN_BIT22       (0x400000U)
#define GDN_BIT23       (0x800000U)
#define GDN_BIT24       (0x1000000U)
#define GDN_BIT25       (0x2000000U)
#define GDN_BIT26       (0x4000000U)
#define GDN_BIT27       (0x8000000U)
#define GDN_BIT28       (0x10000000U)
#define GDN_BIT29       (0x20000000U)
#define GDN_BIT30       (0x40000000U)
#define GDN_BIT31       (0x80000000U)

/************************* COMMUNICATION STACK MACROS *************************/
#define GDN_TP_STMIN                ((Gdn_TPParameterType)0U)
#define GDN_TP_BS                   ((Gdn_TPParameterType)1U)

#define GDN_BUFREQ_OK               ((Gdn_BufReq_ReturnType)0U)
#define GDN_BUFREQ_E_NOT_OK         ((Gdn_BufReq_ReturnType)1U)
#define GDN_BUFREQ_E_BUSY           ((Gdn_BufReq_ReturnType)2U)
#define GDN_BUFREQ_E_OVFL           ((Gdn_BufReq_ReturnType)3U)

#define GDN_NTFRSLT_OK              ((Gdn_NotifResultType)0U)
#define GDN_NTFRSLT_E_NOT_OK        ((Gdn_NotifResultType)1U)
#define GDN_NTFRSLT_E_TIMEOUT_A     ((Gdn_NotifResultType)2U)
#define GDN_NTFRSLT_E_TIMEOUT_BS    ((Gdn_NotifResultType)3U)
#define GDN_NTFRSLT_E_TIMEOUT_CR    ((Gdn_NotifResultType)4U)
#define GDN_NTFRSLT_E_WRONG_SN      ((Gdn_NotifResultType)5U)
#define GDN_NTFRSLT_E_INVALID_FS    ((Gdn_NotifResultType)6U)
#define GDN_NTFRSLT_E_UNEXP_PDU     ((Gdn_NotifResultType)7U)
#define GDN_NTFRSLT_E_WFT_OVRN      ((Gdn_NotifResultType)8U)
#define GDN_NTFRSLT_E_NO_BUFFER     ((Gdn_NotifResultType)9U)

#define GDN_TP_DATACONF             ((Gdn_TpDataStateType)0U)
#define GDN_TP_DATARETRY            ((Gdn_TpDataStateType)1U)
#define GDN_TP_DATAPENDING          ((Gdn_TpDataStateType)2U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/

/******************************* STANDARD TYPES *******************************/
typedef uint8               gdn_uint8;
typedef uint16              gdn_uint16;
typedef uint32              gdn_uint32;
typedef sint8               gdn_sint8;
typedef sint16              gdn_sint16;
typedef sint32              gdn_sint32;

typedef float32             gdn_float32;
typedef float64             gdn_float64;

typedef boolean             gdn_bool;

typedef Std_ReturnType      Gdn_Std_ReturnType;

/************************* COMMUNICATION STACK  TYPES *************************/
typedef PduIdType           Gdn_PduIdType;
typedef PduLengthType       Gdn_PduLengthType;
typedef PduInfoType         Gdn_PduInfoType;

typedef TPParameterType     Gdn_TPParameterType;
typedef BufReq_ReturnType   Gdn_BufReq_ReturnType;
typedef TpDataStateType     Gdn_TpDataStateType;
typedef RetryInfoType       Gdn_RetryInfoType;

typedef gdn_uint8           Gdn_NotifResultType;
/******************************* WRAPPER  TYPES *******************************/
typedef gdn_uint8           Gdn_TimerIdType;
typedef gdn_uint16          Gdn_TimeoutValueType;

/*----------------------------------------------------------------------------*/
/* Variables                                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* External Function Prototypes                                               */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_Component[_Module]_ExternalFunction                    */
/* Description   |                                                            */
/* Re-entrancy   | (Non) Reentrant                                            */
/* Parameter(s)  | (in/out/io) Address : Receiver of the love letter          */
/* Return Value  | StatusType                                                 */
/*               |  GDN_E_OK     : Happy Ending                               */
/*               |  GDN_E_NOT_OK : Tragic Ending                              */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/

#endif /* GDN_TYPES_H */
/**** End of File *************************************************************/
