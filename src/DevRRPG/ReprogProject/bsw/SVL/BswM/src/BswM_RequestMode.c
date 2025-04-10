/* BswM_RequestMode_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestMode/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC2_VAR
#include <BswM_MemMap.h>

P2CONST(BswM_ConfigType, BSWM_VAR_CLEARED, BSWM_APPL_CONST) BswM_CfgPtr;
VAR(BswM_CtrlReqModeType, BSWM_VAR_CLEARED) BswM_CtrlReqMode;

#define BSWM_STOP_SEC2_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC2_CST
#include <BswM_MemMap.h>

static CONST(AB_83_ConstV BswM_ReqUserType, BSWM_CONST) BswM_ReqUserTbl[BSWM_MAX_USER_NUM] = {
     { &BswM_RequestMode_Rewrite,           BSWM_USER_SCHM_REWRITE          }
    ,{ &BswM_RequestMode_Session,           BSWM_USER_SCHM_SESSION          }
    ,{ &BswM_RequestMode_Security,          BSWM_USER_SCHM_SECURITY         }
    ,{ &BswM_RequestMode_FlsPrg,            BSWM_USER_SCHM_FLS_PRG          }
    ,{ &BswM_RequestMode_Finish,            BSWM_USER_SCHM_FINISH           }
    ,{ &BswM_RequestMode_UsrReset,          BSWM_USER_RTE_USR_RESET         }
    ,{ &BswM_RequestMode_UsrSleep,          BSWM_USER_RTE_USR_SLEEP         }
    ,{ &BswM_RequestMode_Acc,               BSWM_USER_RTE_ACC               }
    ,{ &BswM_RequestMode_Ig,                BSWM_USER_RTE_IG                }
#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
    ,{ &BswM_RequestMode_EcuReset,          BSWM_USER_SCHM_ECU_RESET        }
    ,{ &BswM_RequestMode_MainErr,           BSWM_USER_SCHM_MAIN_ERR         }
#endif
#if (REPROG_CFG_ETH_USE == STD_ON)
    ,{ &BswM_RequestMode_EthSendRcv,        BSWM_USER_COMM_ETH_SENDRCV      }
#endif
#if (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
    ,{ &BswM_RequestMode_Mmicon_Session,    BSWM_USER_SUBMICONIF_SESSION    }
    ,{ &BswM_RequestMode_Mmicon_Security,   BSWM_USER_SUBMICONIF_SECURITY   }
    ,{ &BswM_RequestMode_EcuReset,          BSWM_USER_SUBMICONIF_ECU_RESET  }
    ,{ &BswM_RequestMode_Mmicon_MainErr,    BSWM_USER_SUBMICONIF_MAIN_ERR   }
    ,{ &BswM_RequestMode_UsrReset,          BSWM_USER_SUBMICONIF_USR_RESET  }
    ,{ &BswM_RequestMode_UsrSleep,          BSWM_USER_SUBMICONIF_USR_SLEEP  }
    ,{ &BswM_RequestMode_Acc,               BSWM_USER_SUBMICONIF_ACC        }
    ,{ &BswM_RequestMode_Ig,                BSWM_USER_SUBMICONIF_IG         }
#endif
};

#define BSWM_STOP_SEC2_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC2_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_RequestMode                                           */
/* Description   | Generic function call to request modes                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] requesting_user : The user that requests the mode     */
/*               | [IN] requested_mode  : The requested mode                  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode
(
    VAR(BswM_UserType, AUTOMATIC) requesting_user,
    VAR(BswM_ModeType, AUTOMATIC) requested_mode
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) ReqUserFlg;

    if( BswM_CfgPtr != NULL_PTR )
    {
        ReqUserFlg = STD_OFF;

        for( i = 0U; i < BSWM_MAX_USER_NUM; i++ )
        {
            if( requesting_user == BswM_ReqUserTbl[i].User )
            {
                ReqUserFlg = STD_ON;

                BswM_ReqUserTbl[i].Func(requested_mode);

                break;
            }
        }

        /* The requesting user was out of range */
        if( ReqUserFlg != (uint8)STD_ON )
        {
            BswM_ReportError(BSWM_API_ID_REQMODE, BSWM_E_REQ_USER_OUT_OF_RANGE);
        }
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE, BSWM_E_NO_INIT);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define BSWM_STOP_SEC2_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

