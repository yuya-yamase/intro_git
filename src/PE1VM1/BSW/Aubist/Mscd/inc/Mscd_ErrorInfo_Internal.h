/* Mscd_ErrorInfo_Internal.h v2-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/ERRORINFO/INTERNAL/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_ERRORINFO_INTERNAL_H
#define MSCD_ERRORINFO_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( MSCD_ERRORINFO_USE == STD_ON )

/* Total number of Error */
#define MSCD_ERRINFO_SERVICE_ERRORSTATE_NUM      (0x18U)
/* Total number of ErrorFactor */
#define MSCD_ERRINFO_ERRORFACTOR_NUM             (0x03U)

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#if ( MSCD_ERRORINFO_USE == STD_ON )

/* Error Info Result */
typedef struct {
    uint32 u4ErrorResultNvm; /* Error Info NvM Result */
    uint32 u4ErrorResult;   /* Error Info user Release */
} Mscd_ErrorInfo_ErrorResultType;

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if ( MSCD_ERRORINFO_USE == STD_ON )

FUNC(void, MSCD_CODE) Mscd_ErrorInfo_UpdateStateErrorFactor( void );
FUNC(uint32, MSCD_CODE) Mscd_ErrorInfo_TransformErrorResult( uint32 u4ErrorResult );

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_VAR_NO_INIT_32
#include <Mscd_MemMap.h>

#if ( MSCD_ERRORINFO_USE == STD_ON )

extern VAR(Mscd_ErrorInfo_ErrorFactorInfoType, MSCD_VAR_NO_INIT) Mscd_ErrorInfo_stErrorFactorInfo;
extern VAR(Mscd_ErrorInfo_ErrorResultInfoType, MSCD_VAR_NO_INIT) Mscd_ErrorInfo_stSingleErrorResultInfo;
extern VAR(Mscd_ErrorInfo_ErrorResultInfoType, MSCD_VAR_NO_INIT) Mscd_ErrorInfo_stMultiErrorResultInfo;
extern VAR(NvM_BlockRequestType, MSCD_VAR_NO_INIT)               Mscd_ErrorInfo_u1CurrentSingleBlockRequest;
extern VAR(NvM_MultiBlockRequestType, MSCD_VAR_NO_INIT)          Mscd_ErrorInfo_u1CurrentMultiBlockRequest;

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#define MSCD_STOP_SEC_VAR_NO_INIT_32
#include <Mscd_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CONST_32
#include <Mscd_MemMap.h>

#if ( MSCD_ERRORINFO_USE == STD_ON )

extern CONST( AB_83_ConstV Mscd_ErrorInfo_ErrorFactorInfoType, MSCD_CONST) Mscd_ErrorInfo_stErrorFactor_BitPtnTbl[MSCD_ERRINFO_ERRORFACTOR_NUM];
extern CONST( AB_83_ConstV Mscd_ErrorInfo_ErrorResultType, MSCD_CONST) Mscd_ErrorInfo_stErrorResult_BitPtnTbl[MSCD_ERRINFO_SERVICE_ERRORSTATE_NUM];

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#define MSCD_STOP_SEC_CONST_32
#include <Mscd_MemMap.h>

#endif /* MSCD_ERRORINFO_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/31                                              */
/*  1-2-0          :2019/09/06                                              */
/*  2-0-0          :2020/12/22                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
