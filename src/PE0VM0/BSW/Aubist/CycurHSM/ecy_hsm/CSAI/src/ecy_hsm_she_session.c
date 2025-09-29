/**
 * @file
 ***********************************************************************************************
 * @brief SHE session implementation file
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_sessions_params.h"
#include "ecy_hsm_she.h"
#include "ecy_hsm_she_host_private.h"
#include "ecy_hsm_ipcdrv.h"
#include "ecy_hsm_proxy.h"

/* Worst case FEE reorg time (email from Adrian Funk, CDG-SMT/ESE1, 19/1/2017). With current CycurHSM structure this
   can potentially delay close session */
#define CLOSE_SESSION_TIMEOUT_MSEC      (uint16)5000u       /* 5 seconds */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *** static function prototypes *************************************************************************************/

#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
/**
 * This static function performs the hot swap.
 *
 * @note The function uses global variable pSHE_SessionStatus_backup. The caller function has to ensure that this is not
 *       a null pointer.
 *
 * @return                          ERC_NO_ERROR or error code
 */
static SHE_ErrorCodeT SHE_PerformHotSwap(void);
#endif /* #if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL== ENABLED) */

/***************************** STATIC FUNCTIONS ***********************************************************************/

#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
static SHE_ErrorCodeT SHE_PerformHotSwap(void)
{
    SHE_ErrorCodeT errorCode = ERC_GENERAL_ERROR;

    register HSM_PortStatusT sessionStatus_backup = *pSHE_SessionStatus_backup;

    if((HSM_STATUS_PENDING == sessionStatus_backup) || (HSM_STATUS_PROCESSING == sessionStatus_backup))
    {
        /* Old Session also Busy, so return error code and dont perform the hot swap */
        errorCode = ERC_BUSY;
    }
    else if (ecy_hsm_CSAI_SUCCESS != ecy_HSM_CancelOp(SHE_Session))
    {
        /* Cancel was not successful, so return error code and dont perform the hot swap */
    }
    else if(ecy_hsm_CSAI_SUCCESS != ecy_HSM_SessionHotSwap(&pSHE_SessionStatus,
                                                           &SHE_Session,
                                                           &pSHE_SessionStatus_backup,
                                                           &SHE_Session_backup))
    {
        /* Hot swap was not successful, so return error code */
    }
    else
    {
        /* Acknowledge the new SHE session in any case, don't care about the return value so discard it */
        (void)SHE_Sync();

        /* Hot swap was successful */
        errorCode = ERC_NO_ERROR;
    }

    return errorCode;
}
#endif /* #if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL== ENABLED) */

/***************************** PUBLIC FUNCTIONS ***********************************************************************/

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_Init(void)
{
    SHE_ErrorCodeT errorCode = ERC_GENERAL_ERROR;

    if(     ( SHE_Session < CYCURHSM_SC_MAX_HOST_HSM_SESSIONS )
#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
        ||  ( SHE_Session_backup < CYCURHSM_SC_MAX_HOST_HSM_SESSIONS )
#endif
      )
    {
        errorCode = ERC_SEQUENCE_ERROR;
    }
    else if( (ecy_hsm_CSAI_SUCCESS == ecy_hsm_Csai_OpenSession(ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING, ecy_hsm_CSAI_PRIO_MEDIUM, &SHE_Session)) )
    {
        if( ecy_hsm_CSAI_SUCCESS == ecy_HSM_GetSessionStatusPointer(&pSHE_SessionStatus, SHE_Session))
        {
            errorCode = ERC_NO_ERROR;
        }
    }
    else
    {
        /* nothing to do */
    }

#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
    /* Open a 2nd SHE session for the hot swap in SHE_CMD_CANCEL */
    if (errorCode == ERC_NO_ERROR)
    {
        errorCode = ERC_GENERAL_ERROR;

        if( (ecy_hsm_CSAI_SUCCESS == ecy_hsm_Csai_OpenSession(ecy_hsm_CSAI_SESSION_MODE_NON_BLOCKING, ecy_hsm_CSAI_PRIO_MEDIUM, &SHE_Session_backup)) )
        {
            if( ecy_hsm_CSAI_SUCCESS == ecy_HSM_GetSessionStatusPointer(&pSHE_SessionStatus_backup, SHE_Session_backup))
            {
                 errorCode = ERC_NO_ERROR;
            }
        }

        if (errorCode != ERC_NO_ERROR)
        {
            /* Close the main SHE Session, if opening of the second session failed */
            ecy_hsm_Csai_JobHandleT hJob;
            if(ecy_hsm_CSAI_SUCCESS == ecy_hsm_Csai_CloseSessionAsync(SHE_Session, &hJob))
            {
                /* Wait for the operation to complete or timeout */
                /* No need to check the return value, an error will definitely be returned */
                (void) ecy_HSM_WaitForOpToComplete(hJob, CLOSE_SESSION_TIMEOUT_MSEC);
            }

            SHE_Session                 = ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE;
            pSHE_SessionStatus          = NULL_PTR;
        }
    }
#endif

    return(errorCode);
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_DeInit(void)
{
    ecy_hsm_Csai_JobHandleT hJob;
    SHE_ErrorCodeT errorCode = ERC_GENERAL_ERROR;

    if(ecy_hsm_CSAI_SUCCESS == ecy_hsm_Csai_CloseSessionAsync(SHE_Session, &hJob))
    {
        /* Wait for the operation to complete or timeout */
        if(ecy_hsm_CSAI_SUCCESS == ecy_HSM_WaitForOpToComplete(hJob, CLOSE_SESSION_TIMEOUT_MSEC))
        {
            errorCode = ERC_NO_ERROR;
        }
    }

    SHE_Session                 = ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE;
    pSHE_SessionStatus          = NULL_PTR;

#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
    /* Close a 2nd SHE session for the hot swap in SHE_CMD_CANCEL */
    if(ecy_hsm_CSAI_SUCCESS == ecy_hsm_Csai_CloseSessionAsync(SHE_Session_backup, &hJob))
    {
        /* Wait for the operation to complete or timeout */
        if(ecy_hsm_CSAI_SUCCESS != ecy_HSM_WaitForOpToComplete(hJob, CLOSE_SESSION_TIMEOUT_MSEC))
        {
            errorCode = ERC_GENERAL_ERROR;
        }
    }
    else
    {
        errorCode = ERC_GENERAL_ERROR;
    }

    SHE_Session_backup          = ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE;
    pSHE_SessionStatus_backup   = NULL_PTR;
    SHE_Priority                = ecy_hsm_CSAI_PRIO_LOW;
#endif

    return(errorCode);
}

/* Note that this function has to execute in under 500ns, which it only just manages on the Aurix target    */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_GetStatus(uint8* pStatus)
{
    SHE_ErrorCodeT retval;
    if((NULL_PTR == pSHE_SessionStatus) || (NULL_PTR == pStatus))
    {
        retval = ERC_GENERAL_ERROR;
    }
    else
    {
        register HSM_PortStatusT status = *pSHE_SessionStatus;

        register uint8 s = (uint8)(ecy_hsm_IpcDrv_GetHsmStatus() & HSM2HTS_SHE_MASK);

        /* Merge in the busy bit from the session that is being used for SHE */
        if((HSM_STATUS_PENDING == status) || (HSM_STATUS_PROCESSING == status))
        {
            *pStatus = s | SHE_STATUS_BUSY;
        }
        else
        {
            *pStatus = s;
        }
        retval = ERC_NO_ERROR;
    }

    return(retval);
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_SHE */
/* PRQA S 1505 1 */ /* Justification: This function is part of the public API and can therefore not be declared static. */
SHE_ErrorCodeT SHE_Sync(void)
{
    register HSM_PortStatusT status;
    SHE_ErrorCodeT retval;

    if(NULL_PTR == pSHE_SessionStatus)
    {
            retval = ERC_GENERAL_ERROR;
    }
    else
    {

        status = *pSHE_SessionStatus;

        /* Use *pSHE_SessionStatus to speed up the initial check    */
        if((HSM_STATUS_PENDING == status) || (HSM_STATUS_PROCESSING == status))
        {
            retval = ERC_BUSY;
        }
        else
        {
            ecy_hsm_Csai_ErrorT csaiErrorCode = ecy_HSM_GetSessionStatus(SHE_Session);

            if(ecy_hsm_CSAI_FC_BUSY == csaiErrorCode)
            {
                retval = ERC_BUSY;
            }
            else if(ecy_hsm_CSAI_ERR_MEM_PROTECTION == csaiErrorCode)
            {
                retval = ERC_MEMORY_FAILURE;
            }
            else if(ecy_hsm_CSAI_ERR_OP_REQUEST_FAILED == csaiErrorCode)
            {
                retval = ERC_GENERAL_ERROR;
            }
            else
            {
                /* PRQA S 4342, 4394 3 */ /* Deviation: rule_10.8_4394_she */ /* Justification: Since csaiErrorCode is uint32,
                * no adverse behaviour expected in type cast. Casted values are expected to fall within enumeration constants,
                * otherwise clear & graceful SHE test failures would be expected. */
                retval = (SHE_ErrorCodeT) (ecy_hsm_CSAI_ERR_CODE_MASK & csaiErrorCode);
            }
        }
    }
    return(retval);
/* PRQA S 6009 1 *//* Justification: Refactoring due to HIS metric LEVEL makes the function less readable. */
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_GetID( const uint8 challenge[SHE_AES_BLOCK_SIZE_BYTES],
                          uint8 id[15],
                          uint8 *pStatus,
                          uint8 mac[SHE_AES_BLOCK_SIZE_BYTES] )
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 6 */ /* Deviation: rule_2.2_2983 */
    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_GetIDParam.csaiErrors = FALSE;
    paramBlock.SHE_GetIDParam.challenge  = challenge;
    paramBlock.SHE_GetIDParam.id         = id;
    paramBlock.SHE_GetIDParam.pStatus    = pStatus;
    paramBlock.SHE_GetIDParam.mac        = mac;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_GET_ID, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_SecureBoot( uint32 size, const uint8* data )
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 4 */ /* Deviation: rule_2.2_2983 */
    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_SecureBootParam.csaiErrors = FALSE;
    paramBlock.SHE_SecureBootParam.size       = size;
    paramBlock.SHE_SecureBootParam.data       = data;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_SECURE_BOOT, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_SecureBootFailure( void )
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;
    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_SecureBootControlParam.csaiErrors = FALSE;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_SECURE_BOOT_FAILURE, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_SecureBootOk(void)
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;
    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_SecureBootControlParam.csaiErrors = FALSE;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_SECURE_BOOT_OK, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_Cancel(void)
{
    SHE_ErrorCodeT errorCode = ERC_NO_ERROR;

#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == DISABLED)
    if(ecy_hsm_CSAI_SUCCESS == ecy_HSM_CancelOp(SHE_Session))
    {
        errorCode = ERC_NO_ERROR;
    }
    else
    {
        errorCode = ERC_GENERAL_ERROR;
    }
#else
    if ((pSHE_SessionStatus == NULL_PTR) || (pSHE_SessionStatus_backup == NULL_PTR) )
    {
        errorCode = ERC_GENERAL_ERROR;
    }
    else
    {
        register HSM_PortStatusT sessionStatus = *pSHE_SessionStatus;
        if(HSM_STATUS_IDLE == sessionStatus)
        {
            /* Session is in State Idle: Nothing to do */
        }
        else if(HSM_STATUS_COMPLETE == sessionStatus)
        {
            /* Session is in State Complete: Acknowledge the old error message */
            /* Just acknowledge the SHE session, don't care about the return value so discard it */
            (void)SHE_Sync();
        }
        else if((ecy_hsm_CSAI_PRIO_MEDIUM) == SHE_Priority)
        {
            /* The prio is checked for the remaining session states */
            errorCode = ERC_BUSY;
        }
        else
        {
            /* State Current Session Busy: Try to Hot Swap */
            errorCode = SHE_PerformHotSwap();
        }
    }

#endif
    return(errorCode);
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_CmdDebugChallenge( uint8 challenge[SHE_AES_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 3 */ /* Deviation: rule_2.2_2983 */
    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_DebugChallengeParam.csaiErrors = FALSE;
    paramBlock.SHE_DebugChallengeParam.challenge  = challenge;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_DEBUG_CHALLENGE, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_SHE */
SHE_ErrorCodeT SHE_CmdDebugAuthorize(const uint8 authorization[SHE_AES_BLOCK_SIZE_BYTES])
{
    /* PRQA S 0759 1 */ /* <Deviation: defintion of union is appropriate here */
    HSM_SheParamT paramBlock;

    /* PRQA S 2983 3 */ /* Deviation: rule_2.2_2983 */
    /* PRQA S 4404 1 */ /* <Deviation: rule_10.3_4404_10.5_4304_boolean */
    paramBlock.SHE_DebugAuthorizeParam.csaiErrors         = FALSE;
    paramBlock.SHE_DebugAuthorizeParam.debugAuthorization = authorization;

    /* HSM Applet Request */
    return SHE_LoadApplet( APPLET_SHE_FUNC_DEBUG_AUTHORIZE, sizeof(paramBlock), &paramBlock );
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
