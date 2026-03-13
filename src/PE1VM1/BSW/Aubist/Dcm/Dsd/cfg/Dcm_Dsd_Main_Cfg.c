/* Dcm_Dsd_Main_Cfg_c(v5-10-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#include <Dcm/Dcm_Dsp_SID19_Sub02.h>
#include <Dcm/Dcm_Dsp_SID19_Sub03.h>
#include <Dcm/Dcm_Dsp_SID19_Sub04.h>
#include <Dcm/Dcm_Dsp_SID19_Sub17.h>
#include <Dcm/Dcm_Dsp_SID19_Sub18.h>
#include <Dcm/Dcm_Dsp_SID28.h>
#include <Dcm/Dcm_Dsp_SID3E.h>
#include <Dcm/Dcm_Dsp_SID27.h>
#include <Dcm/Dcm_Dsp_SID86.h>
#include <Dcm/Dcm_Apl_SID22.h>
#include <Dcm/Dcm_Apl_SID2E.h>
#include <Dcm/Dcm_Apl_SID2F.h>
#include <Dcm/Dcm_Apl_SID31.h>
#include <Dcm/Dcm_Apl_SIDBA.h>


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

/* Definitions table of request notice mechanism R-PORT name (Xxx_Indication) for suppliers   */
static CONST(AB_83_ConstV Dcm_Dsd_IndicationFuncType, DCM_CONFIG_DATA) Dcm_Dsd_SplrIndNotify[DCM_D_SPLRINDNOTIFY_NUM] =
{
    &(Dcm_Indication)
};


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

/* Dcm_Dsd_stService[0002] SID=0x19 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0002SubService[5] =
{
    /* Dcm_Dsd_stService[0002] SID=0x19 SF=0x02 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub02), NULL_PTR,                       NULL_PTR,                       (uint8)0x02U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0002] SID=0x19 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub03), NULL_PTR,                       NULL_PTR,                       (uint8)0x03U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0002] SID=0x19 SF=0x04 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub04), NULL_PTR,                       NULL_PTR,                       (uint8)0x04U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0002] SID=0x19 SF=0x17 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub17), NULL_PTR,                       NULL_PTR,                       (uint8)0x17U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0002] SID=0x19 SF=0x18 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub18), NULL_PTR,                       NULL_PTR,                       (uint8)0x18U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[0002] SID=0x19 */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0002SesChk[2] =
{
    /* Enable Session List */
    (uint8)0x01U,
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0004] SID=0x28 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0004SubService[2] =
{
    /* Dcm_Dsd_stService[0004] SID=0x28 SF=0x00 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID28_Sub00), NULL_PTR,                       NULL_PTR,                       (uint8)0x00U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[0004] SID=0x28 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID28_Sub03), NULL_PTR,                       NULL_PTR,                       (uint8)0x03U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[0004] SID=0x28 */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0004SesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0005] SID=0x2E */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0005SesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0006] SID=0x2F */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0006SesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[0008] SID=0x3E */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0008SubService[1] =
{
    /* Dcm_Dsd_stService[0008] SID=0x3E SF=0x00 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID3E_Sub00), NULL_PTR,                       NULL_PTR,                       (uint8)0x00U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[0009] SID=0xBA */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx0009SesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[000A] SID=0x27 SF=0x03 */
/* Table of subfunctions SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000ASB03SesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[000A] SID=0x27 SF=0x04 */
/* Table of subfunctions SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000ASB04SesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[000A] SID=0x27 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000ASubService[2] =
{
    /* Dcm_Dsd_stService[000A] SID=0x27 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID27_Sub03), NULL_PTR,                       Dcm_Dsd_stIdx000ASB03SesChk,    (uint8)0x03U,   (uint8)0U,          (uint8)1U
    },
    /* Dcm_Dsd_stService[000A] SID=0x27 SF=0x04 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID27_Sub04), NULL_PTR,                       Dcm_Dsd_stIdx000ASB04SesChk,    (uint8)0x04U,   (uint8)0U,          (uint8)1U
    }
};

/* Dcm_Dsd_stService[000A] SID=0x27 */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000ASesChk[1] =
{
    /* Enable Session List */
    (uint8)0x03U
};

/* Dcm_Dsd_stService[000B] SID=0x10 SF=0x03 */
/* Table of subfunctions SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000BSB03SesChk[2] =
{
    /* Enable Session List */
    (uint8)0x01U,
    (uint8)0x03U
};

/* Dcm_Dsd_stService[000B] SID=0x10 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000BSubService[2] =
{
    /* Dcm_Dsd_stService[000B] SID=0x10 SF=0x01 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub01), NULL_PTR,                       NULL_PTR,                       (uint8)0x01U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000B] SID=0x10 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub03), NULL_PTR,                       Dcm_Dsd_stIdx000BSB03SesChk,    (uint8)0x03U,   (uint8)0U,          (uint8)2U
    }
};

/* Dcm_Dsd_stService[000C] SID=0x10 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000CSubService[2] =
{
    /* Dcm_Dsd_stService[000C] SID=0x10 SF=0x01 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub01), NULL_PTR,                       NULL_PTR,                       (uint8)0x01U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000C] SID=0x10 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID10_Sub03), NULL_PTR,                       NULL_PTR,                       (uint8)0x03U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[000D] SID=0x19 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000DSubService[5] =
{
    /* Dcm_Dsd_stService[000D] SID=0x19 SF=0x02 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub02), NULL_PTR,                       NULL_PTR,                       (uint8)0x02U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000D] SID=0x19 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub03), NULL_PTR,                       NULL_PTR,                       (uint8)0x03U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000D] SID=0x19 SF=0x04 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub04), NULL_PTR,                       NULL_PTR,                       (uint8)0x04U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000D] SID=0x19 SF=0x17 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub17), NULL_PTR,                       NULL_PTR,                       (uint8)0x17U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000D] SID=0x19 SF=0x18 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID19_Sub18), NULL_PTR,                       NULL_PTR,                       (uint8)0x18U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[000E] SID=0x86 */
/* Table of subfunctions */
static CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000ESubService[5] =
{
    /* Dcm_Dsd_stService[000E] SID=0x86 SF=0x00 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID86_Sub00), NULL_PTR,                       NULL_PTR,                       (uint8)0x00U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000E] SID=0x86 SF=0x03 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID86_Sub03), NULL_PTR,                       NULL_PTR,                       (uint8)0x03U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000E] SID=0x86 SF=0x05 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID86_Sub05), NULL_PTR,                       NULL_PTR,                       (uint8)0x05U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000E] SID=0x86 SF=0x06 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID86_Sub06), NULL_PTR,                       NULL_PTR,                       (uint8)0x06U,   (uint8)0U,          (uint8)0U
    },
    /* Dcm_Dsd_stService[000E] SID=0x86 SF=0x45 */
    {
        /* ptFnc            ptSecurityLevel                 ptSessionLevel                  u1Id            u1SecurityLevelNum  u1SessionLevelNum    */
        &(Dcm_SID86_Sub45), NULL_PTR,                       NULL_PTR,                       (uint8)0x45U,   (uint8)0U,          (uint8)0U
    }
};

/* Dcm_Dsd_stService[000E] SID=0x86 */
/* Table of service SessionCheck */
static CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_Dsd_stIdx000ESesChk[1] =
{
    /* Enable Session List */
    (uint8)0x01U
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
    /* Idx=0002 SID=0x19 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   Dcm_Dsd_stIdx0002SesChk,    Dcm_Dsd_stIdx0002SubService,    (uint8)0x19U,   (boolean)TRUE,      (uint8)0U,          (uint8)2U,          (uint8)5U
    },
    /* Idx=0003 SID=0x22 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(u1_g_oXDoCANApl_SID22),NULL_PTR,                   NULL_PTR,                   NULL_PTR,                       (uint8)0x22U,   (boolean)FALSE,     (uint8)0U,          (uint8)0U,          (uint8)0U
    },
    /* Idx=0004 SID=0x28 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   Dcm_Dsd_stIdx0004SesChk,    Dcm_Dsd_stIdx0004SubService,    (uint8)0x28U,   (boolean)TRUE,      (uint8)0U,          (uint8)1U,          (uint8)2U
    },
    /* Idx=0005 SID=0x2E */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(u1_g_oXDoCANApl_SID2E),NULL_PTR,                   Dcm_Dsd_stIdx0005SesChk,    NULL_PTR,                       (uint8)0x2EU,   (boolean)FALSE,     (uint8)0U,          (uint8)1U,          (uint8)0U
    },
    /* Idx=0006 SID=0x2F */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(u1_g_oXDoCANApl_SID2F),NULL_PTR,                   Dcm_Dsd_stIdx0006SesChk,    NULL_PTR,                       (uint8)0x2FU,   (boolean)FALSE,     (uint8)0U,          (uint8)1U,          (uint8)0U
    },
    /* Idx=0007 SID=0x31 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(u1_g_oXDoCANApl_SID31),NULL_PTR,                   NULL_PTR,                   NULL_PTR,                       (uint8)0x31U,   (boolean)FALSE,     (uint8)0U,          (uint8)0U,          (uint8)0U
    },
    /* Idx=0008 SID=0x3E */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx0008SubService,    (uint8)0x3EU,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)1U
    },
    /* Idx=0009 SID=0xBA */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        &(u1_g_oXDoCANApl_SIDBA),NULL_PTR,                   Dcm_Dsd_stIdx0009SesChk,    NULL_PTR,                       (uint8)0xBAU,   (boolean)FALSE,     (uint8)0U,          (uint8)1U,          (uint8)0U
    },
    /* Idx=000A SID=0x27 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   Dcm_Dsd_stIdx000ASesChk,    Dcm_Dsd_stIdx000ASubService,    (uint8)0x27U,   (boolean)TRUE,      (uint8)0U,          (uint8)1U,          (uint8)2U
    },
    /* Idx=000B SID=0x10 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx000BSubService,    (uint8)0x10U,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)2U
    },
    /* Idx=000C SID=0x10 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx000CSubService,    (uint8)0x10U,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)2U
    },
    /* Idx=000D SID=0x19 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_stIdx000DSubService,    (uint8)0x19U,   (boolean)TRUE,      (uint8)0U,          (uint8)0U,          (uint8)5U
    },
    /* Idx=000E SID=0x86 */
    {
        /* ptFnc        ptSecurityLevelRef          ptSessionLevelRef           ptSubService                    u1Id            bSubfuncAvail       u1SecurityLevelNum  u1SessionLevelNum   u1SubServiceNum        */
        NULL_PTR,       NULL_PTR,                   Dcm_Dsd_stIdx000ESesChk,    Dcm_Dsd_stIdx000ESubService,    (uint8)0x86U,   (boolean)TRUE,      (uint8)0U,          (uint8)1U,          (uint8)5U
    }
};

/* Table of Dcm_Dsd_stService Index */
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0004_ServiceIndex[11] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0000U,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0004U,
    (uint8)0x0005U,
    (uint8)0x0006U,
    (uint8)0x0007U,
    (uint8)0x0008U,
    (uint8)0x0009U,
    (uint8)0x000AU
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0005_ServiceIndex[11] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x000BU,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0004U,
    (uint8)0x0005U,
    (uint8)0x0006U,
    (uint8)0x0007U,
    (uint8)0x0008U,
    (uint8)0x0009U,
    (uint8)0x000AU
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0006_ServiceIndex[8] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x000CU,
    (uint8)0x000DU,
    (uint8)0x0003U,
    (uint8)0x0005U,
    (uint8)0x0008U,
    (uint8)0x000EU,
    (uint8)0x0009U,
    (uint8)0x000AU
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0007_ServiceIndex[11] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x0000U,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0004U,
    (uint8)0x0005U,
    (uint8)0x0006U,
    (uint8)0x0007U,
    (uint8)0x0008U,
    (uint8)0x0009U,
    (uint8)0x000AU
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0008_ServiceIndex[11] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x000BU,
    (uint8)0x0001U,
    (uint8)0x0002U,
    (uint8)0x0003U,
    (uint8)0x0004U,
    (uint8)0x0005U,
    (uint8)0x0006U,
    (uint8)0x0007U,
    (uint8)0x0008U,
    (uint8)0x0009U,
    (uint8)0x000AU
};
static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsd_PduId0009_ServiceIndex[8] = 
{
    /* Index of Dcm_Dsd_stService */
    (uint8)0x000BU,
    (uint8)0x000DU,
    (uint8)0x0003U,
    (uint8)0x0005U,
    (uint8)0x0008U,
    (uint8)0x000EU,
    (uint8)0x0009U,
    (uint8)0x000AU
};

CONST(AB_83_ConstV Dcm_DsdType, DCM_CONFIG_DATA) Dcm_Dsd_stConfigSet =
{
    /* bReqMfrNotifyEnabled     bReqSplrNotifyEnabled   ptMfrIndNotify              ptMfrConfNotify             ptSplrIndNotify             ptSplrConfNotify */
    (boolean)FALSE,             (boolean)TRUE,          NULL_PTR,                   NULL_PTR,                   Dcm_Dsd_SplrIndNotify,      NULL_PTR,
    /* stServiceTable */
    {
        /* u2Id             u1ServiceNum,         ptServiceIdx  */
        {  (uint16)0x0004U, (uint8)11U,           Dcm_Dsd_PduId0004_ServiceIndex },
        {  (uint16)0x0005U, (uint8)11U,           Dcm_Dsd_PduId0005_ServiceIndex },
        {  (uint16)0x0006U, (uint8)8U,            Dcm_Dsd_PduId0006_ServiceIndex },
        {  (uint16)0x0007U, (uint8)11U,           Dcm_Dsd_PduId0007_ServiceIndex },
        {  (uint16)0x0008U, (uint8)11U,           Dcm_Dsd_PduId0008_ServiceIndex },
        {  (uint16)0x0009U, (uint8)8U,            Dcm_Dsd_PduId0009_ServiceIndex }
    }
};

CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Mfrindnotify_Num = (uint8)DCM_D_MFRINDNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Mfrconfnotify_Num = (uint8)DCM_D_MFRCONFNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Splrindnotify_Num = (uint8)DCM_D_SPLRINDNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Splrconfnotify_Num = (uint8)DCM_D_SPLRCONFNOTIFY_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Servicetable_Num = (uint8)DCM_D_SERVICETABLE_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1SupportObdSystem = DCM_DSD_OBDSYS_NONOBD;
CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsd_bNoSuppressNegResIMLOIFToOBDClient = (boolean)FALSE;
CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsd_bNoSuppressNegResToUDSClient = (boolean)FALSE;

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
/*  v5-5-0         :2023-10-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
