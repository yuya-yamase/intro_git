/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : CTL                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_CTL_C_MAJOR                          (1U)
#define RIM_CTL_C_MINOR                          (3U)
#define RIM_CTL_C_PATCH                          (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "rim_ctl_cfg_private.h"

#include "rim_func_private.h"
#include "rim_initbackupram.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_CTL_C_MAJOR != RIM_CTL_H_MAJOR) || \
     (RIM_CTL_C_MINOR != RIM_CTL_H_MINOR) || \
     (RIM_CTL_C_PATCH != RIM_CTL_H_PATCH))
#error "rim_ctl.c and rim_ctl.h : source and header files are inconsistent!"
#endif

#if ((RIM_CTL_C_MAJOR != RIM_CTL_CFG_H_MAJOR) || \
     (RIM_CTL_C_MINOR != RIM_CTL_CFG_H_MINOR) || \
     (RIM_CTL_C_PATCH != RIM_CTL_CFG_H_PATCH))
#error "rim_ctl.c and rim_ctl_cfg.h : source and header files are inconsistent!"
#endif

#if ((RIM_CTL_C_MAJOR != RIM_CTL_CFG_PRIVATE_H_MAJOR) || \
     (RIM_CTL_C_MINOR != RIM_CTL_CFG_PRIVATE_H_MINOR) || \
     (RIM_CTL_C_PATCH != RIM_CTL_CFG_PRIVATE_H_PATCH))
#error "rim_ctl.c and rim_ctl_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_Rim_ReadU4Main(const U2 u2_a_ID, U4 *u4_ap_data, const U2 u2_a_RIMSIZE);
static U1   u1_s_Rim_WriteU4Main(const U2 u2_a_ID, const U4 u4_a_DATA, const U2 u2_a_RIMSIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_Rim_BonInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Rim_BonInit(void)
{
    vd_g_Rim_InitBackupram();
    vd_d_Rim_CfgBonInit();
}

/*===================================================================================================================================*/
/*  void    vd_g_Rim_WriteU1(const U2 u2_a_ID, const U1 u1_a_DATA)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u1_a_DATA : Write Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Rim_WriteU1(const U2 u2_a_ID, const U1 u1_a_DATA)
{
    (void)u1_s_Rim_WriteU4Main(u2_a_ID, (U4)u1_a_DATA, (U2)RIMID_RIMSIZE_1BYTE);
}

/*===================================================================================================================================*/
/*  void    vd_g_Rim_WriteU2(const U2 u2_a_ID, const U2 u2_a_DATA)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u2_a_DATA : Write Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Rim_WriteU2(const U2 u2_a_ID, const U2 u2_a_DATA)
{
    (void)u1_s_Rim_WriteU4Main(u2_a_ID, (U4)u2_a_DATA, (U2)RIMID_RIMSIZE_2BYTE);
}

/*===================================================================================================================================*/
/*  void    vd_g_Rim_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u4_a_DATA : Write Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Rim_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)
{
    (void)u1_s_Rim_WriteU4Main(u2_a_ID, u4_a_DATA, (U2)RIMID_RIMSIZE_4BYTE);
}

/*===================================================================================================================================*/
/*  void    vd_g_Rim_WriteOther(const U2 u2_a_ID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> u2_a_SIZE   : Size                                                                                           */
/*                  --> *u1_ap_DATA : Write Data Pointer                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Rim_WriteOther(const U2 u2_a_ID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA)
{
    (void)u1_g_Rim_WriteOtherwithStatus(u2_a_ID, u2_a_SIZE, u1_ap_DATA);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_ReadU1withStatus(const U2 u2_a_ID, U1 *u1_ap_data)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_ReadU1withStatus(const U2 u2_a_ID, U1 *u1_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u1_ap_data == vdp_PTR_NA){
        /* PRM:DATA Error(Data Pointer Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_DATA_P;
    }
    else{
        u1_t_ret = u1_s_Rim_ReadU4Main(u2_a_ID, &u4_t_data, (U2)RIMID_RIMSIZE_1BYTE);
        if((u1_t_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            *u1_ap_data = (U1)u4_t_data;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_ReadU2withStatus(const U2 u2_a_ID, U2 *u2_ap_data)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> *u2_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_ReadU2withStatus(const U2 u2_a_ID, U2 *u2_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u2_ap_data == vdp_PTR_NA){
        /* PRM:DATA Error(Data Pointer Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_DATA_P;
    }
    else{
        u1_t_ret = u1_s_Rim_ReadU4Main(u2_a_ID, &u4_t_data, (U2)RIMID_RIMSIZE_2BYTE);
        if((u1_t_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            *u2_ap_data = (U2)u4_t_data;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_ReadU4withStatus(const U2 u2_a_ID, U4 *u4_ap_data)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> *u4_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_ReadU4withStatus(const U2 u2_a_ID, U4 *u4_ap_data)
{
    U1  u1_t_ret;
    U4  u4_t_data;

    if(u4_ap_data == vdp_PTR_NA){
        /* PRM:DATA Error(Data Pointer Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_DATA_P;
    }
    else{
        u1_t_ret = u1_s_Rim_ReadU4Main(u2_a_ID, &u4_t_data, (U2)RIMID_RIMSIZE_4BYTE);
        if((u1_t_ret & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            *u4_ap_data = u4_t_data;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_ReadOtherwithStatus(const U2 u2_a_ID, const U2 u2_a_SIZE, U1 *u1_ap_data)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> u2_a_SIZE   : Size                                                                                           */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_ReadOtherwithStatus(const U2 u2_a_ID, const U2 u2_a_SIZE, U1 *u1_ap_data)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U1  u1_t_moduleid;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u1_t_moduleid = u1_g_RIM_GET_MODULE_ID(u2_a_ID);
    if(u2_t_rimsize != (U2)RIMID_RIMSIZE_OTHER){
        /* PRM:RIMID Error(SIZE Error) */
    }
#if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U))
    else if(u1_t_moduleid >= (U1)RIM_MODULE_ID_NUM){
        /* PRM:RIMID Error(MODULE ID Error) */
    }
#endif  /* #if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U)) */
    else if(fp_gp_u1_RIM_READ_OTHER[u1_t_moduleid] == vdp_PTR_NA){
        /* PRM:RIMID Error(MODULE ID Error) */
    }
    else if(u1_ap_data == vdp_PTR_NA){
        /* PRM:DATA Error(Data Pointer Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_DATA_P;
    }
    else{
        u1_t_ret = (fp_gp_u1_RIM_READ_OTHER[u1_t_moduleid])(u2_a_ID, u2_a_SIZE, u1_ap_data);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_WriteU1withStatus(const U2 u2_a_ID, const U1 u1_a_DATA)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u1_a_DATA : Write Data                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_WriteU1withStatus(const U2 u2_a_ID, const U1 u1_a_DATA)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_Rim_WriteU4Main(u2_a_ID, (U4)u1_a_DATA, (U2)RIMID_RIMSIZE_1BYTE);

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_WriteU2withStatus(const U2 u2_a_ID, const U2 u2_a_DATA)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u2_a_DATA : Write Data                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_WriteU2withStatus(const U2 u2_a_ID, const U2 u2_a_DATA)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_Rim_WriteU4Main(u2_a_ID, (U4)u2_a_DATA, (U2)RIMID_RIMSIZE_2BYTE);

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_WriteU4withStatus(const U2 u2_a_ID, const U4 u4_a_DATA)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u4_a_DATA : Write Data                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_WriteU4withStatus(const U2 u2_a_ID, const U4 u4_a_DATA)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_Rim_WriteU4Main(u2_a_ID, u4_a_DATA, (U2)RIMID_RIMSIZE_4BYTE);

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Rim_WriteOtherwithStatus(const U2 u2_a_ID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> u2_a_SIZE   : Size                                                                                           */
/*                  --> *u1_ap_DATA : Write Data Pointer                                                                             */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Rim_WriteOtherwithStatus(const U2 u2_a_ID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U1  u1_t_moduleid;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u1_t_moduleid = u1_g_RIM_GET_MODULE_ID(u2_a_ID);
    if(u2_t_rimsize != (U2)RIMID_RIMSIZE_OTHER){
        /* PRM:RIMID Error(SIZE Error) */
    }
#if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U))
    else if(u1_t_moduleid >= (U1)RIM_MODULE_ID_NUM){
        /* PRM:RIMID Error(MODULE ID Error) */
    }
#endif  /* #if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U)) */
    else if(fp_gp_u1_RIM_WRITE_OTHER[u1_t_moduleid] == vdp_PTR_NA){
        /* PRM:RIMID Error(MODULE ID Error) */
    }
    else if(u1_ap_DATA == vdp_PTR_NA){
        /* PRM:DATA Error(Data Pointer Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_DATA_P;
    }
    else{
        u1_t_ret = (fp_gp_u1_RIM_WRITE_OTHER[u1_t_moduleid])(u2_a_ID, u2_a_SIZE, u1_ap_DATA);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Static Functions                                                                                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  U1      u1_s_Rim_ReadU4Main(const U2 u2_a_ID, U4 *u4_ap_data, const U2 u2_a_RIMSIZE)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID      : RimId                                                                                         */
/*                  --> *u4_ap_data  : Read Data Pointer                                                                             */
/*                  --> u2_a_RIMSIZE : RimSize                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1       u1_s_Rim_ReadU4Main(const U2 u2_a_ID, U4 *u4_ap_data, const U2 u2_a_RIMSIZE)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U1  u1_t_moduleid;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u1_t_moduleid = u1_g_RIM_GET_MODULE_ID(u2_a_ID);
    if(u2_t_rimsize != u2_a_RIMSIZE){
        /* PRM:RIMID Error(SIZE Error) */
        /* u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID; */
    }
#if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U))
    else if(u1_t_moduleid >= (U1)RIM_MODULE_ID_NUM){
        /* PRM:RIMID Error(MODULE ID Error) */
        /* u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID; */
    }
#endif  /* #if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U)) */
    else if(fp_gp_u1_RIM_READ_U4[u1_t_moduleid] == vdp_PTR_NA){
        /* PRM:RIMID Error(MODULE ID Error) */
        /* u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID; */
    }
    else{
        u1_t_ret = (fp_gp_u1_RIM_READ_U4[u1_t_moduleid])(u2_a_ID, u4_ap_data);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1  u1_s_Rim_WriteU4Main(const U2 u2_a_ID, const U4 u4_a_DATA, const U2 u2_a_RIMSIZE)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID      : RimId                                                                                         */
/*                  --> u4_a_DATA    : Write Data                                                                                    */
/*                  --> u2_a_RIMSIZE : RimSize                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Rim_WriteU4Main(const U2 u2_a_ID, const U4 u4_a_DATA, const U2 u2_a_RIMSIZE)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U1  u1_t_moduleid;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u1_t_moduleid = u1_g_RIM_GET_MODULE_ID(u2_a_ID);
    if(u2_t_rimsize != u2_a_RIMSIZE){
        /* PRM:RIMID Error(SIZE Error) */
        /* u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID; */
    }
#if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U))
    else if(u1_t_moduleid >= (U1)RIM_MODULE_ID_NUM){
        /* PRM:RIMID Error(MODULE ID Error) */
        /* u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID; */
    }
#endif  /* #if (RIM_MODULE_ID_NUM != ((RIMID_MODULE_ID_MASK >> RIMID_MODULE_ID_SHIFT) + 1U)) */
    else if(fp_gp_u1_RIM_WRITE_U4[u1_t_moduleid] == vdp_PTR_NA){
        /* PRM:RIMID Error(MODULE ID Error) */
        /* u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID; */
    }
    else{
        u1_t_ret = (fp_gp_u1_RIM_WRITE_U4[u1_t_moduleid])(u2_a_ID, u4_a_DATA);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           11/18/2014  KM      New.                                                                                         */
/*  1.1.0           03/30/2015  MH      Fixed QAC issue.                                                                             */
/*                                      Update version check                                                                         */
/*  1.1.1           07/14/2015  HK      Comment correction                                                                           */
/*                                      Revise the cast for NULL of the condition judgment sentence                                  */
/*  1.2.0           07/30/2015  HK      Change the notice condition of "vd_d_Rim_ReadErrorHook"                                      */
/*  1.2.1           09/07/2015  HK      Comment correction                                                                           */
/*                                      Revise the cast for NULL of the condition judgment sentence                                  */
/*  1.2.2           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.2.3           01/06/2016  HK      Delete RIM_READ_ERROR_HOOK_USE                                                               */
/*  1.2.4           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.2.5           03/20/2018  HK      Fixed AIP3GBSW-266 issue.                                                                    */
/*  1.2.6            9/14/2021  TN      NULL -> vdp_PTR_NA.                                                                          */
/*  1.2.6            9/15/2021  TN      vd_d_Rim_vd_FptrCall(fp_gp_vd_RIM_BONINIT) -> vd_d_Rim_CfgBonInit                            */
/*                                      vd_g_Rim_WkupInit                          -> vd_d_Rim_CfgWkupInit                           */
/*                                      vd_g_Rim_PostInit                          -> vd_d_Rim_CfgPostInit                           */
/*                                      vd_g_Rim_DeInit                            -> vd_d_Rim_CfgDeInit                             */
/*                                      vd_g_Rim_Task                              -> vd_d_Rim_CfgTask                               */
/*                                      u1_g_Rim_WkupRAMCheck                      -> u1_d_Rim_CfgWkupRAMCheck                       */
/*                                      u1_g_Rim_TmrWkupRAMCheck                   -> u1_d_Rim_CfgTmrWkupRAMCheck                    */
/*  1.3.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
