/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "STRCtl.h"

#include "ivdsh.h"
#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define STR_VMCOM_WORD_1      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  void    vd_g_Str_Bon_Init(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Str_Bon_Init(void)
{
    U4  u4_t_vmcom_str_mode;                                                     /* VM Communication Send Data "STR Mode" */

    /* VM Communication Send Data "STR Mode" Initialize */
    u4_t_vmcom_str_mode = (U4)STR_VMCOM_STROFF;
    vd_g_Rim_WriteU1((U2)RIMID_U1_IVI_STR_MODE, (U1)u4_t_vmcom_str_mode);
    /* VM Communication : STR Mode Notification */
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_CPREQ_046, &u4_t_vmcom_str_mode, (U2)STR_VMCOM_WORD_1);  /* STR Mode : OFF */
    /* OS Command :STR Status Notification */
    vd_STR_OSCMD_STR_MODE_NOTIF((U1)STR_OSCMD_STROFF);
}

/*===================================================================================================================================*/
/*  void    vd_g_Str_Wkup_Init(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Str_Wkup_Init(void)
{
    U1  u1_t_rim_sts;
    U1  u1_t_rim_readdata;
    U4  u4_t_vmcom_str_mode;                                                     /* VM Communication Send Data "STR Mode" */

    u1_t_rim_readdata = (U1)0U;

    u1_t_rim_sts = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_IVI_STR_MODE, &u1_t_rim_readdata);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u4_t_vmcom_str_mode = (U4)u1_t_rim_readdata;
        /* VM Communication : STR Mode Notification */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_CPREQ_046, &u4_t_vmcom_str_mode, (U2)STR_VMCOM_WORD_1);  /* STR Mode */
        if(u1_t_rim_readdata == (U1)STR_VMCOM_STROFF){                  /* STR Mode : OFF */
            /* OS Command :STR Status Notification */
            vd_STR_OSCMD_STR_MODE_NOTIF((U1)STR_OSCMD_STROFF);
        }
        else{                                                           /* STR Modet : ON */
            /* OS Command :STR Status Notification */
            vd_STR_OSCMD_STR_MODE_NOTIF((U1)STR_OSCMD_STRON);
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_Str_ModeReq(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_strreq  :  STR Sts Suspend(0) / STR Sts Resume(1)                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Str_ModeReq(U1 u1_a_strreq)
{
    U4  u4_t_vmcom_str_mode;                                                     /* VM Communication Send Data "STR Mode" */

    if(u1_a_strreq == (U1)STR_OSCMD_STROFF){                            /* STR Mode Request : OFF */
        u4_t_vmcom_str_mode = (U4)STR_VMCOM_STROFF;
        vd_g_Rim_WriteU1((U2)RIMID_U1_IVI_STR_MODE, (U1)u4_t_vmcom_str_mode);
        /* VM Communication : STR Mode Notification */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_CPREQ_046, &u4_t_vmcom_str_mode, (U2)STR_VMCOM_WORD_1);  /* STR Mode : OFF */
        /* OS Command :STR Status Notification */
        vd_STR_OSCMD_STR_MODE_NOTIF((U1)STR_OSCMD_STROFF);
    }
    else if(u1_a_strreq == (U1)STR_OSCMD_STRON){                        /* STR Mode Request : ON */
        u4_t_vmcom_str_mode = (U4)STR_VMCOM_STRON;
        vd_g_Rim_WriteU1((U2)RIMID_U1_IVI_STR_MODE, (U1)u4_t_vmcom_str_mode);
        /* VM Communication : STR Mode Notification */
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_CPREQ_046, &u4_t_vmcom_str_mode, (U2)STR_VMCOM_WORD_1);  /* STR Mode : ON */
        /* OS Command :STR Status Notification */
        vd_STR_OSCMD_STR_MODE_NOTIF((U1)STR_OSCMD_STRON);
    }
    else{                                                               /* STR Respons : Invalid Value */
        /* Noting */
    }
}
