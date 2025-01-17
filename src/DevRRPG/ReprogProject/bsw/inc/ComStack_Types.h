/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name | ComStack_Types/HEADER                                      */
/*----------------------------------------------------------------          */
/* Revision History                                                         */
/*   Revision    :Date       :Description                                   */
/*   v0_0_1      :2016/09/14 :New created                                   */
/*   v0_0_2      :2022/12/06 :Update                                        */
/*----------------------------------------------------------------          */
/* Notes  Made modifications for Reprog                                     */
/****************************************************************************/

#ifndef COMSTACK_TYPES_H   /* SWS_COMTYPE_00016 */
#define COMSTACK_TYPES_H   /* SWS_COMTYPE_00016 */

#include <Std_Types.h>     /* SWS_COMTYPE_00001 */
#include <ComStack_Cfg.h>  /* SWS_COMTYPE_00001 */

/*-----------------------------------------------------------------------------
    Type definitions
 -----------------------------------------------------------------------------*/

/* PduInfoType - SWS_COMTYPE_00011 */
typedef struct {
    P2VAR(uint8, TYPEDEF, COMSTACK_DATA)    SduDataPtr;     /* uint8-pointer to the SDU of the PDU */
    VAR(PduLengthType, TYPEDEF)             SduLength;      /* length of the SDU in bytes */
} PduInfoType;

/* PNCHandleType - SWS_COMTYPE_00036 */
typedef uint8  PNCHandleType;                           /* SWS_COMTYPE_00036 */

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

/* BusTrcvErrorType - SWS_COMTYPE_00020 */
typedef uint8                           BusTrcvErrorType;
/*  0x00 - 0x1E : General return codes
*   0x1F - 0x3C : Error notification: CAN Transceiver Driver
*   0x3D - 0x5A : Error notification: Lin Interface
*   0x5B - 0x78 : Error notification: FlexRay Transceiver Driver
*        > 0x78 : Currently values in this range are invalid
*/

/*  General Codes - SWS_COMTYPE_00020, SWS_COMTYPE_00021 */
#define BUSTRCV_OK                      ( 0x00U )     /* Successfully */
#define BUSTRCV_E_ERROR                 ( 0x01U )     /* Not successfully */
/* Added return code                                                        */
/*                                                                          */
/* SWS_COMTYPE_00022                                                        */
/* BUSTRCV_E_<Communication System Abbreviation>_<Error Code Name>          */
/* -> Communication System Abbreviation                                     */
/*    LIN : for Local Interconnect Network                                  */
/*    CAN : for Controller Area Network                                     */
/*    FR  : for FlexRay                                                     */
/* -> Error Code Name                                                       */
/*    Self explaining name of error return code.                            */
/* Example                                                                  */
/*  BUSTRCV_E_CAN_SINGLE : The fault tolerant bus is in single wire mode.   */
/*  (*AUTOSAR R4.2.1 does not use <BusTrcvErrorType>.                       */
/*   Therefore, the following definition is not made. )                     */
/*   LIN: BUSTRCV_E_LIN_XXX                                                 */
/*   CAN: BUSTRCV_E_CAN_XXX                                                 */
/*   FR : BUSTRCV_E_FR_XXX                                                  */
/*                                                                          */


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

#endif    /* COMSTACK_TYPES_H *//* SWS_COMTYPE_00016 */
