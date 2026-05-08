/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  NVMC_IF IVI                                                                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_IF_IVI_C_MAJOR                       (1)
#define NVMC_IF_IVI_C_MINOR                       (0)
#define NVMC_IF_IVI_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "nvmc_if_ivi.h"
#include "aip_common.h"
#include "veh_opemd.h"
#include "nvmc_mgr.h"
#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_IF_IVI_C_MAJOR != NVMC_IF_IVI_H_MAJOR) || \
     (NVMC_IF_IVI_C_MINOR != NVMC_IF_IVI_H_MINOR) || \
     (NVMC_IF_IVI_C_PATCH != NVMC_IF_IVI_H_PATCH))
#error "nvmc_if_ivi.c and nvmc_if_ivi.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_IF_IVI_MASK_1BYTE          (0x000000FFU)
#define NVMC_IF_IVI_MASK_2BYTE          (0x0000FF00U)
#define NVMC_IF_IVI_MASK_3BYTE          (0x00FF0000U)
#define NVMC_IF_IVI_MASK_HIBYTE         (0xFFFF0000U)
#define NVMC_IF_IVI_MASK_LOBYTE         (0x0000FFFFU)

#define NVMC_IF_IVI_SHIF_1BYTE          (8U)
#define NVMC_IF_IVI_SHIF_2BYTE          (16U)
#define NVMC_IF_IVI_SHIF_3BYTE          (24U)

#define NVMC_IF_IVI_VM_1WORD            (1U)
#define NVMC_IF_IVI_VM_2WORD            (2U)

#define NVMC_IF_IVI_DRCCNT_NUM          (135U)
#define NVMC_IF_IVI_DRCCNT_MAX          (NVMC_IF_IVI_DRCCNT_NUM - 1U)

#define NVMC_IF_IVI_RD_BUFF             (2U)
#define NVMC_IF_IVI_RD_WCNT             (0U)
#define NVMC_IF_IVI_RD_WP               (1U)
#define NVMC_IF_IVI_RD_ID               (0U)
#define NVMC_IF_IVI_RD_TIME             (1U)

#define NVMC_IF_IVI_ALCNT_UNKNOWN       (U1_MAX)
#define NVMC_IF_IVI_ALCNT_MIN           (0U)
#define NVMC_IF_IVI_ALCNT_MAX           (200U)

#define NVMC_IF_IVI_DRCDATE_NUM         (8U)

#define NVMC_IF_IVI_CAM_KIND_UNFIX      (0x00U)
#define NVMC_IF_IVI_CAM_SIZE_NONE       (0x00U)
#define NVMC_IF_IVI_CAM_HANDLE_UNKNOWN  (0x02U)

#define NVMC_IF_IVI_RETRY_NON           (0U)
#define NVMC_IF_IVI_RETRY_MAX           (200U)

#define NVMC_IF_IVI_FAILVAL_RETRY       (U4_MAX)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_IF_IVI_VHP_PARK            (VEH_OPEMD_MDBIT_PBA)

#define NVMC_IF_IVI_ID_DIREC_INDEX      (NVMCID_U4_DIREC_INDEX)
#define NVMC_IF_IVI_ID_MAVTYPE          (NVMCID_U4_PICT_MAVTYPE)
#define NVMC_IF_IVI_ID_RCROP0           (NVMCID_U4_PICT_RCROP0)
#define NVMC_IF_IVI_ID_DIREC_STRGWHL    (NVMCID_U4_PICT_STRGWHL)

#define NVMC_IF_IVI_VM1TO2_CAM_DIAP     (IVDSH_DID_WRI_VM1TO2_CAM_DIAP)
#define NVMC_IF_IVI_VM2TO1_CAM_DIAP     (IVDSH_DID_REA_VM2TO1_CAM_DIAP)
#define NVMC_IF_IVI_VM1TO2_DRC_ALVCNT   (IVDSH_DID_WRI_VM1TO2_DRC_ALVCNT)
#define NVMC_IF_IVI_VM2TO1_DRC_ALVCNT   (IVDSH_DID_REA_VM2TO1_DRC_ALVCNT)
#define NVMC_IF_IVI_VM1TO2_DRC_RDDATA   (IVDSH_DID_WRI_VM1TO2_DRC_RDDATA)
#define NVMC_IF_IVI_VM2TO1_DRC_WRDATA   (IVDSH_DID_REA_VM2TO1_DRC_WRDATA)
#define NVMC_IF_IVI_VM1TO2_DRC_FSTRD    (IVDSH_DID_WRI_VM1TO2_DRC_FSTRD)
#define NVMC_IF_IVI_VM1TO2_DRC_WRINF    (IVDSH_DID_WRI_VM1TO2_DRC_WRINF)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2  u2_wp;
    U2  u2_wcnt;
} ST_DRC_MNG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_DRC_MNG   st_s_nvmc_ivi_drcmgr;
static U1           u1_s_nvmc_ivi_initread_flg;
static U1           u1_s_nvmc_ivi_rdalive_cnt;
static U1           u1_s_nvmc_ivi_wralive_cnt;
static U2           u2_s_nvmc_ivi_inird_p;
static U1           u1_s_nvmc_ivi_ini_retry_cnt;
static U1           u1_s_nvmc_ivi_wrinf_chgreq;
static U1           u1_s_nvmc_ivi_mavtype;
static U1           u1_s_nvmc_ivi_size;
static U1           u1_s_nvmc_ivi_handle;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_NvmcIfIVI_DrcInit(void);
static void     vd_s_NvmcIfIVI_CamInit(void);
static void     vd_s_NvmcIfIVI_DrcChk(void);
static void     vd_s_NvmcIfIVI_SetIniReadData(void);
static U1       u1_s_NvmcIfIVI_SetWriteData(const U1 u1_a_CNT);
static U1       u1_s_NvmcIfIVI_SetReadData(const U2 u2_a_NVM_ID);
static void     vd_s_NvmcIfIVI_Rdalivecnt(void);
static void     vd_s_NvmcIfIVI_CamChk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2 u2_sp_PICT_DRCDATA_TBL[NVMC_IF_IVI_DRCCNT_NUM] =
{
    (U2)NVMCID_OTR_DIREC_000,
    (U2)NVMCID_OTR_DIREC_001,
    (U2)NVMCID_OTR_DIREC_002,
    (U2)NVMCID_OTR_DIREC_003,
    (U2)NVMCID_OTR_DIREC_004,
    (U2)NVMCID_OTR_DIREC_005,
    (U2)NVMCID_OTR_DIREC_006,
    (U2)NVMCID_OTR_DIREC_007,
    (U2)NVMCID_OTR_DIREC_008,
    (U2)NVMCID_OTR_DIREC_009,
    (U2)NVMCID_OTR_DIREC_010,
    (U2)NVMCID_OTR_DIREC_011,
    (U2)NVMCID_OTR_DIREC_012,
    (U2)NVMCID_OTR_DIREC_013,
    (U2)NVMCID_OTR_DIREC_014,
    (U2)NVMCID_OTR_DIREC_015,
    (U2)NVMCID_OTR_DIREC_016,
    (U2)NVMCID_OTR_DIREC_017,
    (U2)NVMCID_OTR_DIREC_018,
    (U2)NVMCID_OTR_DIREC_019,
    (U2)NVMCID_OTR_DIREC_020,
    (U2)NVMCID_OTR_DIREC_021,
    (U2)NVMCID_OTR_DIREC_022,
    (U2)NVMCID_OTR_DIREC_023,
    (U2)NVMCID_OTR_DIREC_024,
    (U2)NVMCID_OTR_DIREC_025,
    (U2)NVMCID_OTR_DIREC_026,
    (U2)NVMCID_OTR_DIREC_027,
    (U2)NVMCID_OTR_DIREC_028,
    (U2)NVMCID_OTR_DIREC_029,
    (U2)NVMCID_OTR_DIREC_030,
    (U2)NVMCID_OTR_DIREC_031,
    (U2)NVMCID_OTR_DIREC_032,
    (U2)NVMCID_OTR_DIREC_033,
    (U2)NVMCID_OTR_DIREC_034,
    (U2)NVMCID_OTR_DIREC_035,
    (U2)NVMCID_OTR_DIREC_036,
    (U2)NVMCID_OTR_DIREC_037,
    (U2)NVMCID_OTR_DIREC_038,
    (U2)NVMCID_OTR_DIREC_039,
    (U2)NVMCID_OTR_DIREC_040,
    (U2)NVMCID_OTR_DIREC_041,
    (U2)NVMCID_OTR_DIREC_042,
    (U2)NVMCID_OTR_DIREC_043,
    (U2)NVMCID_OTR_DIREC_044,
    (U2)NVMCID_OTR_DIREC_045,
    (U2)NVMCID_OTR_DIREC_046,
    (U2)NVMCID_OTR_DIREC_047,
    (U2)NVMCID_OTR_DIREC_048,
    (U2)NVMCID_OTR_DIREC_049,
    (U2)NVMCID_OTR_DIREC_050,
    (U2)NVMCID_OTR_DIREC_051,
    (U2)NVMCID_OTR_DIREC_052,
    (U2)NVMCID_OTR_DIREC_053,
    (U2)NVMCID_OTR_DIREC_054,
    (U2)NVMCID_OTR_DIREC_055,
    (U2)NVMCID_OTR_DIREC_056,
    (U2)NVMCID_OTR_DIREC_057,
    (U2)NVMCID_OTR_DIREC_058,
    (U2)NVMCID_OTR_DIREC_059,
    (U2)NVMCID_OTR_DIREC_060,
    (U2)NVMCID_OTR_DIREC_061,
    (U2)NVMCID_OTR_DIREC_062,
    (U2)NVMCID_OTR_DIREC_063,
    (U2)NVMCID_OTR_DIREC_064,
    (U2)NVMCID_OTR_DIREC_065,
    (U2)NVMCID_OTR_DIREC_066,
    (U2)NVMCID_OTR_DIREC_067,
    (U2)NVMCID_OTR_DIREC_068,
    (U2)NVMCID_OTR_DIREC_069,
    (U2)NVMCID_OTR_DIREC_070,
    (U2)NVMCID_OTR_DIREC_071,
    (U2)NVMCID_OTR_DIREC_072,
    (U2)NVMCID_OTR_DIREC_073,
    (U2)NVMCID_OTR_DIREC_074,
    (U2)NVMCID_OTR_DIREC_075,
    (U2)NVMCID_OTR_DIREC_076,
    (U2)NVMCID_OTR_DIREC_077,
    (U2)NVMCID_OTR_DIREC_078,
    (U2)NVMCID_OTR_DIREC_079,
    (U2)NVMCID_OTR_DIREC_080,
    (U2)NVMCID_OTR_DIREC_081,
    (U2)NVMCID_OTR_DIREC_082,
    (U2)NVMCID_OTR_DIREC_083,
    (U2)NVMCID_OTR_DIREC_084,
    (U2)NVMCID_OTR_DIREC_085,
    (U2)NVMCID_OTR_DIREC_086,
    (U2)NVMCID_OTR_DIREC_087,
    (U2)NVMCID_OTR_DIREC_088,
    (U2)NVMCID_OTR_DIREC_089,
    (U2)NVMCID_OTR_DIREC_090,
    (U2)NVMCID_OTR_DIREC_091,
    (U2)NVMCID_OTR_DIREC_092,
    (U2)NVMCID_OTR_DIREC_093,
    (U2)NVMCID_OTR_DIREC_094,
    (U2)NVMCID_OTR_DIREC_095,
    (U2)NVMCID_OTR_DIREC_096,
    (U2)NVMCID_OTR_DIREC_097,
    (U2)NVMCID_OTR_DIREC_098,
    (U2)NVMCID_OTR_DIREC_099,
    (U2)NVMCID_OTR_DIREC_100,
    (U2)NVMCID_OTR_DIREC_101,
    (U2)NVMCID_OTR_DIREC_102,
    (U2)NVMCID_OTR_DIREC_103,
    (U2)NVMCID_OTR_DIREC_104,
    (U2)NVMCID_OTR_DIREC_105,
    (U2)NVMCID_OTR_DIREC_106,
    (U2)NVMCID_OTR_DIREC_107,
    (U2)NVMCID_OTR_DIREC_108,
    (U2)NVMCID_OTR_DIREC_109,
    (U2)NVMCID_OTR_DIREC_110,
    (U2)NVMCID_OTR_DIREC_111,
    (U2)NVMCID_OTR_DIREC_112,
    (U2)NVMCID_OTR_DIREC_113,
    (U2)NVMCID_OTR_DIREC_114,
    (U2)NVMCID_OTR_DIREC_115,
    (U2)NVMCID_OTR_DIREC_116,
    (U2)NVMCID_OTR_DIREC_117,
    (U2)NVMCID_OTR_DIREC_118,
    (U2)NVMCID_OTR_DIREC_119,
    (U2)NVMCID_OTR_DIREC_120,
    (U2)NVMCID_OTR_DIREC_121,
    (U2)NVMCID_OTR_DIREC_122,
    (U2)NVMCID_OTR_DIREC_123,
    (U2)NVMCID_OTR_DIREC_124,
    (U2)NVMCID_OTR_DIREC_125,
    (U2)NVMCID_OTR_DIREC_126,
    (U2)NVMCID_OTR_DIREC_127,
    (U2)NVMCID_OTR_DIREC_128,
    (U2)NVMCID_OTR_DIREC_129,
    (U2)NVMCID_OTR_DIREC_130,
    (U2)NVMCID_OTR_DIREC_131,
    (U2)NVMCID_OTR_DIREC_132,
    (U2)NVMCID_OTR_DIREC_133,
    (U2)NVMCID_OTR_DIREC_134
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void    vd_g_NvmcIfIVIBonInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NvmcIfIVIBonInit(void)
{
    vd_s_NvmcIfIVI_DrcInit();
    vd_s_NvmcIfIVI_CamInit();
}

/*===================================================================================================================================*/
/* void    vd_g_NvmcIfIVIRstInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NvmcIfIVIRstInit(void)
{
    vd_s_NvmcIfIVI_DrcInit();
    vd_s_NvmcIfIVI_CamInit();
}

/*===================================================================================================================================*/
/* void    vd_g_NvmcIfIVIWkupInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NvmcIfIVIWkupInit(void)
{
    vd_s_NvmcIfIVI_DrcInit();
    vd_s_NvmcIfIVI_CamInit();
}

/*===================================================================================================================================*/
/* static void    vd_s_NvmcIfIVI_DrcInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_NvmcIfIVI_DrcInit(void)
{
    U1 u1_t_sts;
    U4 u4_t_write;
    U4 u4_t_read;
    U2 u2_t_drc[NVMC_IF_IVI_RD_BUFF];
    
    u1_s_nvmc_ivi_initread_flg = (U1)FALSE;
    u1_s_nvmc_ivi_rdalive_cnt = (U1)NVMC_IF_IVI_ALCNT_MIN;
    u1_s_nvmc_ivi_wralive_cnt = (U1)NVMC_IF_IVI_ALCNT_MIN;
    u2_s_nvmc_ivi_inird_p = (U2)0U;
    u1_s_nvmc_ivi_ini_retry_cnt = (U1)NVMC_IF_IVI_RETRY_NON;
    u1_s_nvmc_ivi_wrinf_chgreq = (U1)FALSE;
    st_s_nvmc_ivi_drcmgr.u2_wp = (U2)0U;
    st_s_nvmc_ivi_drcmgr.u2_wcnt = (U2)0U;
    
    u4_t_read = (U4)0U;
    u1_t_sts = u1_g_Nvmc_ReadU4withSts((U2)NVMC_IF_IVI_ID_DIREC_INDEX, &u4_t_read);
    if(u1_t_sts == (U1)NVMC_STATUS_COMP){
        u2_t_drc[NVMC_IF_IVI_RD_WCNT] = (U2)(u4_t_read & (U4)NVMC_IF_IVI_MASK_LOBYTE);
        u2_t_drc[NVMC_IF_IVI_RD_WP] = (U2)((u4_t_read & (U4)NVMC_IF_IVI_MASK_HIBYTE) >> NVMC_IF_IVI_SHIF_2BYTE);
        if(u2_t_drc[NVMC_IF_IVI_RD_WP] < (U2)NVMC_IF_IVI_DRCCNT_NUM){
            st_s_nvmc_ivi_drcmgr.u2_wcnt = u2_t_drc[NVMC_IF_IVI_RD_WCNT];
            st_s_nvmc_ivi_drcmgr.u2_wp = u2_t_drc[NVMC_IF_IVI_RD_WP];
        }
    }
    
    u4_t_write = (U4)0U;
    vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_ALVCNT, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);

    u4_t_write  = (U4)st_s_nvmc_ivi_drcmgr.u2_wcnt;
    u4_t_write |= (U4)((U4)st_s_nvmc_ivi_drcmgr.u2_wp << NVMC_IF_IVI_SHIF_2BYTE);
    vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_WRINF, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);
    
    u4_t_write = (U4)u1_s_nvmc_ivi_initread_flg;
    vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_FSTRD, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);
}

/*===================================================================================================================================*/
/* static void    vd_s_NvmcIfIVI_CamInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_NvmcIfIVI_CamInit(void)
{
    U1 u1_t_sts;
    U4 u4_t_read;
    U4 u4_t_write;
    
    u1_s_nvmc_ivi_mavtype = (U1)NVMC_IF_IVI_CAM_KIND_UNFIX;
    u1_s_nvmc_ivi_size = (U1)NVMC_IF_IVI_CAM_SIZE_NONE;
    u1_s_nvmc_ivi_handle = (U1)NVMC_IF_IVI_CAM_HANDLE_UNKNOWN;

    u4_t_read = (U4)0U;
    u1_t_sts = u1_g_Nvmc_ReadU4withSts((U2)NVMC_IF_IVI_ID_MAVTYPE, &u4_t_read);
    if(u1_t_sts == (U1)NVMC_STATUS_COMP){
        u1_s_nvmc_ivi_mavtype = u4_t_read & (U4)NVMC_IF_IVI_MASK_1BYTE;
    }

    u1_t_sts = u1_g_Nvmc_ReadU4withSts((U2)NVMC_IF_IVI_ID_RCROP0, &u4_t_read);
    if(u1_t_sts == (U1)NVMC_STATUS_COMP){
        u1_s_nvmc_ivi_size = u4_t_read & (U4)NVMC_IF_IVI_MASK_1BYTE;
    }

    u1_t_sts = u1_g_Nvmc_ReadU4withSts((U2)NVMC_IF_IVI_ID_DIREC_STRGWHL, &u4_t_read);
    if(u1_t_sts == (U1)NVMC_STATUS_COMP){
        u1_s_nvmc_ivi_handle = u4_t_read & (U4)NVMC_IF_IVI_MASK_1BYTE;
    }
    
    u4_t_write  = (U4)u1_s_nvmc_ivi_mavtype;
    u4_t_write |= (U4)((U4)u1_s_nvmc_ivi_size << NVMC_IF_IVI_SHIF_1BYTE);
    u4_t_write |= (U4)((U4)u1_s_nvmc_ivi_handle  << NVMC_IF_IVI_SHIF_2BYTE);
    vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_CAM_DIAP, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);
}

/*===================================================================================================================================*/
/*  void    vd_g_NvmcIfIVIMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NvmcIfIVIMainTask(void)
{
    vd_s_NvmcIfIVI_DrcChk();
    vd_s_NvmcIfIVI_CamChk();
}

/*===================================================================================================================================*/
/*  static void vd_s_NvmcIfIVI_DrcChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_NvmcIfIVI_DrcChk(void)
{
    U1 u1_t_sts;
    U4 u4_t_read;
    U4 u4_t_write;
    U1 u1_t_rdalive_cnt;
    U1 u1_t_wralive_cnt;
    U1 u1_t_chg_req;
    U4 u4_t_power_sts;
    U1 u1_write_sts;
    
    u1_t_sts = (U1)0U;
    u4_t_read = (U4)0U;
    u4_t_write = (U4)0U;
    u1_t_rdalive_cnt = NVMC_IF_IVI_ALCNT_UNKNOWN;
    u1_t_wralive_cnt = NVMC_IF_IVI_ALCNT_UNKNOWN;
    u1_t_chg_req = (U1)FALSE;
    u4_t_power_sts = u4_g_VehopemdMdfield();
    u1_write_sts = (U1)FALSE;
    
    u1_t_sts = u1_g_iVDshReabyDid((U2)NVMC_IF_IVI_VM2TO1_DRC_ALVCNT, &u4_t_read, (U2)NVMC_IF_IVI_VM_1WORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u1_t_rdalive_cnt = (U1)(u4_t_read & (U4)NVMC_IF_IVI_MASK_1BYTE);
        u1_t_wralive_cnt = (U1)((u4_t_read & (U4)NVMC_IF_IVI_MASK_2BYTE) >> NVMC_IF_IVI_SHIF_1BYTE);
    }
    
    if(u1_s_nvmc_ivi_initread_flg == (U1)FALSE){
        if(((u1_t_rdalive_cnt == u1_s_nvmc_ivi_rdalive_cnt) &&
           (u1_t_rdalive_cnt != (U1)NVMC_IF_IVI_ALCNT_UNKNOWN)) ||
           (u1_s_nvmc_ivi_ini_retry_cnt != (U1)NVMC_IF_IVI_RETRY_NON)){
            vd_s_NvmcIfIVI_SetIniReadData();
            u1_t_chg_req = (U1)TRUE;
        }
    }
    else{
        if((u1_t_rdalive_cnt == u1_s_nvmc_ivi_rdalive_cnt) &&
           (u1_t_wralive_cnt != u1_s_nvmc_ivi_wralive_cnt)){
            u1_write_sts = u1_s_NvmcIfIVI_SetWriteData(u1_t_wralive_cnt);
            u1_t_chg_req = (U1)TRUE;
        }
    }
    if(u1_t_chg_req == (U1)TRUE){
        u4_t_write  = (U4)u1_s_nvmc_ivi_rdalive_cnt;
        u4_t_write |= (U4)((U4)u1_s_nvmc_ivi_wralive_cnt << NVMC_IF_IVI_SHIF_1BYTE);
        vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_ALVCNT, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);
    }
    
    if(u1_write_sts == (U1)TRUE){
        u4_t_write = (U4)st_s_nvmc_ivi_drcmgr.u2_wcnt;
        u4_t_write |= (U4)((U4)st_s_nvmc_ivi_drcmgr.u2_wp << NVMC_IF_IVI_SHIF_2BYTE);
        vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_WRINF, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);
        u1_s_nvmc_ivi_wrinf_chgreq = (U1)TRUE;
    }
    
    if((u4_t_power_sts == (U4)NVMC_IF_IVI_VHP_PARK) &&
       (u1_s_nvmc_ivi_wrinf_chgreq != (U1)FALSE)){
        u4_t_write  = (U4)st_s_nvmc_ivi_drcmgr.u2_wcnt;
        u4_t_write |= (U4)((U4)st_s_nvmc_ivi_drcmgr.u2_wp << NVMC_IF_IVI_SHIF_2BYTE);
        vd_g_Nvmc_WriteU4((U2)NVMC_IF_IVI_ID_DIREC_INDEX, u4_t_write);
        u1_s_nvmc_ivi_wrinf_chgreq = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_NvmcIfIVI_SetIniReadData(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_NvmcIfIVI_SetIniReadData(void)
{
    U2 u2_t_dtcid;
    U4 u4_t_write;
    U1 u1_t_sts;
    U1 u1_t_req;
    U4 u4_t_drc[NVMC_IF_IVI_VM_2WORD];
    
    u4_t_drc[NVMC_IF_IVI_RD_ID] = (U4)NVMC_IF_IVI_FAILVAL_RETRY;
    u4_t_drc[NVMC_IF_IVI_RD_TIME] = (U4)NVMC_IF_IVI_FAILVAL_RETRY;
    
    if((st_s_nvmc_ivi_drcmgr.u2_wp <= u2_s_nvmc_ivi_inird_p) &&
       (st_s_nvmc_ivi_drcmgr.u2_wcnt <= (U2)NVMC_IF_IVI_DRCCNT_MAX)){
        u1_s_nvmc_ivi_initread_flg = (U1)TRUE;
        vd_s_NvmcIfIVI_Rdalivecnt();
    }
    
    if(u1_s_nvmc_ivi_initread_flg == (U1)FALSE){
        u2_t_dtcid = u2_sp_PICT_DRCDATA_TBL[u2_s_nvmc_ivi_inird_p];
        u1_t_sts = u1_s_NvmcIfIVI_SetReadData(u2_t_dtcid);
        u1_t_req = (U1)FALSE;
        
        if(u1_t_sts == (U1)TRUE){
            u1_s_nvmc_ivi_ini_retry_cnt = (U1)NVMC_IF_IVI_RETRY_NON;
            u1_t_req = (U1)TRUE;
        }
        else{
            u1_s_nvmc_ivi_ini_retry_cnt++;
            if(u1_s_nvmc_ivi_ini_retry_cnt >= NVMC_IF_IVI_RETRY_MAX){
                u1_t_req = (U1)TRUE;
                u1_s_nvmc_ivi_ini_retry_cnt = (U1)NVMC_IF_IVI_RETRY_NON;
                vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_RDDATA, &u4_t_drc[0], (U2)NVMC_IF_IVI_VM_2WORD);
                vd_s_NvmcIfIVI_Rdalivecnt();
            }
        }
        if(u1_t_req == (U1)TRUE){
            if(u2_s_nvmc_ivi_inird_p < (U2)NVMC_IF_IVI_DRCCNT_MAX){
                u2_s_nvmc_ivi_inird_p++;
            }
            else{
                u2_s_nvmc_ivi_inird_p = (U2)0U;
                u1_s_nvmc_ivi_initread_flg = (U1)TRUE;
            }
        }
    }
    
    u4_t_write = (U4)u1_s_nvmc_ivi_initread_flg;
    vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_FSTRD, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_NvmcIfIVI_SetWriteData(const U1 u1_a_CNT)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_NvmcIfIVI_SetWriteData(const U1 u1_a_CNT)
{
    U1 u1_t_sts;
    U2 u2_t_dtcid;
    U1 u1_t_return;
    U4 u4_t_drc[NVMC_IF_IVI_VM_2WORD];
    
    u1_t_sts = (U1)0U;
    u2_t_dtcid = (U2)0U;
    u1_t_return = (U1)FALSE;
    u4_t_drc[NVMC_IF_IVI_RD_ID] = (U4)0U;
    u4_t_drc[NVMC_IF_IVI_RD_TIME] = (U4)0U;
    
    u1_t_sts = u1_g_iVDshReabyDid((U2)NVMC_IF_IVI_VM2TO1_DRC_WRDATA, &u4_t_drc[0], (U2)NVMC_IF_IVI_VM_2WORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u2_t_dtcid = u2_sp_PICT_DRCDATA_TBL[st_s_nvmc_ivi_drcmgr.u2_wp];
        vd_g_Nvmc_WriteOthr(u2_t_dtcid, (U2)NVMC_IF_IVI_DRCDATE_NUM, (U1*)&u4_t_drc[0]);
        u1_s_nvmc_ivi_wralive_cnt = u1_a_CNT;
        
        if(st_s_nvmc_ivi_drcmgr.u2_wp < (U2)NVMC_IF_IVI_DRCCNT_MAX){
            st_s_nvmc_ivi_drcmgr.u2_wp++;
        }
        else{
            st_s_nvmc_ivi_drcmgr.u2_wp = (U2)0U;
        }
        
        if(st_s_nvmc_ivi_drcmgr.u2_wcnt < (U2)U2_MAX){
            st_s_nvmc_ivi_drcmgr.u2_wcnt++;
        }
        
        vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_RDDATA, &u4_t_drc[0], (U2)NVMC_IF_IVI_VM_2WORD);
        vd_s_NvmcIfIVI_Rdalivecnt();
        
        u1_t_return = (U1)TRUE;
    }
    
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_NvmcIfIVI_SetReadData(const U2 u2_a_NVM_ID)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_NvmcIfIVI_SetReadData(const U2 u2_a_NVM_ID)
{
    U1 u1_t_sts;
    U1 u1_t_return;
    U4 u4_t_drc[NVMC_IF_IVI_VM_2WORD];
    
    u1_t_sts = (U1)0U;
    u1_t_return = (U1)FALSE;
    u4_t_drc[NVMC_IF_IVI_RD_ID] = (U4)0U;
    u4_t_drc[NVMC_IF_IVI_RD_TIME] = (U4)0U;
    
    u1_t_sts = u1_g_Nvmc_ReadOthrwithSts(u2_a_NVM_ID, (U2)NVMC_IF_IVI_DRCDATE_NUM, (U1*)&u4_t_drc[0]);
    if(u1_t_sts == (U1)NVMC_STATUS_COMP){
        vd_s_NvmcIfIVI_Rdalivecnt();
        u1_t_return = (U1)TRUE;
    }
    else{
        u4_t_drc[NVMC_IF_IVI_RD_TIME] = (U4)0U;
        u4_t_drc[NVMC_IF_IVI_RD_ID] = (U4)0U;
        u1_s_nvmc_ivi_rdalive_cnt = (U1)NVMC_IF_IVI_ALCNT_UNKNOWN;
    }
    vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_DRC_RDDATA, &u4_t_drc[0], (U2)NVMC_IF_IVI_VM_2WORD);
    
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void vd_s_NvmcIfIVI_Rdalivecnt(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_NvmcIfIVI_Rdalivecnt(void)
{
    if(u1_s_nvmc_ivi_rdalive_cnt < (U1)NVMC_IF_IVI_ALCNT_MAX){
        u1_s_nvmc_ivi_rdalive_cnt++;
    }
    else{
        u1_s_nvmc_ivi_rdalive_cnt = (U1)NVMC_IF_IVI_ALCNT_MIN;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_NvmcIfIVI_CamChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_NvmcIfIVI_CamChk(void)
{
    U1 u1_t_sts;
    U4 u4_t_read;
    U4 u4_t_write;
    U1 u1_t_mavtype;
    U1 u1_t_size;
    U1 u1_t_handle;
    U1 u1_t_req;
    
    u4_t_read = (U4)0U;
    u4_t_write = (U4)0U;
    u1_t_mavtype = u1_s_nvmc_ivi_mavtype;
    u1_t_size = u1_s_nvmc_ivi_size;
    u1_t_handle = u1_s_nvmc_ivi_handle;
    u1_t_req = (U1)FALSE;
    
    u1_t_sts = u1_g_iVDshReabyDid((U2)NVMC_IF_IVI_VM2TO1_CAM_DIAP, &u4_t_read, (U2)NVMC_IF_IVI_VM_1WORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u1_t_mavtype = (U1)(u4_t_read & (U4)NVMC_IF_IVI_MASK_1BYTE);
        u1_t_size = (U1)((u4_t_read & (U4)NVMC_IF_IVI_MASK_2BYTE) >> NVMC_IF_IVI_SHIF_1BYTE);
        u1_t_handle = (U1)((u4_t_read & (U4)NVMC_IF_IVI_MASK_3BYTE) >> NVMC_IF_IVI_SHIF_2BYTE);
    }
    
    if(u1_t_mavtype != u1_s_nvmc_ivi_mavtype){
        u1_s_nvmc_ivi_mavtype = u1_t_mavtype;
        u4_t_write = (U4)u1_t_mavtype;
        vd_g_Nvmc_WriteU4((U2)NVMC_IF_IVI_ID_MAVTYPE, u4_t_write);
        u1_t_req = (U1)TRUE;
    }
    
    if(u1_t_size != u1_s_nvmc_ivi_size){
        u1_s_nvmc_ivi_size = u1_t_size;
        u4_t_write = (U4)u1_t_size;
        vd_g_Nvmc_WriteU4((U2)NVMC_IF_IVI_ID_RCROP0, u4_t_write);
        u1_t_req = (U1)TRUE;
    }
    
    if(u1_t_handle != u1_s_nvmc_ivi_handle){
        u1_s_nvmc_ivi_handle = u1_t_handle;
        u4_t_write = (U4)u1_t_handle;
        vd_g_Nvmc_WriteU4((U2)NVMC_IF_IVI_ID_DIREC_STRGWHL, u4_t_write);
        u1_t_req = (U1)TRUE;
    }
    
    if(u1_t_req == (U1)TRUE){
        u4_t_write  = (U4)u1_s_nvmc_ivi_mavtype;
        u4_t_write |= (U4)((U4)u1_s_nvmc_ivi_size << NVMC_IF_IVI_SHIF_1BYTE);
        u4_t_write |= (U4)((U4)u1_s_nvmc_ivi_handle  << NVMC_IF_IVI_SHIF_2BYTE);
        vd_g_iVDshWribyDid((U2)NVMC_IF_IVI_VM1TO2_CAM_DIAP, &u4_t_write, (U2)NVMC_IF_IVI_VM_1WORD);
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    4/14/2026   FO       New.                                                                                               */
/*                                                                                                                                   */
/*  * FO   = Fumiya Onishi, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
