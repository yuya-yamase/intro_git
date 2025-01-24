/* ComStack_Types_h_v2-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ComStack_Types/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Std_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR specification version information [SWS_BSW_00059] */
#define COMTYPE_VENDOR_ID                    (0x0053U)
#define COMTYPE_MODULE_ID                    (0x00C4U)
#define COMTYPE_AR_RELEASE_MAJOR_VERSION     (4U)
#define COMTYPE_AR_RELEASE_MINOR_VERSION     (5U)
#define COMTYPE_AR_RELEASE_REVISION_VERSION  (0U)

/* File version information [SWS_BSW_00059] */
#define COMTYPE_SW_MAJOR_VERSION  (2U)
#define COMTYPE_SW_MINOR_VERSION  (0U)
#define COMTYPE_SW_PATCH_VERSION  (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* SWS_COMTYPE_00005 */
typedef uint16                          PduIdType;
/* SWS_COMTYPE_00008 */
typedef uint32                          PduLengthType;

/* PduInfoType - SWS_COMTYPE_00011 */
typedef struct 
{
    P2VAR(uint8, TYPEDEF, COMSTACK_DATA)  SduDataPtr;     /* uint8-pointer to the SDU of the PDU */
    P2VAR(uint8, TYPEDEF, COMSTACK_DATA)  MetaDataPtr;    /* uint8-pointer to the meta data of the PDU */
    VAR(PduLengthType, TYPEDEF)           SduLength;      /* length of the SDU in bytes */
} PduInfoType;

/* PNCHandleType - SWS_COMTYPE_00036 */
typedef uint8                           PNCHandleType;

/* TPParameterType - SWS_COMTYPE_00031 */
typedef uint8                           TPParameterType;
#define TP_STMIN ( 0x00U ) /* Separation Time */
#define TP_BS    ( 0x01U ) /* Block Size */
#define TP_BC    ( 0x02U ) /* The Band width control parameter used in FlexRay TP */

/* BufReq_ReturnType - SWS_COMTYPE_00012 */
typedef uint8                           BufReq_ReturnType;
#define BUFREQ_OK                       ( 0x00U )  /*  Successful */
#define BUFREQ_E_NOT_OK                 ( 0x01U )  /*  Not successful*/
#define BUFREQ_E_BUSY                   ( 0x02U )  /*  Busy */
#define BUFREQ_E_OVFL                   ( 0x03U )  /*  Overflow */

/* TpDataStateType - SWS_COMTYPE_00027 */
typedef uint8                           TpDataStateType;
#define TP_DATACONF                     ( 0x00U )
#define TP_DATARETRY                    ( 0x01U )
#define TP_CONFPENDING                  ( 0x02U )

/* RetryInfoType - SWS_COMTYPE_00037 */
typedef struct {
    VAR(TpDataStateType, TYPEDEF)       TpDataState;    /* The enum type to be used to store the state of Tp buffer */
    VAR(PduLengthType, TYPEDEF)         TxTpDataCnt;    /* length of the SDU in bytes */
} RetryInfoType;

/* NetworkHandleType - SWS_COMTYPE_00038 */
typedef uint8                           NetworkHandleType;  /* Variables of the type NetworkHandleType */

/* IcomConfigIdType - SWS_COMTYPE_00039 */
typedef uint8                           IcomConfigIdType;

/* IcomSwitch_ErrorType - SWS_COMTYPE_00040 */
typedef uint8                           IcomSwitch_ErrorType;
#define ICOM_SWITCH_E_OK                ( 0x00U )
#define ICOM_SWITCH_E_FAILED            ( 0x01U )

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif    /* COMSTACK_TYPES_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2017/10/09                                              */
/*  v1-0-1         :2018/11/12                                              */
/*  v2-0-0         :2020/12/31                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
