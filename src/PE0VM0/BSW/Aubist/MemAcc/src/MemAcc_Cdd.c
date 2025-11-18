/* MemAcc_Cdd.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemAcc.h>
#include <MemAcc_Cdd.h>
#include <MemAcc_Ext.h>
#include "../inc/MemAcc_Mpu_Const.h"
#include "../inc/MemAcc_Api.h"
#include "../inc/MemAcc_JobCtl.h"
#include "../inc/MemAcc_SemCtl.h"
#include "../inc/MemAcc_FlsWrp.h"
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

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

/*****************************************************************************
      Synchronous Function
*****************************************************************************/
#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
/****************************************************************************/
/* Function Name | MemAcc_Cdd_Read - Synchronous function                   */
/* Description   | This function accepts Data Flash Read operation as       */
/*               | synchronous function.                                    */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress       target Flash physical address        */
/*               | destinationDataPtr  destination pointer to store ReadData*/
/*               | length              target data size                     */
/* Return Value  | FLS_CDD_RSP_OK                                           */
/*               | FLS_CDD_RSP_NG_PARAM                                     */
/*               | FLS_CDD_RSP_NG_BUSY                                      */
/*               | FLS_CDD_RSP_NG_READ                                      */
/*               | FLS_CDD_RSP_NG_COMPARE                                   */
/*               | FLS_CDD_RSP_NG_BLANKCHECK                                */
/*               | FLS_CDD_RSP_NG_INTERNAL                                  */
/*               | FLS_CDD_RSP_NG_FATALFAILED                               */
/*               | FLS_CDD_RSP_NG_AUTHID                                    */
/*               | FLS_CDD_RSP_NG_ALLBLANK                                  */
/*               | FLS_CDD_RSP_OK_SUSPENDED                                 */
/*               | FLS_CDD_RSP_NG_USED_HSM                                  */
/*               | FLS_CDD_RSP_NG_SUSPEND                                   */
/*               | FLS_CDD_RSP_NO_SUSPEND                                   */
/*               | FLS_CDD_RSP_SUSPENDING                                   */
/*               | FLS_CDD_RSP_SUSPENDED                                    */
/* Notes         | If MemAcc is not initialized, FLS_CDD_RSP_NG_INTERNAL    */
/*               | is returned.                                             */
/*               | When the data flash access propriety confirmation        */
/*               | result is E_NOT_OK, FLS_CDD_RSP_NG_BUSY is returned.     */
/*               | Otherwise, return the return value from                  */
/*               | MemAcc_FlsWrp_Cdd_Read.                                  */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, MEMACC_CODE ) 
MemAcc_Cdd_Read(
    Fls_AddressType targetAddress,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) destinationDataPtr,
    Fls_LengthType length
)
{
    Fls_Cdd_JobResultType u1_rtn;
    uint8 u1_funcRet;
    
    /* Check data flash access availability */
    u1_funcRet = MemAcc_ExtDfPreExecution();
            
    /* When data flash access is not possible */
    if( (Std_ReturnType)E_OK != u1_funcRet )
    {
        /* Return busy error */
        u1_rtn = FLS_CDD_RSP_NG_BUSY;
    }
    /* When data flash access is possible */
    else
    {
        /* Call read operation - Synchronous function */
        u1_rtn = MemAcc_FlsWrp_Cdd_Read( targetAddress, destinationDataPtr, length );
    }
    
    return ( u1_rtn );
    
} /* MemAcc_Cdd_Read */
#endif /* MEMACC_DEVICE_CYT2Bx */


/****************************************************************************/
/* Function Name | MemAcc_Cdd_BlankCheck - Synchronous function             */
/* Description   | This function accepts Data Flash BlankCheck operation as */
/*               | synchronous function.                                    */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress       target Flash physical address        */
/*               | destinationDataPtr  destination pointer to store ReadData*/
/*               | length              target data size                     */
/* Return Value  | FLS_CDD_RSP_OK                                           */
/*               | FLS_CDD_RSP_NG_PARAM                                     */
/*               | FLS_CDD_RSP_NG_BUSY                                      */
/*               | FLS_CDD_RSP_NG_READ                                      */
/*               | FLS_CDD_RSP_NG_COMPARE                                   */
/*               | FLS_CDD_RSP_NG_BLANKCHECK                                */
/*               | FLS_CDD_RSP_NG_INTERNAL                                  */
/*               | FLS_CDD_RSP_NG_FATALFAILED                               */
/*               | FLS_CDD_RSP_NG_AUTHID                                    */
/*               | FLS_CDD_RSP_NG_ALLBLANK                                  */
/*               | FLS_CDD_RSP_OK_SUSPENDED                                 */
/*               | FLS_CDD_RSP_NG_USED_HSM                                  */
/*               | FLS_CDD_RSP_NG_SUSPEND                                   */
/*               | FLS_CDD_RSP_NO_SUSPEND                                   */
/*               | FLS_CDD_RSP_SUSPENDING                                   */
/*               | FLS_CDD_RSP_SUSPENDED                                    */
/* Notes         | If MemAcc is not initialized, FLS_CDD_RSP_NG_INTERNAL    */ 
/*               | is returned.                                             */
/*               | When the data flash access propriety confirmation        */
/*               | result is E_NOT_OK, FLS_CDD_RSP_NG_BUSY is returned.     */
/*               | Otherwise, return the return value                       */
/*               | from MemAcc_FlsWrp_BlankCheck.                           */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, MEMACC_CODE ) 
MemAcc_Cdd_BlankCheck(
    Fls_AddressType targetAddress,
    Fls_LengthType length
)
{
    Fls_Cdd_JobResultType u1_rtn;
    uint8 u1_funcRet;
    
    /* Check data flash access availability */
    u1_funcRet = MemAcc_ExtDfPreExecution();
            
    /* When data flash access is not possible */
    if( (Std_ReturnType)E_OK != u1_funcRet )
    {
        /* Return busy error */
        u1_rtn = FLS_CDD_RSP_NG_BUSY;
    }
    /* When data flash access is possible */
    else
    {
        /* Call BlankCheck operation - Synchronous function */
        u1_rtn = MemAcc_FlsWrp_BlankCheck( targetAddress, length );
    }
    
    return ( u1_rtn );
    
} /* MemAcc_Cdd_BlankCheck */


#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
/****************************************************************************/
/* Function Name | MemAcc_Cdd_NotBlankCheck - Synchronous function          */
/* Description   | This function accepts Data Flash NotBlankCheck operation */
/*               | as synchronous function.                                 */
/* Preconditions | None                                                     */
/* Parameters    | targetAddress       target Flash physical address        */
/*               | length              target data size                     */
/*               |notBlankAddress      destination pointer to               */
/*               |                     store BlankAddress                   */
/* Return Value  | FLS_CDD_RSP_OK                                           */
/*               | FLS_CDD_RSP_NG_PARAM                                     */
/*               | FLS_CDD_RSP_NG_BUSY                                      */
/*               | FLS_CDD_RSP_NG_READ                                      */
/*               | FLS_CDD_RSP_NG_COMPARE                                   */
/*               | FLS_CDD_RSP_NG_BLANKCHECK                                */
/*               | FLS_CDD_RSP_NG_INTERNAL                                  */
/*               | FLS_CDD_RSP_NG_FATALFAILED                               */
/*               | FLS_CDD_RSP_NG_AUTHID                                    */
/*               | FLS_CDD_RSP_NG_ALLBLANK                                  */
/*               | FLS_CDD_RSP_OK_SUSPENDED                                 */
/*               | FLS_CDD_RSP_NG_USED_HSM                                  */
/*               | FLS_CDD_RSP_NG_SUSPEND                                   */
/*               | FLS_CDD_RSP_NO_SUSPEND                                   */
/*               | FLS_CDD_RSP_SUSPENDING                                   */
/*               | FLS_CDD_RSP_SUSPENDED                                    */
/* Notes         | If MemAcc is not initialized, FLS_CDD_RSP_NG_INTERNAL    */
/*               | is returned.                                             */
/*               | When the data flash access propriety confirmation        */
/*               | result is E_NOT_OK, FLS_CDD_RSP_NG_BUSY is returned.     */
/*               | Otherwise, return the return value                       */
/*               | from MemAcc_FlsWrp_NotBlankCheck.                        */
/****************************************************************************/
FUNC( Fls_Cdd_JobResultType, MEMACC_CODE ) 
MemAcc_Cdd_NotBlankCheck(
    Fls_AddressType targetAddress,
    Fls_LengthType length,
    P2VAR( Fls_AddressType, AUTOMATIC, TYPEDEF ) notBlankAddress
)
{
    Fls_Cdd_JobResultType u1_rtn;
    uint8 u1_funcRet;
    
    /* Check data flash access availability */
    u1_funcRet = MemAcc_ExtDfPreExecution();
            
    /* When data flash access is not possible */
    if( (Std_ReturnType)E_OK != u1_funcRet )
    {
        /* Return busy error */
        u1_rtn = FLS_CDD_RSP_NG_BUSY;
    }
    /* When data flash access is possible */
    else
    {
        /* Call  NotBlankCheck operation - Synchronous function */
        u1_rtn = MemAcc_FlsWrp_NotBlankCheck( targetAddress, length, notBlankAddress );
    }
    
    return ( u1_rtn );
    
} /* MemAcc_Cdd_NotBlankCheck */
#endif /* MEMACC_DEVICE_CYT2Bx */

/****************************************************************************/
/* Function Name | MemAcc_Cdd_GetLockStatus                                 */
/* Description   | This function returns the public lock held by SemCtl.    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | MEMACC_LOCKST_UNLOCK                                     */
/*               | MEMACC_LOCKST_LOCK                                       */
/* Notes         | Exposes the lock state of address area ID=0 for FEE.     */
/****************************************************************************/
FUNC( uint8, MEMACC_CODE ) 
MemAcc_Cdd_GetLockStatus( void )
{
    uint8 u1_LockStatus;
    uint8 u1_rtn;

    /* Get lock status */
    u1_LockStatus = MemAcc_SemCtl_GetExtLockStatus();

    if ( MEMACC_SEMCTL_ST_EXT_UNLOCK == u1_LockStatus )
    {
        u1_rtn = MEMACC_LOCKST_UNLOCK;
    }
    else
    {
        u1_rtn = MEMACC_LOCKST_LOCK;
    }

    return ( u1_rtn );

} /* MemAcc_Cdd_GetLockStatus */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
