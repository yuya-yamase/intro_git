/* NvM_Nvb.h v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/NVB/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_NVB_H
#define     NVM_NVB_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_NVB_OPERATION_READ                  (NVM_RND_NUM_UINT32_31)
#define NVM_NVB_OPERATION_WRITE                 (NVM_RND_NUM_UINT32_32)

#define NVM_NVB_OPERATION_NUM                   (0x02U)

/* Nvb status */
#define NVM_NVB_IDLE                            (0x01U)
#define NVM_NVB_BUSY                            (0x02U)

/* Set mode labels */
#define NVM_NVB_MODE_SLOW                       (0x00U)
#define NVM_NVB_MODE_FAST                       (0x01U)

/* Under layer's MainFunction call mode */
#define NVM_NVB_CALLMODE_PERIODIC               (0x00U)
#define NVM_NVB_CALLMODE_NONPERIODIC            (0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8   NvM_Nvb_StatusType;
typedef uint32  NvM_Nvb_OperationIdType;
typedef uint8  NvM_Nvb_ModeType;

typedef struct {
    NvM_Nvb_OperationIdType OperationId;
    NvM_BlockIdType BlockId;
    P2VAR( uint8, TYPEDEF, TYPEDEF ) DstPtr;
    P2CONST( uint8, TYPEDEF, TYPEDEF ) SrcPtr;
} NvM_Nvb_OperationInformationType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE ) NvM_Nvb_Init( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_RequestOperation(
    P2CONST( NvM_Nvb_OperationInformationType, AUTOMATIC, TYPEDEF ) OperationInfo
);

FUNC( void, NVM_CODE )
NvM_Nvb_MainFunction(
    uint8 CallMode
);

FUNC( void, NVM_CODE ) NvM_Nvb_DestructiveCancelOperation( void );

FUNC( NvM_RequestResultType, NVM_CODE ) NvM_Nvb_GetOperationResult( void );

FUNC( NvM_Nvb_StatusType, NVM_CODE ) NvM_Nvb_GetStatus( void );

FUNC( void, NVM_CODE )
NvM_Nvb_SetMode(
    NvM_Nvb_ModeType Mode
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_NVB_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/11/14                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
