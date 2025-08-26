/* Rte_Dcm_Typedef_h(v5-3-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | RTE/DCM_Typedef/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef RTE_DCM_TYPEDEF_H
#define RTE_DCM_TYPEDEF_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8        Dcm_ConfirmationStatusType;
typedef uint8        Dcm_NegativeResponseCodeType;
typedef uint8        Dcm_OpStatusType;
typedef uint8        Dcm_SecLevelType;
typedef uint8        Dcm_SesCtrlType;
typedef uint8        Dcm_ProtocolType;
typedef uint8        Dcm_DidSupportedType;
typedef uint8        Dcm_DTCKindType;
typedef uint8        Dcm_DidRequestType;
typedef uint8        Dcm_InputOutputControlParameterType;
typedef uint8        Dcm_IOOperationResponseType;
typedef uint8        Dcm_ActiveStateType;
typedef uint8        Dcm_RequestDataArrayType[4095];

typedef uint8        Dcm_AuthenticationRoleType[1];

/* Dcm_SetComparisonOfValues Parameter */
typedef struct
{
    uint16                  u2DID;              /* target DID */
    uint8                   u1ComparisonLogic;  /* the logics of the comparison method */
    uint32                  u4ComparisonValue;  /* the reference comparison value */
    uint8                   u1Hysteresis;       /* histeresys value in percentage from 0 to 100 */
    uint16                  u2Localization;     /* localization of value within the data identifier */
} Dcm_ComparisonValueType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* RTE_DCM_TYPEDEF_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File************************************************************/
