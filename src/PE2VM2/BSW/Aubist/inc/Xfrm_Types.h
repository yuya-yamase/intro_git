/* Xfrm_Types_h_v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Xfrm_Types/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     XFRM_TYPES_H
#define     XFRM_TYPES_H

#include <Xfrm/Xfrm_Types_ExtDefs.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Serializer Transformer Soft Error */
#define E_NO_DATA                       (0x01U)

/* Serializer Transformer Hard Error */
#define E_SER_GENERIC_ERROR             (0x81U)
#define E_SER_WRONG_PROTOCOL_VERSION    (0x87U)
#define E_SER_WRONG_INTERFACE_VERSION   (0x88U)
#define E_SER_MALFORMED_MESSAGE         (0x89U)
#define E_SER_WRONG_MESSAGE_TYPE        (0x8AU)

/* Safety Transformer Soft Error */
#define E_SAFETY_VALID_REP              (0x01U)
#define E_SAFETY_VALID_SEQ              (0x02U)
#define E_SAFETY_VALID_ERR              (0x03U)
#define E_SAFETY_VALID_NND              (0x05U)
#define E_SAFETY_NODATA_OK              (0x20U)
#define E_SAFETY_NODATA_REP             (0x21U)
#define E_SAFETY_NODATA_SEQ             (0x22U)
#define E_SAFETY_NODATA_ERR             (0x23U)
#define E_SAFETY_NODATA_NND             (0x25U)
#define E_SAFETY_INIT_OK                (0x30U)
#define E_SAFETY_INIT_REP               (0x31U)
#define E_SAFETY_INIT_SEQ               (0x32U)
#define E_SAFETY_INIT_ERR               (0x33U)
#define E_SAFETY_INIT_NND               (0x35U)
#define E_SAFETY_INVALID_OK             (0x40U)
#define E_SAFETY_INVALID_REP            (0x41U)
#define E_SAFETY_INVALID_SEQ            (0x42U)
#define E_SAFETY_INVALID_ERR            (0x43U)
#define E_SAFETY_INVALID_NND            (0x45U)
#define E_SAFETY_SOFT_RUNTIMEERROR      (0x77U)

/* Safety Transformer Hard Error */
#define E_SAFETY_HARD_RUNTIMEERROR      (0xFFU)

/* Security Transformer Soft Error */
#define E_SEC_NOT_AUTH                  (0x01U)
#define E_SEC_NOT_FRESH                 (0x02U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* XFRM_TYPES_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2021/11/29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
