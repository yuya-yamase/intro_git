/* Dcm_Dsd_Main_Cfg_c(v5-4-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_Main_Cfg/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <Dcm/Dcm_Dsd_Main_Callout.h>
#include "../../Dsd/cfg/Dcm_Dsd_Main_Cfg.h"

#include <Dcm/Dcm_Dsp_SID10.h>
#include <Dcm/Dcm_Dsp_SID14.h>
#include <Dcm/Dcm_Dsp_SID28.h>
#include <Dcm/Dcm_Dsp_SID3E.h>
#include <Dcm/Dcm_Apl_SID22.h>
#include <Dcm/Dcm_Apl_SID2E.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


/* Dcm_Dsd_stService[0000] SID=0x10 SF=0x02 */
/* Table of subfunctions SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0000SB02SesChk[3] =
{
    /* Enable Session List */
    (uint8)0x01U,
    (uint8)0x02U,
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0000] SID=0x10 SF=0x03 */
/* Table of subfunctions SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0000SB03SesChk[2] =
{
    /* Enable Session List */
    (uint8)0x01U,
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0000] SID=0x10 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0000SubService[3] =
{
    /* Dcm_Dsd_stService[0000] SID=0x10 SF=0x01 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub01), NULL_PTR,                       NULL_PTR,                       (uint8)0x01U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0000] SID=0x10 SF=0x02 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub02), NULL_PTR,                       Dcm_Dsd_stIdx0000SB02SesChk,    (uint8)0x02U,   (uint8)0U,          (uint8)3U
    },
    /* Dcm_Dsd_stService[0000] SID=0x10 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub03), NULL_PTR,                       Dcm_Dsd_stIdx0000SB03SesChk,    (uint8)0x03U,   (uint8)0U,          (uint8)2U
    }
};

/* Dcm_Dsd_stService[0001] SID=0x14 */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0001SesChk[2] =
{
    /* Enable Session List */
    (uint8)0x01U,
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0003] SID=0x28 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0003SubService[2] =
{
    /* Dcm_Dsd_stService[0003] SID=0x28 SF=0x00 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID28_Sub00), NULL_PTR,                       NULL_PTR,                       (uint8)0x00U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0003] SID=0x28 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID28_Sub03), NULL_PTR,                       NULL_PTR,                       (uint8)0x03U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[0003] SID=0x28 */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0003SesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0004] SID=0x3E */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0004SubService[1] =
{
    /* Dcm_Dsd_stService[0004] SID=0x3E SF=0x00 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID3E_Sub00), NULL_PTR,                       NULL_PTR,                       (uint8)0x00U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[0005] SID=0x10 SF=0x03 */
/* Table of subfunctions SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0005SB03SesChk[2] =
{
    /* Enable Session List */
    (uint8)0x01U,
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0005] SID=0x10 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0005SubService[2] =
{
    /* Dcm_Dsd_stService[0005] SID=0x10 SF=0x01 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub01), NULL_PTR,                       NULL_PTR,                       (uint8)0x01U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0005] SID=0x10 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub03), NULL_PTR,                       Dcm_Dsd_stIdx0005SB03SesChk,    (uint8)0x03U,   (uint8)0U,          (uint8)2U
    }
};

/* Dcm_Dsd_stService[0006] SID=0x10 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0006SubService[1] =
{
    /* Dcm_Dsd_stService[0006] SID=0x10 SF=0x01 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub01), NULL_PTR,                       NULL_PTR,                       (uint8)0x01U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[0008] SID=0x2E */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0008SesChk[2] =
{
    /* Enable Session List */
    (uint8)0x02U,
    (uint8)0x03U
};

/* Table of all services */
CONST(AB_83_ConstV Dcm_Dsd_ServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stService[DCM_D_SERVICE_NUM] =
{
    /* Idx=0000 SID=0x10 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx0000SubService,    (uint8)0x10U,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)3U
    },
    /* Idx=0001 SID=0x14 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(Dcm_SID14),   NULL_PTR,                   Dcm_Dsd_stIdx0001SesChk,    NULL_PTR,                       (uint8)0x14U,   (boolean)FALSE,     (uint8)0U,          (uint8)2U,          (uint8)0U
    },
    /* Idx=0002 SID=0x22 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(u1_g_oXDoCANApl_SID22),NULL_PTR,                   NULL_PTR,                   NULL_PTR,                       (uint8)0x22U,   (boolean)FALSE,     (uint8)0U,          (uint8)0U,          (uint8)0U
    },
    /* Idx=0003 SID=0x28 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   Dcm_Dsd_stIdx0003SesChk,    Dcm_Dsd_stIdx0003SubService,    (uint8)0x28U,   (boolean)TRUE,      (uint8)0U,          (uint8)1U,          (uint8)2U
    },
    /* Idx=0004 SID=0x3E */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx0004SubService,    (uint8)0x3EU,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)1U
    },
    /* Idx=0005 SID=0x10 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx0005SubService,    (uint8)0x10U,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)2U
    },
    /* Idx=0006 SID=0x10 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx0006SubService,    (uint8)0x10U,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)1U
    },
    /* Idx=0007 SID=0x14 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(Dcm_SID14),   NULL_PTR,                   NULL_PTR,                   NULL_PTR,                       (uint8)0x14U,   (boolean)FALSE,     (uint8)0U,          (uint8)0U,          (uint8)0U
    },
    /* Idx=0008 SID=0x2E */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(u1_g_oXDoCANApl_SID2E),NULL_PTR,                   Dcm_Dsd_stIdx0008SesChk,    NULL_PTR,                       (uint8)0x2EU,   (boolean)FALSE,     (uint8)0U,          (uint8)2U,          (uint8)0U
    },
    /* Idx=0009 SID=0x19 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   NULL_PTR,                       (uint8)0x19U,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)0U
    }
};

/* Table of Dcm_Dsd_stService Index */
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0004_ServiceIndex[5] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0000U,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0004U
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0005_ServiceIndex[5] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0005U,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0004U
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0006_ServiceIndex[4] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0006U,
    (uint8)0x0007U,
    (uint8)0x0002U,
    (uint8)0x0004U
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0007_ServiceIndex[6] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0000U,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0008U,
    (uint8)0x0004U
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0008_ServiceIndex[5] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0005U,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0004U
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0009_ServiceIndex[5] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0006U,
    (uint8)0x0007U,
    (uint8)0x0009U,
    (uint8)0x0002U,
    (uint8)0x0004U
};

CONST(AB_83_ConstV Dcm_DsdType, DCM_CONFIG_DATA) Dcm_Dsd_stConfigSet =
{
    /* bReqMfrNotifyEnabled     bReqSplrNotifyEnabled   ptMfrIndNotify              ptMfrConfNotify             ptSplrIndNotify             ptSplrConfNotify */
    (boolean)FALSE,             (boolean)FALSE,         NULL_PTR,                   NULL_PTR,                   NULL_PTR,                   NULL_PTR,
    /* stServiceTable */
    {
        /* u2Id             u1ServiceNum,         ptServiceIdx  */
        {  (uint16)0x0004U, (uint8)5U,            Dcm_Dsd_PduId0004_ServiceIndex },
        {  (uint16)0x0005U, (uint8)5U,            Dcm_Dsd_PduId0005_ServiceIndex },
        {  (uint16)0x0006U, (uint8)4U,            Dcm_Dsd_PduId0006_ServiceIndex },
        {  (uint16)0x0007U, (uint8)6U,            Dcm_Dsd_PduId0007_ServiceIndex },
        {  (uint16)0x0008U, (uint8)5U,            Dcm_Dsd_PduId0008_ServiceIndex },
        {  (uint16)0x0009U, (uint8)5U,            Dcm_Dsd_PduId0009_ServiceIndex }
    }
};

CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Mfrindnotify_Num = (uint8)DCM_D_MFRINDNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Mfrconfnotify_Num = (uint8)DCM_D_MFRCONFNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Splrindnotify_Num = (uint8)DCM_D_SPLRINDNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Splrconfnotify_Num = (uint8)DCM_D_SPLRCONFNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Servicetable_Num = (uint8)DCM_D_SERVICETABLE_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1SupportObdSystem = DCM_DSD_OBDSYS_NONOBD;
CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsd_bNoSuppressNegResIMLOIFToOBDClient = (boolean)FALSE;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
