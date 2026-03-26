/**
 * @file
 ***********************************************************************************************
 * @brief Applet manager implementation (HOST side)
 * @details Applet manager handles user job requests using applet controls
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#include "ecy_hsm_applet_manager.h"
#include "ecy_hsm_applet_cfg.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_sessions_params.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"
/*
 **********************************************************************************************************************
 * Function implementations
 **********************************************************************************************************************
 */
/* PRQA S 2889 3 */ /* Justification: Functions which have many error checks need to return immediately in case of an error */
/* PRQA S 3673 6 */ /* Justification: Function fits a generic interface, pointer to const not always feasible */
/* PRQA S 0759 3 */ /* Deviation: usage of union is appropriate here */
Applet_ReturnTypeT Applet_Function(Applet_SessionT           hSession,
                                   ecy_hsm_Csai_JobPriorityT priority,
                                   Applet_FunctionT          appFunc,
                                   uint32                    paramBlockSize,
                                   void* const               pParamBlock)
{
    Applet_ReturnTypeT result_st;
    Applet_JobHandleT  hJob = hSession;

    if(hSession >= CYCURHSM_SC_MAX_HOST_HSM_SESSIONS)
    {
        result_st.stJob = HSM_STATUS_COMPLETE;
        result_st.stError = ecy_hsm_CSAI_ERR_INVALID_HANDLE;
        return result_st;
    }

    result_st = Applet_GetOpStatus( hSession );

    /* if there is not a previous error, or if any previous error has already been acknowledged (=> status == IDLE) */
    if ((ecy_hsm_CSAI_SUCCESS == (result_st.stError & ecy_hsm_CSAI_ERR_FLAG_ERROR)) ||
        (HSM_STATUS_IDLE == result_st.stJob))
    {
        // request HSM operation
        /* PRQA S 4342 2 */ /* <Deviation: conversion of uint8 to enum (uint32) does not affect functionality */
        result_st.stError = ecy_HSM_OpRequest_NoJobHandle(hSession, priority, appFunc.HSM_FuncId, paramBlockSize, pParamBlock, &hJob);
    }
    else
    {
        // otherwise mark result as error from previous operation
        result_st.stError |= ecy_hsm_CSAI_ERR_FLAG_PREVIOUS_OP;
    }
    return result_st;
    /* PRQA S 6010 1 */ /* <Deviation: Early returns in case of error handling is accepted */
}

/* PRQA S 1503 2 */ /* Deviation: rule_2.1_1503_Proxy */
/* PRQA S 1505 1 */ /* <Deviation: This function is part of the HSM Applet API and can therefore not be declared static. */
Applet_ReturnTypeT Applet_GetOpStatus( Applet_SessionT  hSession )
{
    /* default return code */
    Applet_ReturnTypeT result_st = { HSM_STATUS_IDLE, ecy_hsm_CSAI_SUCCESS };

    result_st.stError = ecy_HSM_ReadOpStatus(hSession, &result_st.stJob, ecy_hsm_OPT_STAT_IDLE);

    return result_st;

}
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
