/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  DID Config                                                                                                                       */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_ROUT_CFG_C_MAJOR             (1U)
#define OXDOCAN_ROUT_CFG_C_MINOR             (0U)
#define OXDOCAN_ROUT_CFG_C_PATCH             (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"
#include "oxdocan_rout_cfg.h"
#include "oxdocan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Application Headers */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ROUT_POS_INFO                     (0U)
#define OXDC_ROUT_POS_DATA                     (1U)

#define OXDC_ROUT_LSB_3RD                      (16U)
#define OXDC_ROUT_LSB_2ND                      (8U)

#define OXDC_ROUT_D000_ANS_NBYTE_MIN           (8U)
#define OXDC_ROUT_D000_RECTYPE_0               (0U)

#define OXDC_ROUT_D000_IDX_DTC_H               (0U)
#define OXDC_ROUT_D000_IDX_DTC_M               (1U)
#define OXDC_ROUT_D000_IDX_DTC_L               (2U)
#define OXDC_ROUT_D000_IDX_MEMSEL              (3U)
#define OXDC_ROUT_D000_IDX_RECTYPE             (4U)
#define OXDC_ROUT_D000_IDX_RID_WIDE_M          (5U)
#define OXDC_ROUT_D000_IDX_RID_WIDE_L          (6U)
#define OXDC_ROUT_D000_IDX_RECNUM              (7U)

#define OXDC_ROUT_D001_TARGET_MAX              (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4     u4_s_oxdc_rout_d000_dtc;
static U1     u1_s_oxdc_rout_d000_memsel;
static U1     u1_s_oxdc_rout_d001_exe_sts;
static U1     u1_s_oxdc_rout_d001_target_idx;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2   u2_sp_OXDC_ROUT_D001_UDM_DEL_LIST[OXDC_ROUT_D001_TARGET_MAX] = {
    (U2)(DEM_DTC_ORIGIN_USERDEFINED_MEMORY | (U2)0x12U),
    (U2)(DEM_DTC_ORIGIN_USERDEFINED_MEMORY | (U2)0x13U)
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoutCfgInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoutCfgInit(void)
{
    u4_s_oxdc_rout_d000_dtc        = (U4)0U;
    u1_s_oxdc_rout_d000_memsel     = (U1)0U;
    u1_s_oxdc_rout_d001_exe_sts    = (U1)OXDC_ROUT_EXE_STS_IDLE;
    u1_s_oxdc_rout_d001_target_idx = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRoutCfgMain(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRoutCfgMain(void)
{
    U1  u1_t_result;

    if(u1_s_oxdc_rout_d001_exe_sts == (U2)OXDC_ROUT_EXE_STS_RUN){
        if(u1_s_oxdc_rout_d001_target_idx < (U1)OXDC_ROUT_D001_TARGET_MAX){
            u1_t_result = Dem_ClearDTC(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_UDS,
                                            u2_sp_OXDC_ROUT_D001_UDM_DEL_LIST[u1_s_oxdc_rout_d001_target_idx]);

            if((u1_t_result == (U1)DEM_CLEAR_PENDING) ||
               (u1_t_result == (U1)DEM_CLEAR_BUSY   )){
                /* Do Nothing */
            }
            else if(u1_t_result == (U1)E_OK){
                u1_s_oxdc_rout_d001_target_idx++;
                if(u1_s_oxdc_rout_d001_target_idx >= (U1)OXDC_ROUT_D001_TARGET_MAX){
                    u1_s_oxdc_rout_d001_exe_sts = (U1)OXDC_ROUT_EXE_STS_FIN;
                    vd_g_oXDoCANAubIfDtcEvmDeAct((uint8)OXDC_DTC_EVM_MSK);
                }
            }
            else{
                u1_s_oxdc_rout_d001_target_idx = (U1)U1_MAX;
                
                u1_s_oxdc_rout_d001_exe_sts = (U1)OXDC_ROUT_EXE_STS_ABORT;
                vd_g_oXDoCANAubIfDtcEvmDeAct((uint8)OXDC_DTC_EVM_MSK);
            }
        }
        else{
            u1_s_oxdc_rout_d001_exe_sts = (U1)OXDC_ROUT_EXE_STS_ABORT;
        }
    }
    else{
        u1_s_oxdc_rout_d001_target_idx = (U1)U1_MAX;
        vd_g_oXDoCANAubIfDtcEvmDeAct((uint8)OXDC_DTC_EVM_MSK);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D100(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D100(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    if(u2_a_ELPSD == (U2)0U){
        vd_g_oXDoCANXidSupInit((U2)0U, &u1_ap_ans[OXDC_ROUT_POS_DATA]);
    }
    u1_ap_ans[OXDC_ROUT_POS_INFO] = (U1)OXDC_ROUT_INFO_02;
    return(u1_g_oXDoCANRgrSupchk(&st_gp_OXDC_ROUT_XID[0], u2_g_OXDC_ROUT_NUM_XID, &u1_ap_ans[OXDC_ROUT_POS_DATA]));
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D1XX(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D1XX(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    if(u2_a_ELPSD == (U2)0U){
        vd_g_oXDoCANRidSupInit(u2_g_oxdc_rout_xid, &u1_ap_ans[OXDC_ROUT_POS_DATA]);
    }
    u1_ap_ans[OXDC_ROUT_POS_INFO] = (U1)OXDC_ROUT_INFO_02;
    return(u1_g_oXDoCANRidSupchk(&st_gp_OXDC_ROUT_XID[0], u2_g_OXDC_ROUT_NUM_XID, &u1_ap_ans[OXDC_ROUT_POS_DATA]));
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutCorchk_D000(const U1 u1_a_SUBF, const U1 * u1_ap_COR)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutCorchk_D000(const U1 u1_a_SUBF, const U1 * u1_ap_COR)
{
    U4  u4_t_dtc;
    U1  u1_t_ret;

    u1_t_ret = (U1)OXDC_SAL_PROC_NR_10;

    if(u1_a_SUBF == (U1)OXDC_ROUT_SUBF_START){
        u4_t_dtc  = (U4)u1_ap_COR[OXDC_ROUT_D000_IDX_DTC_H] << OXDC_ROUT_LSB_3RD;   /* req[0] : DTCMaskRecord High   */
        u4_t_dtc |= (U4)u1_ap_COR[OXDC_ROUT_D000_IDX_DTC_M] << OXDC_ROUT_LSB_2ND;   /* req[1] : DTCMaskRecord Middle */
        u4_t_dtc |= (U4)u1_ap_COR[OXDC_ROUT_D000_IDX_DTC_L];                        /* req[2] : DTCMaskRecord Low    */
        u4_s_oxdc_rout_d000_dtc    = u4_t_dtc;
        u1_s_oxdc_rout_d000_memsel = (U1)u1_ap_COR[OXDC_ROUT_D000_IDX_MEMSEL];      /* req[3] : MemorySelection      */

        u1_t_ret = (U1)OXDC_SAL_PROC_RUN;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D000(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D000(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1* u1_tp_data;
    U2  u2_t_recnum;
    U2  u2_t_dtc_origin;
    U1  u1_t_recnum;
    U1  u1_t_result;
    U1  u1_t_ret;

    u1_t_ret = (U1)OXDC_SAL_PROC_NR_10;

    if(*u2_ap_nbyte >= (U2)OXDC_ROUT_D000_ANS_NBYTE_MIN){

        u1_ap_ans[OXDC_ROUT_POS_INFO] = (U1)OXDC_ROUT_INFO_02;                                      /* ans[0] : routineinfo          */
        u1_tp_data = &u1_ap_ans[OXDC_ROUT_POS_DATA];

        u1_tp_data[OXDC_ROUT_D000_IDX_DTC_H] = (U1)(u4_s_oxdc_rout_d000_dtc >> OXDC_ROUT_LSB_3RD);  /* ans[1] : DTCMaskRecord High   */
        u1_tp_data[OXDC_ROUT_D000_IDX_DTC_M] = (U1)(u4_s_oxdc_rout_d000_dtc >> OXDC_ROUT_LSB_2ND);  /* ans[2] : DTCMaskRecord Middle */
        u1_tp_data[OXDC_ROUT_D000_IDX_DTC_L] = (U1)u4_s_oxdc_rout_d000_dtc;                         /* ans[3] : DTCMaskRecord Low    */
        u1_tp_data[OXDC_ROUT_D000_IDX_MEMSEL]  = u1_s_oxdc_rout_d000_memsel;                        /* ans[4] : MemorySelection      */
        u1_tp_data[OXDC_ROUT_D000_IDX_RECTYPE] = (U1)OXDC_ROUT_D000_RECTYPE_0;        /* ans[5] : UserDefDTCSnapshotRecordNumberType */
        u1_tp_data[OXDC_ROUT_D000_IDX_RID_WIDE_M] = (U1)0U;           /* ans[6] : RIDOfRetrieveWidenedUserDefDTCSnapshotRecord(MSB)  */
        u1_tp_data[OXDC_ROUT_D000_IDX_RID_WIDE_L] = (U1)0U;           /* ans[7] : RIDOfRetrieveWidenedUserDefDTCSnapshotRecord(LSB)  */

        u2_t_recnum = *u2_ap_nbyte - (U2)OXDC_ROUT_D000_ANS_NBYTE_MIN;
        if(u2_t_recnum > (U2)U1_MAX){
            u2_t_recnum = (U2)U1_MAX;
        }
        u1_t_recnum = (U1)u2_t_recnum;
        u2_t_dtc_origin = (U2)DEM_DTC_ORIGIN_USERDEFINED_MEMORY | (U2)u1_s_oxdc_rout_d000_memsel;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
        u1_t_result = Dem_GetUserDefinedMemoryFreezeFrameRecordNumber(u4_s_oxdc_rout_d000_dtc, u2_t_dtc_origin,
                                                                    &u1_tp_data[OXDC_ROUT_D000_IDX_RECNUM], &u1_t_recnum);
#else
       u1_t_result = E_NOT_OK;
#endif
        if(u1_t_result == (U1)E_OK){
            *u2_ap_nbyte = (U2)u1_t_recnum + (U2)OXDC_ROUT_D000_ANS_NBYTE_MIN;
            u1_t_ret = (U1)OXDC_SAL_PROC_FIN;
        }
        else if(u1_t_result == (U1)DEM_E_ACCESS_PROCESSING){
            u1_t_ret = (U1)OXDC_SAL_PROC_RUN;
        }
        else{
            u1_t_ret = (U1)OXDC_SAL_PROC_NR_31;
        }
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutStart_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutStart_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1  u1_t_ret;

    if(u1_s_oxdc_rout_d001_exe_sts == (U1)OXDC_ROUT_EXE_STS_RUN){
        u1_t_ret = (U1)OXDC_SAL_PROC_NR_24;
    }
    else{
        u1_s_oxdc_rout_d001_target_idx = (U1)0U;
        u1_s_oxdc_rout_d001_exe_sts    = (U1)OXDC_ROUT_EXE_STS_RUN;

        vd_g_oXDoCANAubIfDtcEvmAct((uint8)OXDC_DTC_EVM_MSK);

        u1_ap_ans[OXDC_ROUT_POS_INFO] = (U1)OXDC_ROUT_INFO_03;
        u1_t_ret = (U1)OXDC_SAL_PROC_FIN;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRoutRslt_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRoutRslt_D001(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte)
{
    U1  u1_t_ret;

    if(u1_s_oxdc_rout_d001_exe_sts == (U1)OXDC_ROUT_EXE_STS_RUN){
        u1_t_ret = (U1)OXDC_SAL_PROC_NR_21;
    }
    else if(u1_s_oxdc_rout_d001_exe_sts == (U1)OXDC_ROUT_EXE_STS_FIN){
        u1_ap_ans[OXDC_ROUT_POS_INFO] = (U1)OXDC_ROUT_INFO_03;
        u1_ap_ans[OXDC_ROUT_POS_DATA] = (U1)OXDC_ROUT_RESULT_OK;
        u1_t_ret = (U1)OXDC_SAL_PROC_FIN;
    }
    else if(u1_s_oxdc_rout_d001_exe_sts == (U1)OXDC_ROUT_EXE_STS_ABORT){
        u1_ap_ans[OXDC_ROUT_POS_INFO] = (U1)OXDC_ROUT_INFO_03;
        u1_ap_ans[OXDC_ROUT_POS_DATA] = (U1)OXDC_ROUT_RESULT_NG;
        u1_t_ret = (U1)OXDC_SAL_PROC_FIN;
    }
    else{
        u1_t_ret = (U1)OXDC_SAL_PROC_NR_24;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     7/14/2023  ST        New.                                                                                              */
/*  1.0.1     6/19/2024  ToI       oxdocan_rout.c  v1.0.2 -> 1.0.3                                                                   */
/*                                 rename u1_g_oXDoCANRoutStart_XX00 -> u1_g_oXDoCANRoutStart_D1XX                                   */
/*                                                                                                                                   */
/*  * ST = Shohei Takada, DENSO                                                                                                      */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
