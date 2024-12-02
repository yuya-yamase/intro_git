/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/

/****************************************************************************/
/* Object Name  | Fls/CODE                                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Fls_Drv.h"
#include "../inc/Fls_Mpu.h"
#include "../usr/Fls_Callout.h"
#include <Fls.h>
#include <Fls_Cdd.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*****************************************************************************
  Global variables
 ****************************************************************************/
#define FLS_START_SEC_VAR_NO_INIT_32
#include <Fls_MemMap.h>

VAR(FLS_DRV_DATA_T, FLS_VAR_NO_INIT) Fls_Str;

#define FLS_STOP_SEC_VAR_NO_INIT_32
#include <Fls_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define FLS_START_SEC_CODE
#include <Fls_MemMap.h>

#if ( FLS_Drv_HSM_VALUE == FLS_Drv_HSM_ICUM ) || \
    ( FLS_Drv_HSM_VALUE == FLS_Drv_HSM_OFF )
/*****************************************************************************
   Function      : Initialization Function(ICU-OFF)
   Description   : This API executes the registers of the Data Flash Driver
                    and provides internal information managed by the Data Flash Driver.
   param[in]     : ConfigPtr (Configuration pointer)
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Init(
    P2CONST( Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST ) ConfigPtr
)
{
    Std_ReturnType  st_chk;         /* initialization status */
    Fls_StatusType  st_ret;
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    uint8   u1_rpt = FLS_E_EXT_UNINIT;                 /* report content */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    uint8  u1_AreaLoopCnt;          /* loop counter */

    st_chk = E_OK;                  /* continue processing */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    u1_AreaLoopCnt = FLS_DRV_U1_VAL_0;
#endif

    Fls_Drv_InitVariables();

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    for( u1_AreaLoopCnt = FLS_DRV_U1_VAL_0; u1_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u1_AreaLoopCnt++ )
    {
#endif
    /* ---------------------- Reset process ---------------------------- */
        Fls_Drv_ResetInitr(u1_AreaLoopCnt);
        st_ret = Fls_Drv_Reset(u1_AreaLoopCnt);

        if( FLS_DRV_U1_OK != st_ret )
        {
            st_chk = E_NOT_OK;

            /* report:Initialization failed error                     */
            /* If FLS_DEV_ERROR_DETECT == STD_ON, The value of u1_rpt */
            /* is FLS_E_EXT_UNINIT set as the initial value.          */

            Fls_Str.stiJobResult_enu = MEMIF_JOB_FAILED;
        }

        /* ---------------------- initialize FLS internal variable ----------------------- */
        /* ---------------------- load firmware to RAM ----------------- */
        /* ---------------------- reset process ---------------------------- */
        else
        {
            Fls_Drv_InitRegister(u1_AreaLoopCnt);
        }
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    }
#endif

    /* ---------------------- frequency setting process -------------------------- */
    /* ---------------------- initialization processing completion determination ----------------------- */
    if( (Std_ReturnType)E_OK == st_chk )
    {
        Fls_Str.stiJobResult_enu = MEMIF_JOB_OK;
    }
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    else
    {
        /* A report is notified when an error has occurred. */
        (void)Fls_ErrorHook(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_APIID_INIT, u1_rpt);
    }
#endif /* FLS_DEV_ERROR_DETECT */

} /* Fls_Init */

/*****************************************************************************
   Function      : Write Request(ICU-OFF)
   Description   : This API executes the Flash write operation.
                   After execution, the function 'Fls_MainFunction' should be called 
                   regularly to finish the operation.
   param[in]     : TargetAddress   (Target address)
   param[in]     : SourceAddressPtr(Pointer to the data)
   param[in]     : Length          (Number of bytes to be written)
   return        : E_OK            (Processing result OK (return value))
                 : E_NOT_OK        (Processing result NG (return value))
   Note          : -
*****************************************************************************/
FUNC( Std_ReturnType, FLS_CODE ) 
Fls_Write(
    Fls_AddressType TargetAddress,
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) SourceAddressPtr,
    Fls_LengthType Length
)
{
    Std_ReturnType  st_ret;             /* return value */
    Fls_StatusType  st_result;          /* return value of a called function */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    Fls_DataArea    st_area;            /* return of Target area */
#endif
    uint32          u4_addFlash;        /* start address of the memory to be written */
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) pt_AddBuf; /* start address of data buffer */
    uint32          u4_cntCurOp;        /* access size */
    uint32          u4_cntTotal;        /* write data size(total size) */
    uint8           u1_AreaLoopCnt;     /* area loop counter */
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) pt_BufAdd;
    uint32          u4_FlashAdd;
    uint32          u4_FlashAddEnd;
    uint32          u4_DataBufPos;
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    uint8           u1_reportErr;       /* report */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    u1_reportErr = FLS_E_EXT_WRITE_FAILED;
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    u1_AreaLoopCnt = FLS_DRV_U1_VAL_0;
#endif

    /* check FLS internal state */
    if( MEMIF_IDLE == Fls_Str.stiStat_enu )
    {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* check parameter */
        st_ret = Fls_Drv_ChkBuffer_u1(SourceAddressPtr);
        if( (Std_ReturnType)E_OK != st_ret )
        {
            u1_reportErr = FLS_E_EXT_PARAM_DATA;    /* Buffer NULL error */
        }
        else
        {
            st_ret = Fls_Drv_ChkAddress(TargetAddress, FLS_DRV_U4_ACCESS_SIZE);
            if( (Std_ReturnType)E_OK != st_ret )
            {
                u1_reportErr = FLS_E_EXT_PARAM_ADDRESS;    /* Address error */
            }
            else
            {
                st_ret = Fls_Drv_ChkLength(TargetAddress, Length, FLS_DRV_U4_ACCESS_SIZE);
                if( (Std_ReturnType)E_OK != st_ret )
                {
                    u1_reportErr = FLS_E_EXT_PARAM_LENGTH;    /* Length error */
                }
            }
        }
#else  /* FLS_DEV_ERROR_DETECT == STD_ON */
        st_ret = E_OK;
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        if( (Std_ReturnType)E_OK == st_ret )
        {
#endif /* LS_DEV_ERROR_DETECT == STD_ON */

            /* store information to local variables. */
            pt_AddBuf   = SourceAddressPtr;
            u4_addFlash = TargetAddress;
            u4_cntTotal = Length;
            u4_cntCurOp = FLS_DRV_U4_ACCESS_SIZE;

            pt_BufAdd     = &(pt_AddBuf[u4_cntCurOp]);
            u4_FlashAdd   = u4_addFlash + u4_cntCurOp;
            if((u4_addFlash + u4_cntTotal) > FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE)
            {
                u4_FlashAddEnd = FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE - FLS_DRV_U4_VAL_1;
            }
            else
            {
                u4_FlashAddEnd = (u4_addFlash + u4_cntTotal) - FLS_DRV_U4_VAL_1;
            }
            u4_DataBufPos = FLS_DRV_U4_VAL_0;

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
            /* calculate the target area */
            st_area = Fls_Drv_CalculateTargetArea(TargetAddress, Length);

            for( u1_AreaLoopCnt = FLS_DRV_U1_VAL_0; u1_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u1_AreaLoopCnt++ )
            {
#endif
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].ptBufAdd       = NULL_PTR;
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAdd     = FLS_DRV_U4_VAL_0;
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAddEnd  = FLS_DRV_U4_VAL_0;
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].stStatus       = FLS_DRV_U1_OK;

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
                if( (st_area & (uint8)(FLS_DRV_U1_VAL_1 << u1_AreaLoopCnt) ) != FLS_DRV_U1_VAL_0 )
                {
#endif
                    /* refresh processing */
                    Fls_Drv_ResetRegister(u1_AreaLoopCnt);

                    /* switch to P/E mode */
                    st_result = Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_PE, u1_AreaLoopCnt);
                    if( FLS_DRV_U1_OK == st_result )
                    {

                        /* remove protection */
                        Fls_Drv_SetProtect(FLS_DRV_U4_PROTECT_MODE_OFF, u1_AreaLoopCnt);

                        /* start writing the data in calculated data area (data area 0 or data area 1) */
                        st_result = Fls_Drv_StartWriteOperation(&(pt_AddBuf[u4_DataBufPos]), 
                                                                u4_addFlash, 
                                                                u4_cntCurOp, 
                                                                u1_AreaLoopCnt);


                        if( FLS_DRV_U1_BUSY == st_result )
                        {
                            /* operating successfully in progress if it comes here. */
                            /* (In fact there is a possibility that the write error has occurred but it is detected by Fls_MainFunction().) */
                            /* set the information of each address to carry out the continuation of the process in Fls_MainFunction() */
                            /* set data for data area */
                            Fls_Str.stMulOp_str[u1_AreaLoopCnt].ptBufAdd      = pt_BufAdd;
                            Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAdd    = u4_FlashAdd;
                            Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAddEnd = u4_FlashAddEnd;

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
                            if( FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE >= u4_addFlash )
                            {
                                /* If there is a next area to process, set the address of the buffer to be */
                                /* used for writing to next area.. */
                                pt_BufAdd      = &(pt_AddBuf[((FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE - u4_addFlash) + FLS_DRV_U4_ACCESS_SIZE)]);
                                u4_FlashAddEnd = (u4_addFlash + u4_cntTotal) - FLS_DRV_U4_VAL_1;

                                u4_DataBufPos  = FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE - u4_addFlash;
                                u4_addFlash    = FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE * ((uint32)u1_AreaLoopCnt + FLS_DRV_U4_VAL_1);
                                u4_FlashAdd    = u4_addFlash + u4_cntCurOp;
                            }
#endif

                            /* set the command to FLS_DRV_U1_CMDTYPE_WRITE, set the FLS state to BUSY, set the processing result to processing */
                            Fls_Str.stMulOp_str[u1_AreaLoopCnt].stCommand_enu = FLS_DRV_U1_CMDTYPE_WRITE;
                        }
                        else
                        {
                            /* error recovery */
                            Fls_Drv_ErrRefresh(u1_AreaLoopCnt);

                            /* set protection */
                            Fls_Drv_SetProtect(FLS_DRV_U4_PROTECT_MODE_ON, u1_AreaLoopCnt);

                            (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_AreaLoopCnt);

                            /* If FLS_DEV_ERROR_DETECT == STD_ON, The value of u1_reportErr */
                            /* is FLS_E_EXT_WRITE_FAILED set as the initial value.          */

                            st_ret = E_NOT_OK;
                        }
                    }
                    else
                    {
                        /* switch to read mode for recovery process */
                        (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_AreaLoopCnt);

                        /* If FLS_DEV_ERROR_DETECT == STD_ON, The value of u1_reportErr */
                        /* is FLS_E_EXT_WRITE_FAILED set as the initial value.          */

                        st_ret = E_NOT_OK;
                    }
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
                }
                else
                {
                    u4_FlashAddEnd = (u4_addFlash + u4_cntTotal) - FLS_DRV_U4_VAL_1;
                }
            }
#endif
            if( (Std_ReturnType)E_OK == st_ret )
            {
                Fls_Str.stiStat_enu               = MEMIF_BUSY;
                Fls_Str.stiJobResult_enu          = MEMIF_JOB_PENDING;
            }
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

    }
    else
    {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        u1_reportErr = FLS_E_EXT_BUSY;         /* execution during the busy state */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
        st_ret       = E_NOT_OK;
    }

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    if( (Std_ReturnType)E_OK != st_ret )
    {
        (void)Fls_ErrorHook( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_APIID_WRITE, u1_reportErr );
    }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    return (st_ret);

} /* Fls_Write */

/*****************************************************************************
   Function      : Erasure Request(ICU-OFF)
   Description   : This API executes the Flash erase operation.
                    After execution, the function 'Fls_MainFunction' should be called 
                    regularly to finish the operation.
   param[in]     : TargetAddress (Target address)
   param[in]     : Length        (Number of bytes to erase)
   return        : E_OK          (Processing result OK (return value))
                 : E_NOT_OK      (Processing result NG (return value))
   Note          : -
*****************************************************************************/
FUNC( Std_ReturnType, FLS_CODE ) 
Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length)
{
    Std_ReturnType  st_ret;             /* return value */
    Fls_StatusType  st_result;          /* return value of a called function */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    Fls_DataArea    st_area;            /* return of Target area */
#endif
    uint32          u4_addFlash;        /* start address of the memory to be erased */
    uint32          u4_cntTotal;        /* total byte size of the erased data */
    uint32          u4_addEndCurOp;     /* end address of data buffer */
    uint32          u4_blockNum;        /* number of blocks */
    uint32          u4_FlashAdd;
    uint32          u4_FlashAddEnd;
    uint8           u1_AreaLoopCnt;
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    uint8           u1_reportErr;       /* report */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    u1_reportErr = FLS_E_EXT_ERASE_FAILED;
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    u1_AreaLoopCnt = FLS_DRV_U1_VAL_0;
#endif

    /* check FLS internal state */
    if( MEMIF_IDLE == Fls_Str.stiStat_enu )
    {

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* check parameter */
        st_ret = Fls_Drv_ChkAddress(TargetAddress, FLS_DRV_U4_BLOCK_SIZE);
        if( (Std_ReturnType)E_OK != st_ret )
        {
            u1_reportErr = FLS_E_EXT_PARAM_ADDRESS;    /* Address error */
        }
        else
        {
            st_ret = Fls_Drv_ChkEraseLength(TargetAddress, Length);
            if( (Std_ReturnType)E_OK != st_ret )
            {
                u1_reportErr = FLS_E_EXT_PARAM_LENGTH;    /* Length error */
            }
        }
#else  /* FLS_DEV_ERROR_DETECT == STD_ON */
        st_ret = E_OK;
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        if( (Std_ReturnType)E_OK == st_ret )
        {
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

            /* Information on an argument is stored in a local variable. */
            u4_addFlash    = TargetAddress;
            u4_addEndCurOp = (u4_addFlash + FLS_DRV_U4_BLOCK_SIZE) - FLS_DRV_U4_VAL_1;

            /* 1 block is equivalent to 4 Kbytes(4096 bytes) for U2A8*/
            /* 4097 bytes is calculated as to 2 blocks (8192 bytes) */
            u4_blockNum = Length >> FLS_DRV_U2_BLOCK_SIZE_2N;
            if( FLS_DRV_U4_VAL_0 != ( Length & ( FLS_DRV_U4_BLOCK_SIZE - FLS_DRV_U4_VAL_1 ) ) )
            {
                u4_blockNum = u4_blockNum + FLS_DRV_U4_VAL_1;
            }
            /* set the total size of the data to be erased (max 64 * 4096 = 262144byte) */
            u4_cntTotal = u4_blockNum * FLS_DRV_U4_BLOCK_SIZE;

            u4_FlashAdd = u4_addEndCurOp + FLS_DRV_U4_VAL_1;
            if((u4_addFlash + u4_cntTotal) > FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE)
            {
                u4_FlashAddEnd = FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE - FLS_DRV_U4_VAL_1;
            }
            else
            {
                u4_FlashAddEnd = (u4_addFlash + u4_cntTotal) - FLS_DRV_U4_VAL_1;
            }

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
            /* calculate the target area */
            st_area = Fls_Drv_CalculateTargetArea(TargetAddress, Length);

            for( u1_AreaLoopCnt = FLS_DRV_U1_VAL_0; u1_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u1_AreaLoopCnt++ )
            {
#endif
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].ptBufAdd       = NULL_PTR;
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAdd     = FLS_DRV_U4_VAL_0;
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAddEnd  = FLS_DRV_U4_VAL_0;
                Fls_Str.stMulOp_str[u1_AreaLoopCnt].stStatus       = FLS_DRV_U1_OK;

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
                if( (st_area & (uint8)(FLS_DRV_U1_VAL_1 << u1_AreaLoopCnt) ) != FLS_DRV_U1_VAL_0 )
                {
#endif

                    /* refresh processing */
                    Fls_Drv_ResetRegister(u1_AreaLoopCnt);

                    /* switch to P/E mode */
                    st_result = Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_PE, u1_AreaLoopCnt);
                    if( FLS_DRV_U1_OK == st_result )
                    {

                        /* remove protection */
                        Fls_Drv_SetProtect(FLS_DRV_U4_PROTECT_MODE_OFF, u1_AreaLoopCnt);

                        /* start erasing the data in calculated data area (data area 0 or data area 1) */
                        st_result = Fls_Drv_StartBCEraseOperation(u4_addFlash, 
                                                                  u4_addEndCurOp, 
                                                                  FLS_DRV_U1_CMD_ERASE, 
                                                                  u1_AreaLoopCnt);

                        if( FLS_DRV_U1_BUSY == st_result )
                        {
                            /* operating successfully in progress if it comes here. */
                            /* (there is a possibility that the erase error has occurred but it is detected by Fls_MainFunction().) */
                            /* set the information of each address to carry out the continuation of the process in Fls_MainFunction() */

                            /* set data for data area 0 */
                            Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAdd    = u4_FlashAdd;
                            Fls_Str.stMulOp_str[u1_AreaLoopCnt].u4FlashAddEnd = u4_FlashAddEnd;

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
                            /* set data for data area 1 */
                            u4_FlashAddEnd = (u4_addFlash + u4_cntTotal) - FLS_DRV_U4_VAL_1;
                            u4_addFlash    = FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE * ((uint32)u1_AreaLoopCnt + FLS_DRV_U4_VAL_1);
                            u4_addEndCurOp = (u4_addFlash + FLS_DRV_U4_BLOCK_SIZE) - FLS_DRV_U4_VAL_1;
                            u4_FlashAdd    = FLS_DRV_U4_BOUNDARY_ONE_BLOCK_SIZE + FLS_DRV_U4_BLOCK_SIZE;
#endif

                            /* set the command to FLS_DRV_U1_CMDTYPE_ERASE, set the FLS state to BUSY, set the processing result to processing */
                            Fls_Str.stMulOp_str[u1_AreaLoopCnt].stCommand_enu = FLS_DRV_U1_CMDTYPE_ERASE;
                        }
                        else
                        {
                            /* error recovery */
                            Fls_Drv_ErrRefresh(u1_AreaLoopCnt);

                            /* set protection */
                            Fls_Drv_SetProtect(FLS_DRV_U4_PROTECT_MODE_ON, u1_AreaLoopCnt);

                            (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_AreaLoopCnt);

                            /* If FLS_DEV_ERROR_DETECT == STD_ON, The value of u1_reportErr */
                            /* is FLS_E_EXT_ERASE_FAILED set as the initial value.          */

                            st_ret       = E_NOT_OK;
                        }
                    }
                    else
                    {
                        /* switch to read mode for the recovery process */
                        (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_AreaLoopCnt);

                        /* If FLS_DEV_ERROR_DETECT == STD_ON, The value of u1_reportErr */
                        /* is FLS_E_EXT_ERASE_FAILED set as the initial value.          */

                        st_ret       = E_NOT_OK;
                    }
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
                }
                else
                {
                    u4_FlashAddEnd = (u4_addFlash + u4_cntTotal) - FLS_DRV_U4_VAL_1;
                }
            }
#endif
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

        if( (Std_ReturnType)E_OK == st_ret )
        {
            Fls_Str.stiStat_enu               = MEMIF_BUSY;
            Fls_Str.stiJobResult_enu          = MEMIF_JOB_PENDING;
        }

    }
    else
    {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        u1_reportErr = FLS_E_EXT_BUSY;         /* execution during the busy state */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
        st_ret       = E_NOT_OK;
    }

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    if( (Std_ReturnType)E_OK != st_ret )
    {
        (void)Fls_ErrorHook( FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_APIID_ERASE, u1_reportErr );
    }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    return (st_ret);

} /* Fls_Erase */

#if ( FLS_CANCEL_API == STD_ON )
/*****************************************************************************
   Function      : Cancel Request(ICU-OFF)
   Description   : This API cancels an ongoing job. The driver state 
                    is set to MEMIF_IDLE and the job result to 
                    MEMIF_JOB_CANCELED if the job is currently 
                    being processed.
                    Internal information ,which are managed by Data Flash Driver,
                    is initialized.
   param         : -
   return        : -
                 : -
   Note          : This API can be enabled or disabled by setting the 
                    compile option 'FLS_CANCEL_API' to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_Cancel(void)
{
    Fls_StatusType st_ret;
    Fls_StatusType st_EndStatus;

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    uint8   u1_rpt;     /* report */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    uint8   u1_AreaLoopCnt;

    st_EndStatus = FLS_DRV_U1_OK;
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    u1_AreaLoopCnt = FLS_DRV_U1_VAL_0;
#endif

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    for( u1_AreaLoopCnt = FLS_DRV_U1_VAL_0; u1_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u1_AreaLoopCnt++ )
    {
#endif
        /* forced stop the running job */
        st_ret = Fls_Drv_Reset(u1_AreaLoopCnt);

        if( FLS_DRV_U1_OK == st_ret )
        {
            /* check whether FLS processing result is "processing" */
            if( MEMIF_JOB_PENDING == Fls_Str.stiJobResult_enu )
            {
                /* in the case of "processing", it's set as "processing cancellation". */
                Fls_Str.stiJobResult_enu = MEMIF_JOB_CANCELED;
                Fee_JobErrorNotification();
            }
        }
        else
        {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
            u1_rpt = FLS_E_EXT_BUSY;
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
            st_EndStatus             = FLS_DRV_U1_BUSY;
        }

        /* set protection */
        Fls_Drv_SetProtect(FLS_DRV_U4_PROTECT_MODE_ON, u1_AreaLoopCnt);

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        if( FLS_DRV_U1_OK != st_ret )
        {
            (void)Fls_ErrorHook(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_APIID_CANCEL, u1_rpt);
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
    }
#endif

    if( FLS_DRV_U1_OK == st_EndStatus )
    {
        /* The job information is cleared. */
        Fls_Drv_ClearOperationInfo();

        /* FLS internal state is set to "IDLE". */
        Fls_Str.stiStat_enu = MEMIF_IDLE;
    }
    else
    {
        Fls_Str.stiJobResult_enu = MEMIF_JOB_FAILED;
    }

} /* Fls_Cancel */
#endif /* FLS_CANCEL_API == STD_ON */
/*****************************************************************************
   Function      : Periodic Process(ICU-OFF)
   Description   : This API performs the erase and write job processing.
                   The API is called cyclically until the job is 
                    processed completely.
   param         : -
   return        : -
   Note          : -
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_MainFunction( void )
{
    Fls_FlagType    st_contHdrFct;
    Fls_StatusType  st_status[FLS_DRV_U1_FCU_MAX];
    Fls_StatusType  st_EndStatus;
    Fls_StatusType  st_res;
    uint8           u1_AreaLoopCnt;
    uint8           u1_errArea;

    st_EndStatus   = FLS_DRV_U1_OK;
    u1_errArea     = FLS_DRV_U1_FCU_MAX;
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2B10 )
    u1_AreaLoopCnt = FLS_DRV_U1_VAL_0;
#endif

    /* check whether FLS internal state is 'busy' */
    if( MEMIF_BUSY == Fls_Str.stiStat_enu )
    {
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
        for( u1_AreaLoopCnt = FLS_DRV_U1_VAL_0; u1_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u1_AreaLoopCnt++ )
        {
#endif
            if((Fls_Str.stMulOp_str[u1_AreaLoopCnt].stCommand_enu != FLS_DRV_U1_CMDTYPE_NONE) &&
               ((Fls_Str.stMulOp_str[u1_AreaLoopCnt].stStatus     == FLS_DRV_U1_OK) ||
                (Fls_Str.stMulOp_str[u1_AreaLoopCnt].stStatus     == FLS_DRV_U1_BUSY)))
            {
                st_status[u1_AreaLoopCnt] = FLS_DRV_U1_OK;

                /* check the command execution state */
                st_contHdrFct = Fls_Drv_CheckStatus(&st_status[u1_AreaLoopCnt], u1_AreaLoopCnt);

                /* when the command process has been completed */
                if( FLS_DRV_U1_TRUE == st_contHdrFct )
                {
                    /* Processing of the continuation command */
                    st_contHdrFct = Fls_Drv_MultiOperation(&st_status[u1_AreaLoopCnt], u1_AreaLoopCnt);

                    /* when a command process has been completed */
                    if( FLS_DRV_U1_TRUE == st_contHdrFct )
                    {
                        st_res = Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_AreaLoopCnt);

                        if( FLS_DRV_U1_OK != st_res )
                        {
                            st_status[u1_AreaLoopCnt] = st_res;
                        }
                    }
                }
            }
            else
            {
                st_status[u1_AreaLoopCnt] = Fls_Str.stMulOp_str[u1_AreaLoopCnt].stStatus;
            }

            if( FLS_DRV_U1_OK != st_status[u1_AreaLoopCnt] )
            {
                u1_errArea = u1_AreaLoopCnt;
            }

            if( FLS_DRV_U1_BUSY == st_status[u1_AreaLoopCnt] )
            {
                st_EndStatus = FLS_DRV_U1_BUSY;
            }
            Fls_Str.stMulOp_str[u1_AreaLoopCnt].stStatus = st_status[u1_AreaLoopCnt];

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
        }
#endif

            /* check whether the command processing is continued or not */
        if( FLS_DRV_U1_BUSY != st_EndStatus )
        {
            if( FLS_DRV_U1_FCU_MAX == u1_errArea )
            {
                /* command complete process */
                Fls_Drv_EndCurrentOperation(FLS_DRV_U1_OK, FLS_DRV_U1_VAL_0);
            }
            else
            {
                /* command complete process */
                Fls_Drv_EndCurrentOperation(st_status[u1_errArea], u1_errArea);
            }

#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
            for( u1_AreaLoopCnt = FLS_DRV_U1_VAL_0; u1_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u1_AreaLoopCnt++ )
            {
#endif
                /* set protection */
                Fls_Drv_SetProtect(FLS_DRV_U4_PROTECT_MODE_ON, u1_AreaLoopCnt);
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
            }
#endif

        }

    }
    /*  FLS internal state is 'other than busy' */
    else
    {
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
        for( u1_AreaLoopCnt = FLS_DRV_U1_VAL_0; u1_AreaLoopCnt < FLS_DRV_U1_FCU_MAX; u1_AreaLoopCnt++ )
        {
#endif
            /* refresh SFR */
            (void)Fls_Drv_SwitchMode(FLS_DRV_U2_MODE_USER, u1_AreaLoopCnt);
#if ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A6 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 )
        }
#endif
        Fls_Str.stiStat_enu = MEMIF_IDLE;
    }

} /* Fls_MainFunction */

#else /* FLS_Drv_HSM_VALUE == FLS_Drv_HSM_ICUM ) || ( FLS_Drv_HSM_VALUE == FLS_Drv_HSM_OFF ) */
#error "Fls.c, wrong FLS_Drv_HSM_VALUE"
#endif /* ( FLS_Drv_HSM_VALUE == FLS_Drv_HSM_ICUM ) || ( FLS_Drv_HSM_VALUE == FLS_Drv_HSM_OFF ) */

#if ( FLS_GET_STATUS_API == STD_ON )
/*****************************************************************************
   Function      : Processing State Acquisition Request
   Description   : This API Returns the FLS module state.
   param         : -
   return        : MEMIF_IDLE   (Idle state)
                 : MEMIF_BUSY   (Busy state)
   Note          : This API can be enabled or disabled by setting the 
                    compile option 'FLS_GET_STATUS_API' to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( MemIf_StatusType, FLS_CODE ) 
Fls_GetStatus(void)
{
    /* return FLS internal state */
    return(Fls_Str.stiStat_enu);

} /* Fls_GetStatus */
#endif /* FLS_GET_STATUS_API == STD_ON */

#if ( FLS_GET_JOB_RESULT_API == STD_ON )
/*****************************************************************************
   Function      : Processing Result Acquisition Request
   Description   : This API returns the result of the last job.
   param         : -
   return        : MEMIF_JOB_OK       (Successed processing)
                 : MEMIF_JOB_FAILED   (Failed processing)
                 : MEMIF_JOB_PENDING  (Processing)
                 : MEMIF_JOB_CANCELED (Cancelled processing)
   Note          : This API can be enabled or disabled by setting the
                    compile option 'FLS_GET_JOB_RESULT_API' to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( MemIf_JobResultType, FLS_CODE ) 
Fls_GetJobResult( void )
{
    return(Fls_Str.stiJobResult_enu);

} /* Fls_GetJobResult */
#endif /* FLS_GET_JOB_RESULT_API == STD_ON */

#if ( FLS_SET_MODE_API == STD_ON )
/*****************************************************************************
   Function      : Mode Setting Request
   Description   : This API sets the mode of Data Flash Driver.
   param[in]     : Mode (Mode of Data Flash Driver)
   return        : -
   Note          : This API can be enabled or disabled by setting the
                    compile option 'FLS_SET_MODE_API' to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( void, FLS_CODE ) 
Fls_SetMode(MemIf_ModeType Mode)
{
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    if( MEMIF_BUSY == Fls_Str.stiStat_enu )
    {
        (void)Fls_ErrorHook(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_APIID_SETMODE, FLS_E_EXT_BUSY);
    }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

} /* Fls_SetMode */
#endif /* FLS_SET_MODE_API == STD_ON */

#if ( FLS_VERSION_INFO_API == STD_ON )
/*****************************************************************************
   Function      : Version Information Acquisition Request
   Description   : This API provides version information of Data Flash Driver.
   param[out]    : VersioninfoPtr (Version Information)
   return        : -
   Note          : This API can be enabled or disabled by setting the 
                   compile option 'FLS_VERSION_INFO_API' to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( void, FLS_CODE )
Fls_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA ) VersioninfoPtr )
{
    VersioninfoPtr->vendorID = FLS_VENDOR_ID;
    VersioninfoPtr->moduleID = FLS_MODULE_ID;
    VersioninfoPtr->sw_major_version = FLS_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = FLS_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = FLS_SW_PATCH_VERSION;
}
#endif /* FLS_VERSION_INFO_API == STD_ON */

#define FLS_STOP_SEC_CODE
#include <Fls_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* History                                                                  */
/* Version :Date                                                            */
/* [Number] :[Date]                                                         */
/****************************************************************************/

/**** End of File ***********************************************************/
