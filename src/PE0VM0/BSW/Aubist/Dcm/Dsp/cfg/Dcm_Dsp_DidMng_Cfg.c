/* Dcm_Dsp_DidMng_Cfg_c(v5-4-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng_Cfg/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_DidMng_Cfg.h"
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetDidIndex
(
    const uint16 u2DDDid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
VAR( uint8, DCM_VAR_NO_INIT ) DcmDspDDDidNumOfSourceElement[ DCM_P_DDDID_T ];
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/* -----------------------------VALUE TABLE----------------------------- */

/*------------*/
/* DcmDspData */
/*------------*/
#if ( DCM_SUPPORT_SID2F == STD_ON )
/* DcmDspDataFreezeCurrentStateFnc--------------------- */
/* Sync */
CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_FreezeCurrentStateFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncFreezeCurrentStateFuncTbl[ DCM_P_DATA_SYNC_FCS_FNC_T ] = 
{
    NULL_PTR
};
/* Async */
CONST( AB_83_ConstV Dcm_Dsp_Data_Async_FreezeCurrentStateFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncFreezeCurrentStateFuncTbl[ DCM_P_DATA_ASYNC_FCS_FNC_T ] = 
{
    NULL_PTR
};

/* DcmDspDataReadFnc----------------------------------- */
/* Sync */
CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_ReadFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncReadFuncTbl[ DCM_P_DATA_SYNC_READ_FNC_T ] = 
{
    NULL_PTR
};
/* Async */
CONST( AB_83_ConstV Dcm_Dsp_Data_Async_ReadFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncReadFuncTbl[ DCM_P_DATA_ASYNC_READ_FNC_T ] = 
{
    NULL_PTR
};
/* Async Err */
CONST( AB_83_ConstV Dcm_Dsp_Data_AsyncErr_ReadFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncErrReadFuncTbl[ DCM_P_DATA_ASYNC_ERR_READ_FNC_T ] = 
{
    NULL_PTR
};

/* DcmDspDataResetToDefaultFnc------------------------- */
/* Sync */
CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_ResetToDefaultFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncResetToDefaultFuncTbl[ DCM_P_DATA_SYNC_RTD_FNC_T ] = 
{
    NULL_PTR
};
/* Async */
CONST( AB_83_ConstV Dcm_Dsp_Data_Async_ResetToDefaultFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncResetToDefaultFuncTbl[ DCM_P_DATA_ASYNC_RTD_FNC_T ] = 
{
    NULL_PTR
};

/* DcmDspDataReturnControlToEcuFnc--------------------- */
/* Aubist */
CONST( AB_83_ConstV Dcm_Dsp_Data_ReturnControlToECUFuncType, DCM_CONFIG_DATA ) DcmDspDataReturnControlToECUFuncTbl[ DCM_P_DATA_RCTECU_FNC_T ] = 
{
    NULL_PTR
};

/* DcmDspDataShortTermAdjustmentFnc-------------------- */
/* Sync */
CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_ShortTermAdjustmentFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncShortTermAdjustmentFuncTbl[ DCM_P_DATA_SYNC_STA_FNC_T ] = 
{
    NULL_PTR
};
/* Async */
CONST( AB_83_ConstV Dcm_Dsp_Data_Async_ShortTermAdjustmentFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncShortTermAdjustmentFuncTbl[ DCM_P_DATA_ASYNC_STA_FNC_T ] = 
{
    NULL_PTR
};


#endif /* DCM_SUPPORT_SID2F == STD_ON */
/*---------------*/
/* DcmDspDidInfo */
/*---------------*/
/* DcmDspDidXXXXXXSecurityLevelRef */
/* DcmDspDidXXXXXXSessionRef */
/* DcmDspDidControl */

/* DcmDspDidRead */

/* DcmDspDidWrite */


/*-----------*/
/* DcmDspDid */
/*-----------*/
/* DcmDspDidSignal */
#if ( DCM_SUPPORT_SID2F == STD_ON )

#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV Dcm_Dsp_DidType, DCM_CONFIG_DATA ) DcmDspDidTbl[ DCM_P_DID_T ] = 
{
    { NULL_PTR,               NULL_PTR,               NULL_PTR,                   (uint16)0x0000U, (uint8)0U, (boolean)FALSE, (boolean)FALSE } /* <-Dummy Data */
};
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV Dcm_Dsp_DDDidType, DCM_CONFIG_DATA ) DcmDspDDDidTbl[ DCM_P_DDDID_T ] = 
{

    { NULL_PTR, (uint16)0x0000U }
};
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_u2DidNumber = DCM_P_DID_N;
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

/*----------------*/
/* DcmDspDidRange */
/*----------------*/
#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV Dcm_Dsp_DidRangeType, DCM_CONFIG_DATA ) DcmDspDidRangeTbl[ DCM_P_DIDRANGE_T ] = 
{
    { NULL_PTR,                  NULL_PTR,                          NULL_PTR,               NULL_PTR,                NULL_PTR,               (uint16)0x0000U, (uint16)0x0000U, (boolean)FALSE, (boolean)FALSE } /* <-Dummy Data */
};
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_u2DidRangeNumber = DCM_P_DIDRANGE_N;
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

/*-------------*/
/* DcmDspDDDid */
/*-------------*/
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_u2DDDidNumber = DCM_P_DDDID_N;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

/*--------------*/
/* DcmDspMemory */
/*--------------*/
/* DcmDspMemoryXXXXXXSecurityLevelRef */




#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV Dcm_Dsp_MemoryType, DCM_CONFIG_DATA ) DcmDspMemory = 
{
    NULL_PTR, NULL_PTR, (uint8)0U
};

#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_bChk_Per_Source_Did = (boolean)FALSE;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_Fcs_Fnc_T = (uint16)DCM_P_DATA_SYNC_FCS_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_Fcs_Fnc_T = (uint16)DCM_P_DATA_ASYNC_FCS_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_Read_Fnc_T = (uint16)DCM_P_DATA_SYNC_READ_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_Read_Fnc_T = (uint16)DCM_P_DATA_ASYNC_READ_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_Err_Read_FNC_T = (uint16)DCM_P_DATA_ASYNC_ERR_READ_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_RTD_Fnc_T = (uint16)DCM_P_DATA_SYNC_RTD_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_RTD_Fnc_T = (uint16)DCM_P_DATA_ASYNC_RTD_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_RCTECU_Fnc_T = (uint16)DCM_P_DATA_RCTECU_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_STA_Fnc_T = (uint16)DCM_P_DATA_SYNC_STA_FNC_T;
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_STA_Fnc_T = (uint16)DCM_P_DATA_ASYNC_STA_FNC_T;
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Did_T = (uint16)DCM_P_DID_T;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Didrange_T = (uint16)DCM_P_DIDRANGE_T;
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Dddid_T = (uint16)DCM_P_DDDID_T;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Sid2c_Res_Max_Data_Length = (uint16)DCM_P_SID2C_RES_MAX_DATA_LENGTH;
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) )
CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Source_Did_Max_Data_Size = (uint16)DCM_P_SOURCE_DID_MAX_DATA_SIZE;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON */

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetSourceDID                              */
/* Description   | Set DDDID to RAM                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DDDid Table                 */
/*               | [in] u1SourceDidIndex : Index of SourceElement Table     */
/*               | [in] ptSourceElement : Pointer to Source Did Element     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK : Set success                                  */
/*               |      E_NOT_OK : Set failure                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetSourceDID
(
    const uint16 u2DDDidIndex,
    const uint8 u1SourceDidIndex,
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) ptSourceElement
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_DidIndex;
    uint16 u2_DataId;

    u1_RetVal = E_NOT_OK;

    if( u2DDDidIndex < DCM_P_DDDID_T )
    {
        if( DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef != NULL_PTR )
        {
            u2_DataId = DcmDspDDDidTbl[u2DDDidIndex].u2DDDid;
            u1_FuncRet = Dcm_Dsp_DidMng_GetDidIndex(u2_DataId, &u2_DidIndex);
            if( u1_FuncRet == (Std_ReturnType)E_OK )
            {
                if( u2_DidIndex < DCM_P_DID_T )
                {
                    if( u1SourceDidIndex < DcmDspDidTbl[u2_DidIndex].ptInfoRef->u1DDDIDMaxElements )
                    {
                        DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u2SourceDid = ptSourceElement->u2SourceDid;
                        DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1Position = ptSourceElement->u1Position;
                        DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1Size = ptSourceElement->u1Size;
                        DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u4MemAddr = ptSourceElement->u4MemAddr;
                        DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u4MemSize = ptSourceElement->u4MemSize;
                        DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1MemId = ptSourceElement->u1MemId;
                        DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1SourceElementId = ptSourceElement->u1SourceElementId;

                        u1_RetVal = E_OK;
                    }
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == STD_ON */


#if ( DCM_NVM_DDDID_USE == STD_ON )
#endif /* DCM_NVM_DDDID_USE == STD_ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetNumOfSrcDid                            */
/* Description   | Sets the number of SourceDIDs associated with DDDID      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of Dcm_Dsp_DDDid               */
/*               | [in] u1NumOfSourceDid : Number of SourceDID              */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK : Set success                                  */
/*               |      E_NOT_OK : Set failure                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetNumOfSrcDid
(
    const uint16 u2DDDidIndex,
    const uint8 u1NumOfSourceDid
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( u2DDDidIndex < DCM_P_DDDID_T )
    {
        DcmDspDDDidNumOfSourceElement[ u2DDDidIndex ] = u1NumOfSourceDid;

        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == STD_ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ClrNumOfSrcElm                            */
/* Description   | Clear Number of Source Element                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DDDid Table                 */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK : Clear success                                */
/*               |      E_NOT_OK : Clear failure                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClrNumOfSrcElm
(
    const uint16 u2DDDidIndex
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( u2DDDidIndex < DCM_P_DDDID_T )
    {
        DcmDspDDDidNumOfSourceElement[ u2DDDidIndex ] = (uint8)0U;

        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ClrAllNumOfSrcElm                         */
/* Description   | Clear All Number of Source Element                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK : Clear success                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClrAllNumOfSrcElm
(
    void
)
{
    sint32 s4_DDDidSearchCnt;
    uint16 u2_DDDidNumber;

    u2_DDDidNumber = Dcm_P_DIDMNG_u2DDDidNumber;

    for( s4_DDDidSearchCnt = (sint32)0; s4_DDDidSearchCnt < (sint32)u2_DDDidNumber; s4_DDDidSearchCnt++ )
    {
        DcmDspDDDidNumOfSourceElement[s4_DDDidSearchCnt] = (uint8)0U;
    }

    return E_OK;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON  */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetNumOfSrcDid                            */
/* Description   | Returns the number of SourceDIDs associated with DDDID   */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of Dcm_Dsp_DDDid               */
/*               | [out] ptNumOfSourceDid : Number of SourceDID             */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK : Get success                                  */
/*               |      E_NOT_OK : Get failure                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetNumOfSrcDid
(
    const uint16 u2DDDidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptNumOfSourceDid
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( u2DDDidIndex < DCM_P_DDDID_T )
    {
        *ptNumOfSourceDid = DcmDspDDDidNumOfSourceElement[ u2DDDidIndex ];
        u1_RetVal = E_OK;
    }
    
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetSourceDID                              */
/* Description   | Get DDDID to RAM                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DDDid Table                 */
/*               | [in] u1SourceDidIndex : Index of SourceElement Table     */
/*               | [out] ptSourceElement : SourceElement structure          */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK : Get success                                  */
/*               |      E_NOT_OK : Get failure                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetSourceDID
(
    const uint16 u2DDDidIndex,
    const uint8 u1SourceDidIndex,
    P2VAR( Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) ptSourceElement
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_DidIndex;
    uint16 u2_DDDid;

    u1_RetVal = E_NOT_OK;

    if( u2DDDidIndex < DCM_P_DDDID_T )
    {
        if( DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef != NULL_PTR )
        {
            u2_DDDid = DcmDspDDDidTbl[u2DDDidIndex].u2DDDid;
            u1_FuncRet = Dcm_Dsp_DidMng_GetDidIndex(u2_DDDid, &u2_DidIndex);
            if( u1_FuncRet == (Std_ReturnType)E_OK )
            {
                if( u2_DidIndex < DCM_P_DID_T )
                {
                    if( u1SourceDidIndex < DcmDspDidTbl[u2_DidIndex].ptInfoRef->u1DDDIDMaxElements )
                    {
                        ptSourceElement->u2SourceDid = DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u2SourceDid;
                        ptSourceElement->u1Position = DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1Position;
                        ptSourceElement->u1Size = DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1Size;
                        ptSourceElement->u4MemAddr = DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u4MemAddr;
                        ptSourceElement->u4MemSize = DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u4MemSize;
                        ptSourceElement->u1MemId = DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1MemId;
                        ptSourceElement->u1SourceElementId = DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef[u1SourceDidIndex].u1SourceElementId;

                        u1_RetVal = E_OK;
                    }
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetDidIndex                               */
/* Description   | Get Index of DID Table                                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : u2DDDid                              */
/*               | [out] ptDidIndex : Index of Did Table                    */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK : Get success                                  */
/*               |      E_NOT_OK : Get failure                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetDidIndex
(
    const uint16 u2DDDid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex
)
{
    Std_ReturnType u1_RetVal;
    boolean b_CheckFlag;
    boolean b_BreakFlag;
    uint16 u2_TopIndex;
    uint16 u2_MidIndex;
    uint16 u2_EndIndex;
    uint16 u2_DidNumber;

    u1_RetVal = E_NOT_OK;
    b_CheckFlag = (boolean)FALSE;
    b_BreakFlag = (boolean)FALSE;
    u2_DidNumber = Dcm_P_DIDMNG_u2DidNumber;

    if( u2_DidNumber != (uint16)0U )
    {
        u2_TopIndex = (uint16)0U;
        u2_EndIndex = (uint16)(u2_DidNumber - (uint16)1U);
        
        if( DcmDspDidTbl[u2_TopIndex].u2Identifier > u2DDDid )
        {
            /* no process */
        }
        else if( DcmDspDidTbl[u2_TopIndex].u2Identifier == u2DDDid )
        {
            b_CheckFlag = (boolean)TRUE;
        }
        else if( DcmDspDidTbl[u2_EndIndex].u2Identifier < u2DDDid )
        {
            /* no process */
        }
        else
        {
            while( u2_TopIndex < u2_EndIndex )
            {
                u2_MidIndex = (u2_EndIndex + u2_TopIndex) >> (uint16)1U;
                if( DcmDspDidTbl[u2_MidIndex].u2Identifier < u2DDDid )
                {
                    u2_TopIndex = u2_MidIndex + (uint16)1U;
                }
                else
                {
                    u2_EndIndex = u2_MidIndex;
                }
                
                if( DcmDspDidTbl[u2_TopIndex].u2Identifier == u2DDDid )
                {
                    b_CheckFlag = (boolean)TRUE;
                    b_BreakFlag = (boolean)TRUE;
                }
                
                if( b_BreakFlag == (boolean)TRUE )
                {
                    break;
                }
            }
        }
        
        if( b_CheckFlag == (boolean)TRUE )
        {
            *ptDidIndex = u2_TopIndex;
            u1_RetVal = E_OK;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/*********************************************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CheckSupportedDid                                                      */
/* Description   | Requests if a specific DID is available.                                              */
/* Preconditions | None                                                                                  */
/* Parameters    | [IN] u2Did       : DID value                                                          */
/*               | [IN] u1ReqType   : DID Support Request Type                                           */
/*               | [IN] u2PduId     : Received PduID                                                     */
/* Return Value  | Std_ReturnType                                                                        */
/*               |   E_OK              : DID Supported                                                   */
/*               |   E_NOT_OK          : DID Not Supported                                               */
/* Notes         | None                                                                                  */
/*********************************************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CheckSupportedDid
(
    uint16 u2Did,
    Dcm_DidRequestType u1ReqType,
    uint16 u2PduId
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_CheckSupportedDid( u2Did, u1ReqType, u2PduId );
    
    return u1_RetVal;
}

#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
