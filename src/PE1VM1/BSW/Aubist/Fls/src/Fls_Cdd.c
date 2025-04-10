/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Fls/Cdd/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Fls_Drv.h"
#include "../inc/Fls_Cdd_Mpu.h"
#include "../usr/Fls_Callout.h"
#include "../usr/Fls_Cdd_Callout.h"
#include <Fls_Cdd.h>
#include <Fls.h>

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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define FLS_START_SEC_CODE
#include <Fls_MemMap.h>


#if ( FLS_CDD_READ_API == STD_ON )
/*****************************************************************************
   Function      : Read Request(ICU-OFF)
   Description   : This API performs reading from the flash memory.
                    The data from the flash memory (source address) is read 
                    to the data buffer (Target address) of the 
                    application.
   param[in]     : SourceAddress       (Source address)
   param[in]     : TargetAddressPtr    (Pointer to store the read data)
   param[in]     : Length              (Size of the read data)
   return        : FLS_CDD_RSP_OK          (Normal end (Complex Driver))
                 : FLS_CDD_RSP_NG_PARAM    (Parameter error (Complex Driver))
                 : FLS_CDD_RSP_NG_BUSY     (Execution during the busy state (Complex Driver))
                 : FLS_CDD_RSP_NG_READ     (Read error (Complex Driver))
   Note          : This API can be enabled or disabled by setting the
                    compile option 'FLS_CDD_READ_API' to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Cdd_Read(
    Fls_AddressType SourceAddress,
    P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) TargetAddressPtr,
    Fls_LengthType Length
)
{
    Fls_Cdd_JobResultType  st_ret;      /* return value */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    Std_ReturnType  st_paramChk;        /* check parameter */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    Fls_StatusType  st_result;          /* return value of a called function */
    uint32          u4_addFlash;        /* target address (read address) */
    uint32          u4_cntTotal;        /* size of the read data */

    /* check FLS internal state */
    if( MEMIF_IDLE == Fls_Str.stiStat_enu )
    {

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* Check parameter */
        st_paramChk = Fls_Drv_ChkBuffer_u1(TargetAddressPtr);
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
            st_paramChk = Fls_Drv_ChkAddress(SourceAddress, FLS_DRV_U4_READ_SIZE);
            if( (Std_ReturnType)E_OK == st_paramChk )
            {
                st_paramChk = Fls_Drv_ChkLength(SourceAddress, Length, FLS_DRV_U4_READ_SIZE);
            }
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
            u4_addFlash = SourceAddress;
            u4_cntTotal = Length;

            st_result = Fls_Drv_ReadOperation(u4_addFlash, TargetAddressPtr, u4_cntTotal);
            if( FLS_DRV_U1_BUSY == st_result )
            {
                st_ret = FLS_CDD_RSP_OK;
            }
            else
            {
                st_ret = FLS_CDD_RSP_NG_READ;   /* read error */
            }
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        }
        else
        {
            st_ret = FLS_CDD_RSP_NG_PARAM;      /* parameter error */
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

    }
    else
    {
        st_ret = FLS_CDD_RSP_NG_BUSY;   /* execution during the busy state */
    }

    return(st_ret);

} /* Fls_Cdd_Read */
#endif /* FLS_CDD_READ_API == STD_ON */

#if ( FLS_CDD_COMPARE_API == STD_ON )
/*****************************************************************************
   Function      : Comparison Request(ICU-OFF)
   Description   : This API compares the contents of an area of flash memory 
                    with the user specified data buffer.
   param[in]     : SourceAddress       (Source address)
   param[in]     : TargetAddressPtr    (Pointer to target data buffer)
   param[in]     : Length              (Size of the comparison data)
   return        : FLS_CDD_RSP_OK          (Normal end (Complex Driver))
                 : FLS_CDD_RSP_NG_PARAM    (Parameter error (Complex Driver))
                 : FLS_CDD_RSP_NG_BUSY     (Execution during the busy state (Complex Driver))
                 : FLS_CDD_RSP_NG_COMPARE  (Comparison error (Complex Driver))
                 : FLS_CDD_RSP_NG_SUSPEND  (Unauthorized suspend state)
   Note          : This API can be enabled or disabled by setting the 
                    'FLS_CDD_COMPARE_API' compile option to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Cdd_Compare(
    Fls_AddressType SourceAddress,
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr,
    Fls_LengthType Length)
{
    Fls_Cdd_JobResultType  st_ret;  /* return value */
    Fls_StatusType  st_result;      /* return value of a called function */
    uint32          u4_addFlash;    /* address of source data in Data Flash */
    P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) pt_AddBuf;/* pointer to target data buffer */
    uint32          u4_cntTotal;    /* size of the comparison data */
    uint32          u4_readLen;
    uint8           u1_compareBuf[FLS_DRV_U4_PROC_COMP_MAX_SIZE]; /* for storing comparison data */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    Std_ReturnType  st_paramChk;    /* check parameter */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

    /* check FLS internal state */
    if( MEMIF_IDLE == Fls_Str.stiStat_enu )
    {

#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* check parameter */
        st_paramChk = Fls_Drv_ChkBuffer_u1(TargetAddressPtr);
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
            st_paramChk = Fls_Drv_ChkAddress(SourceAddress, FLS_DRV_U4_COMP_SIZE);
            if( (Std_ReturnType)E_OK == st_paramChk )
            {
                st_paramChk = Fls_Drv_ChkLength(SourceAddress, Length, FLS_DRV_U4_COMP_SIZE);
            }
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
            st_ret      = FLS_CDD_RSP_OK;
            pt_AddBuf   = TargetAddressPtr;
            u4_addFlash = SourceAddress;
            u4_cntTotal = FLS_DRV_U4_VAL_0;
            if( Length <= FLS_DRV_U4_PROC_COMP_MAX_SIZE )
            {
                u4_readLen  = Length;
            }
            else
            {
                u4_readLen = FLS_DRV_U4_PROC_COMP_MAX_SIZE;
            }

            while( ( st_ret == FLS_CDD_RSP_OK ) && ( u4_cntTotal < Length ) )
            {
                st_result = Fls_Drv_ReadOperation(u4_addFlash, &u1_compareBuf[FLS_DRV_U1_VAL_0], u4_readLen);
                if( FLS_DRV_U1_BUSY == st_result )
                {

                    st_ret = Fls_Drv_CheckCompare(pt_AddBuf,&u1_compareBuf[FLS_DRV_U1_VAL_0], u4_readLen);
                    if( st_ret == FLS_CDD_RSP_OK )
                    {
                        pt_AddBuf    = &(pt_AddBuf[u4_readLen]);
                        u4_addFlash += u4_readLen;
                        u4_cntTotal += u4_readLen;
                        if( ( u4_cntTotal + FLS_DRV_U4_PROC_COMP_MAX_SIZE ) > Length )
                        {
                            u4_readLen  = Length - u4_cntTotal;
                        }
                        else
                        {
                            u4_readLen = FLS_DRV_U4_PROC_COMP_MAX_SIZE;
                        }

                    }
                    else
                    {
                        st_ret = FLS_CDD_RSP_NG_COMPARE;    /* comparison error */
                    }
                }
                else
                {
                    st_ret = FLS_CDD_RSP_NG_COMPARE;    /* comparison error */
                }
            }
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        }
        else
        {
            st_ret = FLS_CDD_RSP_NG_PARAM;    /* paraeter error */
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

    }
    else
    {
        st_ret = FLS_CDD_RSP_NG_BUSY;      /* execution during the busy state */
    }

    return(st_ret);

} /* Fls_Cdd_Compare */
#endif /* FLS_CDD_COMPARE_API == STD_ON */

#if ( FLS_CDD_BLANK_CHECK_API == STD_ON )
/*****************************************************************************
   Function      : Blank Check Request(ICU-OFF)
   Description   : This API verifies whether a given memory area has been erased.
   param[in]     : TargetAddress           (Target address)
   param[in]     : Length                  (Range to blank check)
   return        : FLS_CDD_RSP_OK              (Normal end (Complex Driver))
                 : FLS_CDD_RSP_NG_PARAM        (Parameter error (Complex Driver))
                 : FLS_CDD_RSP_NG_BUSY         (Execution during the busy state (Complex Driver))
                 : FLS_CDD_RSP_NG_BLANKCHECK   (Blank check error (Complex Driver))
                 : FLS_CDD_RSP_NG_FATALFAILED  (Fatal error (Complex Driver))
                 : FLS_CDD_RSP_NG_SUSPEND      (Unauthorized suspend state)
   Note          : This API can be enabled or disabled by setting the 
                    'FLS_CDD_BLANK_CHECK_API' compile option to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Cdd_BlankCheck(Fls_AddressType TargetAddress, Fls_LengthType Length)
{
    Fls_Cdd_JobResultType  st_ret;                 /* return value */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    Std_ReturnType  st_paramChk;            /* check parameter */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    Fls_StatusType  st_result;              /* return value of a called function */
    uint32          u4_addFlash;            /* start address of blank check */
    uint32          u4_addEndCurOp;         /* last address of blank check */

    P2VAR( Fls_AddressType, AUTOMATIC, FLS_APPL_DATA )    NotBlankAddress;            /* pointer to target data buffer */ 
    uint32          u4_Blankadd;         /* blank address */

    /* check FLS internal state */
    if( MEMIF_IDLE == Fls_Str.stiStat_enu )
    {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* check parameter */
        st_paramChk = Fls_Drv_ChkAddress(TargetAddress, FLS_DRV_U4_ACCESS_SIZE);
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
            st_paramChk = Fls_Drv_ChkLength(TargetAddress, Length, FLS_DRV_U4_ACCESS_SIZE);
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

            u4_addFlash = TargetAddress;
            u4_addEndCurOp = (u4_addFlash + Length) - FLS_DRV_U4_VAL_1;
            NotBlankAddress = &u4_Blankadd;

            st_result = Fls_Drv_StartBCOperation(u4_addFlash, u4_addEndCurOp, NotBlankAddress);

            if( FLS_DRV_U1_BUSY == st_result )
            {
                st_ret = FLS_CDD_RSP_OK;
            }
            else
            {
                 st_ret = FLS_CDD_RSP_NG_BLANKCHECK;    /* Blank check error */
            }
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        }
        else
        {
            st_ret = FLS_CDD_RSP_NG_PARAM;  /* parameter error */
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

    }
    else
    {
        st_ret = FLS_CDD_RSP_NG_BUSY;   /* execution during the busy state */
    }

    return(st_ret);

} /* Fls_Cdd_BlankCheck */
#endif /* FLS_CDD_BLANK_CHECK_API == STD_ON */

#if ( FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON ) 
/*****************************************************************************
   Function      : Not Blank Address Request(ICU-OFF)
   Description   : This API gives the biggest address in a given not-blank memory area
   param[in]     : TargetAddress           (Target address)
   param[in]     : Length                  (Range to blank check)
   param[in]     : NotBlankAddress         (Not-blank address)
   return        : FLS_CDD_RSP_OK              (Normal end (Complex Driver))
                 : FLS_CDD_RSP_NG_PARAM        (Parameter error (Complex Driver))
                 : FLS_CDD_RSP_NG_BUSY         (Execution during the busy state (Complex Driver))
                 : FLS_CDD_RSP_NG_ALLBLANK     (Blank error (Complex Driver))
                 : FLS_CDD_RSP_NG_FATALFAILED  (Fatal error (Complex Driver))
                 : FLS_CDD_RSP_NG_SUSPEND      (Unauthorized suspend state)
   Note          : This API can be enabled or disabled by setting the 
                    'FLS_CDD_NOT_BLANK_ADDRESS_API' compile option to 'STD_ON' or 'STD_OFF'.
*****************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Cdd_NotBlankAddress(Fls_AddressType TargetAddress, Fls_LengthType Length, P2VAR( Fls_AddressType, AUTOMATIC, FLS_APPL_DATA ) NotBlankAddress)
{
    Fls_Cdd_JobResultType  st_ret;          /* return value */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
    Std_ReturnType  st_paramChk;            /* check parameter */
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
    Fls_StatusType  st_result;              /* return value of a called function */
    uint32          u4_addFlash;            /* start address of blank check */
    uint32          u4_addEndCurOp;         /* last address of blank check */

    /* check FLS internal state */
    if( MEMIF_IDLE == Fls_Str.stiStat_enu )
    {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* check parameter */
        st_paramChk = Fls_Drv_ChkBuffer_u4(NotBlankAddress);
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
            st_paramChk = Fls_Drv_ChkAddress(TargetAddress, FLS_DRV_U4_ACCESS_SIZE);
            if( (Std_ReturnType)E_OK == st_paramChk )
            {
                st_paramChk = Fls_Drv_ChkLength(TargetAddress, Length, FLS_DRV_U4_ACCESS_SIZE);
            }
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        if( (Std_ReturnType)E_OK == st_paramChk )
        {
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */
            u4_addFlash = TargetAddress;
            u4_addEndCurOp = (u4_addFlash + Length) - FLS_DRV_U4_VAL_1;
   
            st_result = Fls_Drv_StartBCOperation(u4_addFlash, u4_addEndCurOp, NotBlankAddress);

            if( FLS_DRV_U1_BUSY == st_result )
            {
                st_ret = FLS_CDD_RSP_NG_ALLBLANK;  /* Target area is blank*/
            }
            else
            {
                st_ret = FLS_CDD_RSP_OK;   /* normal end */
            }
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        }
        else
        {
                st_ret = FLS_CDD_RSP_NG_PARAM;  /* parameter error */
        }
#endif /* FLS_DEV_ERROR_DETECT == STD_ON */

    }
    else
    {
        st_ret = FLS_CDD_RSP_NG_BUSY;   /* execution during the busy state */
    }

    return(st_ret);

}
#endif /* FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON */


#if ( FLS_CDD_SUSPEND_SYSTEM_API == STD_ON )
/*******************************************************************************
   Function      : Suspend Request
   Description   : This API shifts to suspend state when  
                    Erase / Write commands are executed in FACI state.
   param         : -
   return        : FLS_CDD_RSP_NG_SUSPEND   (Unauthorized suspend state)
   Note          : -
*******************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Cdd_Suspend( void )

{
    Fls_Cdd_JobResultType              st_ret;     /* return value */

    st_ret = FLS_CDD_RSP_NG_SUSPEND;    /* unauthorized suspend state */

    return(st_ret);
} /* Fls_Cdd_Suspend */


/*******************************************************************************
   Function      : Resume Request
   Description   : This API resumes the processing of FACI that are suspended.
   param         : -
   return        : FLS_CDD_RSP_NG_SUSPEND  (Unauthorized suspend state)
   Note          : -
*******************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Cdd_Resume( void )
{
    Fls_Cdd_JobResultType  st_ret;             /* return value */

    st_ret = FLS_CDD_RSP_NG_SUSPEND;      /* unauthorized suspend state */

    return(st_ret);
} /* Fls_Cdd_Resume */

/*******************************************************************************
   Function      : Suspend Status Acquisition Request
   Description   : This API notifies the suspend state.
   param         : -
   return        : FLS_CDD_RSP_NO_SUSPEND   (Non-suspended state)
   Note          : -
*******************************************************************************/
FUNC( Fls_Cdd_SuspendStatusType, FLS_CODE ) 
Fls_Cdd_GetSuspendStatus(void)
{
    return(FLS_CDD_RSP_NO_SUSPEND);

} /* Fls_GetStatus */
#endif /* FLS_CDD_SUSPEND_SYSTEM_API == STD_ON */

#if ( FLS_CDD_AUTH_DFID_API == STD_ON )
/*******************************************************************************
   Function      : DataFlashID Authentication Request
   Description   : This API DataFlashID Authentication is performed.
   param         : -
   return        : FLS_CDD_RSP_OK               (Normal end (Complex Driver))
                 : FLS_CDD_RSP_NG_BUSY          (Execution during the busy state (Complex Driver))
                 : FLS_CDD_RSP_NG_PARAM         (Parameter error (Complex Driver))
                 : FLS_CDD_RSP_NG_AUTHID        (ID Authentication failure (Complex Driver))
   Note          : -
*******************************************************************************/
FUNC( Fls_Cdd_JobResultType, FLS_CODE ) 
Fls_Cdd_AuthDFID(
    P2CONST( Fls_Cdd_DataFlashIDType, AUTOMATIC, FLS_APPL_CONST ) IDValue
)
{
    Fls_Cdd_JobResultType  st_ret;
    Fls_FlagType    st_flag;

    st_ret = FLS_CDD_RSP_NG_BUSY;

    if( MEMIF_IDLE == Fls_Str.stiStat_enu )
    {
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        /* NULL check of the Data Flash ID */
        if( NULL_PTR != IDValue )
        {
#endif /* FLS_CDD_COMPARE_API == STD_ON */
            st_flag = Fls_Drv_VerifyID(IDValue);
            if( FLS_DRV_U1_TRUE == st_flag )
            {
                st_ret = FLS_CDD_RSP_OK;
            }
            else
            {
                st_ret = FLS_CDD_RSP_NG_AUTHID;
            }
#if ( FLS_DEV_ERROR_DETECT == STD_ON )
        }
        else
        {
            st_ret = FLS_CDD_RSP_NG_PARAM;  /* Processing result NG */
        }
#endif /* FLS_CDD_COMPARE_API == STD_ON */
    }

    return st_ret;

}
#endif /* FLS_CDD_AUTH_DFID_API == STD_ON */

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
