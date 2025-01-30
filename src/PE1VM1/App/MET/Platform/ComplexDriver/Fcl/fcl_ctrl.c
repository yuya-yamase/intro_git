#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/************************************************************************************************************
* File Name     : $Source: fcl_ctrl.c $
* Mod. Revision : $Revision: 1.1 $
* Mod. Date     : $Date: 2019/04/26 09:04:53JST $
* Device(s)     : RV40 Flash based RH850 microcontroller
* Description   : Application sample for usage of Renesas Flash Control Library (FCL)
************************************************************************************************************/

/************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only  intended for use with
* Renesas products. No other uses are authorized. This software is owned by Renesas Electronics
* Corporation and is protected under all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR
* ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the
* availability of this software. By using this software, you agree to the additional terms and conditions
* found by accessing the  following link:
* www.renesas.com/disclaimer
*
* Copyright (C) 2015-2019 Renesas Electronics Corporation. All rights reserved.
************************************************************************************************************/

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292
#endif

/************************************************************************************************************
* MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 0292)
* Reason:       To support automatic insertion of revision, module name etc. by the source
*               revision control system it is necessary to violate the rule, because the
*               system uses non basic characters as placeholders.
* Verification: The placeholders are used in commentaries only. Therefore rule violation cannot
*               influence code compilation.
************************************************************************************************************/


/************************************************************************************************************
Includes   <System Includes> , "Project Includes"
************************************************************************************************************/
#include "r_typedefs.h"
#include "fcl_cfg.h"
#include "r_fcl_types.h"
#include "r_fcl.h"
#include "target.h"
#include "fcl_descriptor.h"
#include "fcl_user.h"
#include "fcl_ctrl.h"

/************************************************************************************************************
Macro definitions
************************************************************************************************************/

/************************************************************************************************************
Typedef definitions
************************************************************************************************************/

/************************************************************************************************************
Exported global variables (to be accessed by other files)
************************************************************************************************************/
uint16_t u2_g_sec_rslt[FCL_CTRL_CFG_IDX_NUMS];

/************************************************************************************************************
Private global variables and functions
************************************************************************************************************/
#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
    #if R_FCL_COMPILER == R_FCL_COMP_GHS
        #pragma ghs section text = ".R_FCL_CODE_USR"
    #elif R_FCL_COMPILER == R_FCL_COMP_IAR
        #pragma location = "R_FCL_CODE_USR"
    #elif R_FCL_COMPILER == R_FCL_COMP_REC
        #ifdef __PIC
            #pragma section pctext "R_FCL_CODE_USR"
        #else
            #pragma section text "R_FCL_CODE_USR"
        #endif
    #endif
#endif
void FCL_Ctrl (uint8_t req)
{
    r_fcl_request_t     myRequest;
#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
    r_fcl_request_t mySecRequest;
#endif

    FCLUser_Open ();

    /* prepare environment */
    myRequest.command_enu = R_FCL_CMD_PREPARE_ENV;
    R_FCL_Execute (&myRequest);

    #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
        while (R_FCL_BUSY == myRequest.status_enu)
        {
            R_FCL_Handler ();
        }
    #endif

    if(FCL_CTRL_CFG_WT == req)
    {
        if(R_FCL_OK == myRequest.status_enu)
        {
            myRequest.command_enu = R_FCL_CMD_SET_READ_PROTECT_FLAG;
            R_FCL_Execute (&myRequest);
            #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
                while (R_FCL_BUSY == myRequest.status_enu)
                {
                    R_FCL_Handler ();
                }
            #endif
        }

        if(R_FCL_OK == myRequest.status_enu)
        {
            myRequest.command_enu = R_FCL_CMD_SET_WRITE_PROTECT_FLAG;
            R_FCL_Execute (&myRequest);
            #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
            while (R_FCL_BUSY == myRequest.status_enu)
            {
                R_FCL_Handler ();
            }
            #endif
        }
    }

    if(R_FCL_OK == myRequest.status_enu)
    {
        myRequest.command_enu = R_FCL_CMD_GET_READ_PROTECT_FLAG;
        myRequest.bufferAdd_u32 = (uint32_t)&u2_g_sec_rslt[FCL_CTRL_CFG_IDX_RD];
        R_FCL_Execute (&myRequest);
        #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
            while (R_FCL_BUSY == myRequest.status_enu)
            {
                R_FCL_Handler ();
            }
        #endif
    }

    if(R_FCL_OK == myRequest.status_enu)
    {
        myRequest.command_enu = R_FCL_CMD_GET_WRITE_PROTECT_FLAG;
        myRequest.bufferAdd_u32 = (uint32_t)&u2_g_sec_rslt[FCL_CTRL_CFG_IDX_WT];
        R_FCL_Execute (&myRequest);
        #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
            while (R_FCL_BUSY == myRequest.status_enu)
            {
                R_FCL_Handler ();
            }
        #endif
    }

    FCLUser_Close ();
} /* FCL_Ctrl */

