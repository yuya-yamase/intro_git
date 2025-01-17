/* BswM_RequestMode_Mmicon_Security_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestMode/Mmicon/Security/CODE                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Gdn.h>


#if (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    BswM_ModeType BswMMode;
    gdn_uint8 DcmValue;
} BswM_SecLevelMatrixType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_Mmicon_Security
(
    VAR(gdn_uint8, AUTOMATIC) DcmSecurity
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_CST
#include <BswM_MemMap.h>

static CONST(AB_83_ConstV BswM_SecLevelMatrixType, BSWM_CONST) BswM_SecLevelMatrixTbl[] = {
     { BSWM_MODE_SECURITY_UNLOCK_LV1,   GDN_DCM_SECURITY_UNLOCK_LV1 }
    ,{ BSWM_MODE_SECURITY_UNLOCK_LV2,   GDN_DCM_SECURITY_UNLOCK_LV2 }
    ,{ BSWM_MODE_SECURITY_UNLOCK_LV3,   GDN_DCM_SECURITY_UNLOCK_LV3 }
    ,{ BSWM_MODE_SECURITY_UNLOCK_LV4,   GDN_DCM_SECURITY_UNLOCK_LV4 }
    ,{ BSWM_MODE_SECURITY_UNLOCK_LV5,   GDN_DCM_SECURITY_UNLOCK_LV5 }
    ,{ BSWM_MODE_SECURITY_UNLOCK_LV6,   GDN_DCM_SECURITY_UNLOCK_LV6 }
    ,{ BSWM_MODE_SECURITY_UNLOCK_LV7,   GDN_DCM_SECURITY_UNLOCK_LV7 }
    ,{ BSWM_MODE_SECURITY_UNLOCK_LV8,   GDN_DCM_SECURITY_UNLOCK_LV8 }
    ,{ BSWM_MODE_SECURITY_LOCK,         GDN_DCM_SECURITY_LOCK       }
};
static CONST(AB_83_ConstV uint8, BSWM_CONST) BswM_SecLevelMatrixNum = (sizeof(BswM_SecLevelMatrixTbl) / sizeof(BswM_SecLevelMatrixTbl[0]));

#define BSWM_STOP_SEC_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_RequestMode_Mmicon_Security                           */
/* Description   | Security mode request                                      */
/*               | (Synchronous processing with the main micon)               */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV1                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV2                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV3                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV4                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV5                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV6                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV7                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV8                        */
/*               |       BSWM_MODE_SECURITY_LOCK                              */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_SUB    */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Mmicon_Security
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    VAR(uint8, AUTOMATIC) ErrFlg;
    VAR(uint8, AUTOMATIC) MatrixNum;
    VAR(uint8, AUTOMATIC) i;
    VAR(gdn_uint8, AUTOMATIC) DcmSecurity;

    ErrFlg = STD_ON;
    MatrixNum = BswM_SecLevelMatrixNum;

    for( i = 0U; i < MatrixNum; i++ )
    {
        if( Mode == BswM_SecLevelMatrixTbl[i].BswMMode )
        {
            DcmSecurity = BswM_SecLevelMatrixTbl[i].DcmValue;
            ErrFlg = STD_OFF;
            break;
        }
    }

    if( ErrFlg == (uint8)STD_OFF )
    {
        BswM_Act_Mmicon_Security(DcmSecurity);
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQ_MMICON_SECURITY, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_Mmicon_Security                                   */
/* Description   | Action of the security mode control                        */
/*               | (Synchronous processing with the main micon)               */
/* Preconditions |                                                            */
/* Parameters    | [IN] DcmSecurity : Security to notify Dcm                  */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV1                          */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV2                          */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV3                          */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV4                          */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV5                          */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV6                          */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV7                          */
/*               |       GDN_DCM_SECURITY_UNLOCK_LV8                          */
/*               |       GDN_DCM_SECURITY_LOCK                                */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_SUB    */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_Mmicon_Security
(
    VAR(gdn_uint8, AUTOMATIC) DcmSecurity
)
{
    Gdn_Dcm_NotifyChangeSecurity(DcmSecurity);

    return;
}

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>

#endif  /* (REPROG_CFG_SUBMICON_USE_SUB == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2020/03/10 :Update                                rel.AUBASS */
/*  v3.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

