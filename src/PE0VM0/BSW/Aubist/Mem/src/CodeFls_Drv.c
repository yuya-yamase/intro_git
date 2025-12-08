/* CodeFls_Drv_c                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "../inc/CodeFls.h"
#include "../inc/CodeFls_Internal.h"
#include "../inc/CodeFls_Drv.h"
#include "../inc/CodeFls_Device.h"
#include "../inc/CodeFls_Reg.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sSwitchModeCheck
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint16, AUTOMATIC) u2Mode
);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sSetSelfPrg
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint32, AUTOMATIC) u4SetVal
);
static FUNC(void, MEM_CODE) CodeFls_Drv_sClearStatus
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
static FUNC(void, MEM_CODE) CodeFls_Drv_sSetProtect
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint32, AUTOMATIC) u4Mode
);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckTagAreaUpdatePre(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckHwAreaCVA(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckHwAreaSVA(void);
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckHwAreaBVA(void);
static FUNC(uint8, MEM_CODE) CodeFls_Drv_sSearchErrorAddress
(
    VAR(uint32, AUTOMATIC) u4CheckAddr,
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

/* SFR address definition for MEM */ /* MISRA DEVIATION */ /* Casting between a object pointer and a generic integer type */
static CONST(AB_83_ConstV st_CodeFls_RegType, MEM_CONST) CODEFLS_STS_REG =
{
    (uint32*)CODEFLS_U4_REGADD_FLMDCNT,                     /* pu4FLMDCNT       FLMD Control Register                                   */
    (uint32*)CODEFLS_U4_REGADD_IDST,                        /* pu4IDST          ID Authentication Status Register                       */
    (uint32*)CODEFLS_U4_REGADD_CFMAPSTT,                    /* pu4CFMAPSTT      Code Flash Memory Mapping Mode Status Register          */
    (uint8*)CODEFLS_U4_REGADD_FSWASTAT_0,                   /* pu1FSWASTAT      Switch Area Status Register                             */
    {   /* FACI Register Structure */
        /* FACI0 */
        {
            (uint8*)CODEFLS_U4_FLASH_ACCESS_CMD_AREA0,      /* pu1CMDAREA       FACI command-issuing area:1byte                         */
            (uint32*)CODEFLS_U4_FLASH_ACCESS_CMD_AREA0,     /* pu4CMDAREA       FACI command-issuing area:4byte                         */
            (uint8*)CODEFLS_U4_REGADD_FPMON_0,              /* pu1FPMON         Flash Pin Monitor Register                              */
            (uint8*)CODEFLS_U4_REGADD_FASTAT_0,             /* pu1FASTAT        Flash Access Status Register                            */
            (uint8*)CODEFLS_U4_REGADD_FAEINT_0,             /* pu1FAEINT        Flash Access Error Interrupt Enable Register            */
            (uint32*)CODEFLS_U4_REGADD_FSADDR_0,            /* pu4FSADDR        Flash Command Start Address Register                    */
            (uint32*)CODEFLS_U4_REGADD_FEADDR_0,            /* pu4FEADDR        Flash Command End Address Register                      */
            (uint16*)CODEFLS_U4_REGADD_FCVAPROT_0,          /* pu2FCVAPROT      Code Flash Valid Area Protection Register               */
            (uint32*)CODEFLS_U4_REGADD_FSTATR_0,            /* pu4FSTATR        Flash Status Register                                   */
            CODEFLS_U4_REGADD_FSTATR_0,                     /* u4FSTATRADD      Flash Status Register:Address                           */
            (uint16*)CODEFLS_U4_REGADD_FENTRYR_0,           /* pu2FENTRYR       Flash Programming/Erasure Mode Entry Register           */
            CODEFLS_U4_REGADD_FENTRYR_0,                    /* u4FENTRYRADD     Flash Programming/Erasure Mode Entry Register:Address   */
            (uint16*)CODEFLS_U4_REGADD_FSUINITR_0,          /* pu2FSUINITR      Flash Sequencer Set-up Initialize Register              */
            (uint8*)CODEFLS_U4_READDR_FRTEINT_0,            /* pu1FRTEINT       FACI Reset Transfer Warning Interrupt Enable Register   */
            (uint16*)CODEFLS_U4_REGADD_FECCTMD_0,           /* pu2FECCTMD       Flash ECC Test Mode Register                            */
            (uint32*)CODEFLS_U4_REGADD_FHVE3FP0,            /* pu4FHVE3         FHVE3 ontrol Register                                   */
            (uint32*)CODEFLS_U4_REGADD_FHVE15FP0,           /* pu4FHVE15        FHVE15 ontrol Register                                  */
            (uint16*)CODEFLS_U4_REGADD_FCPSR_0              /* pu4FCPSR         Flash Sequencer Process Switch Register                 */
        },
        /* FACI1 */
        {
            (uint8*)CODEFLS_U4_FLASH_ACCESS_CMD_AREA1,      /* pu1CMDAREA       FACI command-issuing area:1byte                         */
            (uint32*)CODEFLS_U4_FLASH_ACCESS_CMD_AREA1,     /* pu4CMDAREA       FACI command-issuing area:4byte                         */
            (uint8*)CODEFLS_U4_REGADD_FPMON_1,              /* pu1FPMON         Flash Pin Monitor Register                              */
            (uint8*)CODEFLS_U4_REGADD_FASTAT_1,             /* pu1FASTAT        Flash Access Status Register                            */
            (uint8*)CODEFLS_U4_REGADD_FAEINT_1,             /* pu1FAEINT        Flash Access Error Interrupt Enable Register            */
            (uint32*)CODEFLS_U4_REGADD_FSADDR_1,            /* pu4FSADDR        Flash Command Start Address Register                    */
            (uint32*)CODEFLS_U4_REGADD_FEADDR_1,            /* pu4FEADDR        Flash Command End Address Register                      */
            (uint16*)CODEFLS_U4_REGADD_FCVAPROT_1,          /* pu2FCVAPROT      Code Flash Valid Area Protection Register               */
            (uint32*)CODEFLS_U4_REGADD_FSTATR_1,            /* pu4FSTATR        Flash Status Register                                   */
            CODEFLS_U4_REGADD_FSTATR_1,                     /* u4FSTATRADD      Flash Status Register:Address                           */
            (uint16*)CODEFLS_U4_REGADD_FENTRYR_1,           /* pu2FENTRYR       Flash Programming/Erasure Mode Entry Register           */
            CODEFLS_U4_REGADD_FENTRYR_1,                    /* u4FENTRYRADD     Flash Programming/Erasure Mode Entry Register:Address   */
            (uint16*)CODEFLS_U4_REGADD_FSUINITR_1,          /* pu2FSUINITR      Flash Sequencer Set-up Initialize Register              */
            (uint8*)CODEFLS_U4_READDR_FRTEINT_1,            /* pu1FRTEINT       FACI Reset Transfer Warning Interrupt Enable Register   */
            (uint16*)CODEFLS_U4_REGADD_FECCTMD_1,           /* pu2FECCTMD       Flash ECC Test Mode Register                            */
            (uint32*)CODEFLS_U4_REGADD_FHVE3FP1,            /* pu4FHVE3         FHVE3 ontrol Register                                   */
            (uint32*)CODEFLS_U4_REGADD_FHVE15FP1,           /* pu4FHVE15        FHVE15 ontrol Register                                  */
            (uint16*)CODEFLS_U4_REGADD_FCPSR_1              /* pu4FCPSR         Flash Sequencer Process Switch Register                 */
        }
    },
    {   /* Authentication ID Register Structure */
        /* Customer ID A */
        {
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN0,          /* pu4CUSTIDxIN0    Customer ID x Input Register 0                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN1,          /* pu4CUSTIDxIN1    Customer ID x Input Register 1                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN2,          /* pu4CUSTIDxIN2    Customer ID x Input Register 2                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN3,          /* pu4CUSTIDxIN3    Customer ID x Input Register 3                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN4,          /* pu4CUSTIDxIN4    Customer ID x Input Register 4                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN5,          /* pu4CUSTIDxIN5    Customer ID x Input Register 5                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN6,          /* pu4CUSTIDxIN6    Customer ID x Input Register 6                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDAIN7           /* pu4CUSTIDxIN7    Customer ID x Input Register 7                          */
        },
        /* Customer ID B */
        {
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN0,          /* pu4CUSTIDxIN0    Customer ID x Input Register 0                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN1,          /* pu4CUSTIDxIN1    Customer ID x Input Register 1                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN2,          /* pu4CUSTIDxIN2    Customer ID x Input Register 2                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN3,          /* pu4CUSTIDxIN3    Customer ID x Input Register 3                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN4,          /* pu4CUSTIDxIN4    Customer ID x Input Register 4                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN5,          /* pu4CUSTIDxIN5    Customer ID x Input Register 5                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN6,          /* pu4CUSTIDxIN6    Customer ID x Input Register 6                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDBIN7           /* pu4CUSTIDxIN7    Customer ID x Input Register 7                          */
        },
        /* Customer ID C */
        {
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN0,          /* pu4CUSTIDxIN0    Customer ID x Input Register 0                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN1,          /* pu4CUSTIDxIN1    Customer ID x Input Register 1                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN2,          /* pu4CUSTIDxIN2    Customer ID x Input Register 2                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN3,          /* pu4CUSTIDxIN3    Customer ID x Input Register 3                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN4,          /* pu4CUSTIDxIN4    Customer ID x Input Register 4                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN5,          /* pu4CUSTIDxIN5    Customer ID x Input Register 5                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN6,          /* pu4CUSTIDxIN6    Customer ID x Input Register 6                          */
            (uint32*)CODEFLS_U4_REGADD_CUSTIDCIN7           /* pu4CUSTIDxIN7    Customer ID x Input Register 7                          */
        }
    },
    {   /* Configration Setting Area Register Structure */
        {
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC00,      /* pu4CSAVOFCn[0]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC08,      /* pu4CSAVOFCn[1]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC09,      /* pu4CSAVOFCn[2]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC10,      /* pu4CSAVOFCn[3]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC11,      /* pu4CSAVOFCn[4]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC12,      /* pu4CSAVOFCn[5]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC13,      /* pu4CSAVOFCn[6]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC14,      /* pu4CSAVOFCn[7]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC15,      /* pu4CSAVOFCn[8]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC16,      /* pu4CSAVOFCn[9]   VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC17,      /* pu4CSAVOFCn[10]  VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC18,      /* pu4CSAVOFCn[11]  VOF Program completion flag n for Configuration Setting Area(back side) */
            (uint32*)CODEFLS_U4_REGADD_CSAB_CSAVOFC19       /* pu4CSAVOFCn[12]  VOF Program completion flag n for Configuration Setting Area(back side) */
        }
    },
    {   /* Security Setting Area Register Structure */
        {
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC00,      /* pu4SSAVOFCn[0]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC01,      /* pu4SSAVOFCn[1]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC07,      /* pu4SSAVOFCn[2]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC08,      /* pu4SSAVOFCn[3]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC09,      /* pu4SSAVOFCn[4]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC10,      /* pu4SSAVOFCn[5]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC11,      /* pu4SSAVOFCn[6]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC12,      /* pu4SSAVOFCn[7]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC13,      /* pu4SSAVOFCn[8]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC14,      /* pu4SSAVOFCn[9]   VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC15,      /* pu4SSAVOFCn[10]  VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC16,      /* pu4SSAVOFCn[11]  VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC17,      /* pu4SSAVOFCn[12]  VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC18,      /* pu4SSAVOFCn[13]  VOF Program completion flag n for Security Setting Area(back side)     */
            (uint32*)CODEFLS_U4_REGADD_SVAB_SSAVOFC40       /* pu4SSAVOFCn[14]  VOF Program completion flag n for Security Setting Area(back side)     */
        }
    },
    {   /* Block Protection Area Register Structure */
        {
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC00,    /* pu4BPA0VOFCn[0]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC01,    /* pu4BPA0VOFCn[1]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC02,    /* pu4BPA0VOFCn[2]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC03,    /* pu4BPA0VOFCn[3]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC04,    /* pu4BPA0VOFCn[4]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC05,    /* pu4BPA0VOFCn[5]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC06,    /* pu4BPA0VOFCn[6]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC07,    /* pu4BPA0VOFCn[7]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC15,    /* pu4BPA0VOFCn[8]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC16,    /* pu4BPA0VOFCn[9]   VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC17,    /* pu4BPA0VOFCn[10]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC18,    /* pu4BPA0VOFCn[11]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC19,    /* pu4BPA0VOFCn[12]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC20,    /* pu4BPA0VOFCn[13]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC21,    /* pu4BPA0VOFCn[14]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC22,    /* pu4BPA0VOFCn[15]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC23,    /* pu4BPA0VOFCn[16]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC24,    /* pu4BPA0VOFCn[17]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC25,    /* pu4BPA0VOFCn[18]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC26,    /* pu4BPA0VOFCn[19]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC27,    /* pu4BPA0VOFCn[20]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC28,    /* pu4BPA0VOFCn[21]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC29,    /* pu4BPA0VOFCn[22]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC30,    /* pu4BPA0VOFCn[23]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC31,    /* pu4BPA0VOFCn[24]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA0B_BPA0VOFC39     /* pu4BPA0VOFCn[25]  VOF Program completion flag n for Block Protection Setting Area for FPSYS0(back side) */
        },
        {
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC00,    /* pu4BPA1VOFCn[0]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC01,    /* pu4BPA1VOFCn[1]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC02,    /* pu4BPA1VOFCn[2]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC03,    /* pu4BPA1VOFCn[3]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC04,    /* pu4BPA1VOFCn[4]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC05,    /* pu4BPA1VOFCn[5]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC06,    /* pu4BPA1VOFCn[6]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC07,    /* pu4BPA1VOFCn[7]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC16,    /* pu4BPA1VOFCn[8]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC17,    /* pu4BPA1VOFCn[9]   VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC18,    /* pu4BPA1VOFCn[10]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC19,    /* pu4BPA1VOFCn[11]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC20,    /* pu4BPA1VOFCn[12]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC21,    /* pu4BPA1VOFCn[13]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC22,    /* pu4BPA1VOFCn[14]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC23,    /* pu4BPA1VOFCn[15]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC24,    /* pu4BPA1VOFCn[16]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC25,    /* pu4BPA1VOFCn[17]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC26,    /* pu4BPA1VOFCn[18]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC27,    /* pu4BPA1VOFCn[19]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC28,    /* pu4BPA1VOFCn[20]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC29,    /* pu4BPA1VOFCn[21]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC30,    /* pu4BPA1VOFCn[22]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
            (uint32*)CODEFLS_U4_REGADD_BVA1B_BPA1VOFC31     /* pu4BPA1VOFCn[23]  VOF Program completion flag n for Block Protection Setting Area for FPSYS1(back side) */
        }
    },
    {   /* Swith Area(front side) Register Structure */
        (uint32*)CODEFLS_U4_REGADD_SWAF_CVA,                /* pu4CVA           Configuration setting Valid Area(front side)               */
        (uint32*)CODEFLS_U4_REGADD_SWAF_SVA,                /* pu4SVA           Security setting Valid Area(front side)                    */
        (uint32*)CODEFLS_U4_REGADD_SWAF_BVA0,               /* pu4BVA0          Block protection setting Valid Area for FPSYS0(front side) */
        (uint32*)CODEFLS_U4_REGADD_SWAF_BVA1                /* pu4BVA1          Block protection setting Valid Area for FPSYS1(front side) */
    },
    {   /* Swith Area(back side) Register Structure */
        (uint32*)CODEFLS_U4_REGADD_SWAB_ANPC,               /* pu4AnPC          Area n Program Complete Flag(back side)                    */
        (uint32*)CODEFLS_U4_REGADD_SWAB_CVA,                /* pu4CVA           Configuration setting Valid Area(back side)                */
        (uint32*)CODEFLS_U4_REGADD_SWAB_SVA,                /* pu4SVA           Security setting Valid Area(back side)                     */
        (uint32*)CODEFLS_U4_REGADD_SWAB_BVA0,               /* pu4BVA0          Block protection setting Valid Area for FPSYS0(back side)  */
        (uint32*)CODEFLS_U4_REGADD_SWAB_BVA1                /* pu4BVA1          Block protection setting Valid Area for FPSYS1(back side)  */
    },
    {   /* TAG Area Register Structure */
        (uint32*)CODEFLS_U4_REGADD_TAG_VAPC                 /* pu4VAPC          VAF Program Complete Flag                                  */
    },
    {   /* LTSC Register Structure */
        (uint32*)CODEFLS_U4_REGADD_LTSC0_TCS,               /* pu4LTSCnTCS      LTSC Timer Counter Start Register                          */
        (uint32*)CODEFLS_U4_REGADD_LTSC0_CNTL               /* pu4LTSCnCNTL     LTSC Timer Counter Register L                              */
    }
};

/* Configration Setting Area Write Area */
static CONST(AB_83_ConstV uint32, MEM_CONST) CODEFLS_U4_CSAWRITE_ADDR[CODEFLS_U1_WRITEADD_AREA_NUM][CODEFLS_CSA_AREA_NUM] =
{
    { CODEFLS_U4_WRITEADD_CSAB_AREA14, CODEFLS_U4_WRITEADD_CSAF_AREA14 },   /* OPBT Change Area                     */
    { CODEFLS_U4_WRITEADD_CSAB_AREA00, CODEFLS_U4_WRITEADD_CSAF_AREA00 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA08, CODEFLS_U4_WRITEADD_CSAF_AREA08 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA09, CODEFLS_U4_WRITEADD_CSAF_AREA09 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA10, CODEFLS_U4_WRITEADD_CSAF_AREA10 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA11, CODEFLS_U4_WRITEADD_CSAF_AREA11 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA12, CODEFLS_U4_WRITEADD_CSAF_AREA12 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA13, CODEFLS_U4_WRITEADD_CSAF_AREA13 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA15, CODEFLS_U4_WRITEADD_CSAF_AREA15 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA16, CODEFLS_U4_WRITEADD_CSAF_AREA16 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA17, CODEFLS_U4_WRITEADD_CSAF_AREA17 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA18, CODEFLS_U4_WRITEADD_CSAF_AREA18 },   /* Configration Setting Area Write Area */
    { CODEFLS_U4_WRITEADD_CSAB_AREA19, CODEFLS_U4_WRITEADD_CSAF_AREA19 }    /* Configration Setting Area Write Area */
};

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MEM_START_SEC_CODE
#include <Mem_MemMap.h>

/****************************************************************************/
/* Function Name | CodeFls_Drv_ResetInitr                                   */
/* Description   | Set the Flash Sequencer Configuration Initialization     */
/*               | register to a reset value.                               */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_ResetInitr
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aFrdy;

    /* Check the status of the flash sequencer */
    u1aFrdy = CodeFls_Drv_CheckReady(u1FaciNum);

    /* Check rusult is CODEFLS_U1_TRUE */
    if( CODEFLS_U1_TRUE == u1aFrdy )
    {
        /* Initializing the Flash Sequencer Configuration Initialization Register */
        *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FSUINITR) = (CODEFLS_U2_REGBIT_FSUINITR_RESET + CODEFLS_U2_REGBIT_FSUINITR_KEY);
    }
    else
    {
        /* Do Nothing */
    }
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_GetFlashMode                                 */
/* Description   | Get flash sequencer mode.                                */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/* Return Value  | CODEFLS_U2_MODE_CPE     : Code Flash P/E Mode            */
/*               | CODEFLS_U2_MODE_DPE     : Data Flash P/E Mode            */
/*               | CODEFLS_U2_MODE_USER    : Read Mode                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint16, MEM_CODE) CodeFls_Drv_GetFlashMode
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(uint16, AUTOMATIC) u2aFlashMode;

    /* Read the Flash P/E Mode Entry Register */
    u2aFlashMode = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FENTRYR);
    u2aFlashMode &= (CODEFLS_U2_MODE_DPE + CODEFLS_U2_MODE_CPE);

    return(u2aFlashMode);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_SwitchModeStart                              */
/* Description   | Switch flash sequencer mode.                             */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum       : FACI Number                        */
/*               | [IN]u2Mode          : Flash Sequencer Mode               */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_SwitchModeStart
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint16, AUTOMATIC) u2Mode
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC)  u1aRet;
    VAR(uint32, AUTOMATIC)              u4aFSTATR;
    VAR(uint16, AUTOMATIC)              u2aFENTRYR;
    VAR(uint8, AUTOMATIC)              u1aMapMode;
    VAR(volatile uint16, AUTOMATIC)     u2aDummy;

    /* Set return value to E_OK */
    u1aRet = E_OK;

    /* Get map mode */
    u1aMapMode = CodeFls_Drv_GetMapMode();

    /* Switch to Destination Mode is CODEFLS_U2_MODE_USER */
    if( CODEFLS_U2_MODE_USER == u2Mode )
    {
        /* FSTATR Read */
        u4aFSTATR = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSTATR);

        /* If the FSTATR register indicates a specific error */
        if( CODEFLS_U4_REGBIT_FSTATR_NOERR != (u4aFSTATR & (CODEFLS_U4_REGBIT_FSTATR_ERSERR +
                                                            CODEFLS_U4_REGBIT_FSTATR_PRGERR +
                                                            CODEFLS_U4_REGBIT_FSTATR_ILGLERR)) )
        {
            /* Flush status clear */
            CodeFls_Drv_sClearStatus(u1FaciNum);
        }
        else
        {
            /* Do Nothing */
        }

        /* Protect Settings */
        CodeFls_Drv_sSetProtect(u1FaciNum, CODEFLS_U4_REGBIT_FHVE_RESET);
    }
    else
    {
        /* Get flash sequencer operating mode */
        u2aFENTRYR = CodeFls_Drv_GetFlashMode(u1FaciNum);

        /* Already in Flash P/E mode */
        if( CODEFLS_U2_MODE_USER != u2aFENTRYR )
        {
            /* Set return value to E_NOT_OK */
            u1aRet = E_NOT_OK;
        }
        else
        {
            /* Reset FACI Command Processing Start/End Address */
            *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSADDR) = CODEFLS_U4_REGBIT_FSADDR_RESET;
            *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FEADDR) = CODEFLS_U4_REGBIT_FEADDR_RESET;

            /* Switch to Destination Mode is CODEFLS_U2_MODE_CPE */
            if( CODEFLS_U2_MODE_CPE == u2Mode )
            {
                /* Set FLMD to self-programming permission */
                u1aRet = CodeFls_Drv_sSetSelfPrg(u1FaciNum, CODEFLS_U4_REGBIT_FLMDCNT_SFWE);

                /* Self-programming permission settings and double map mode */
                if( ((uint8)STD_ON == CODEFLS_DEVCFG_DATA.PermitSetting->Permit) &&
                    (CODEFLS_U1_MAPMODE_DOUBLE == u1aMapMode) )
                {
                    /* Set FCVAPROT to self-programming permission enable */
                    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FCVAPROT) = CODEFLS_U2_REGBIT_FCVAPROT_ENA;
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
    }

    /* Return to this point E_OK */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* Switch the Flash Sequencer Operating Mode */
        *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FENTRYR) = (u2Mode + CODEFLS_U2_REGBIT_FENTRY_KEY);

        /* FENTRYR Dummy Read */
        u2aDummy = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FENTRYR);
        /* Check Mode Switching */
        u1aRet = CodeFls_Drv_sSwitchModeCheck(u1FaciNum, u2Mode);

        /* Switch to Destination Mode is CODEFLS_U2_MODE_USER */
        if( CODEFLS_U2_MODE_USER == u2Mode )
        {
            /* Self-programming permission settings and double map mode */
            if( ((uint8)STD_ON == CODEFLS_DEVCFG_DATA.PermitSetting->Permit) &&
                (CODEFLS_U1_MAPMODE_DOUBLE == u1aMapMode) )
            {
                /* Set FCVAPROT to self-programming permission disable */
                *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FCVAPROT) = CODEFLS_U2_REGBIT_FCVAPROT_DIS;
            }
            else
            {
                /* Do Nothing */
            }

            /* Do not check the results because hardware error is nothing in read mode */
            (void)CodeFls_Drv_sSetSelfPrg(u1FaciNum, CODEFLS_U4_REGBIT_FLMDCNT_RESET);
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_ForcedStop                                   */
/* Description   | Issue a Forced Stop command.                             */
/* Preconditions | -                                                        */
/* Parameters    | [IN] u1FaciNum      : FACI Number                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_ForcedStop
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    VAR(uint8, AUTOMATIC)              u1aCheckTimeOut;
    VAR(Std_ReturnType, AUTOMATIC)  u1aRet;
    VAR(CodeFls_GetRegParam, AUTOMATIC) staParam;

    /* Set return value to E_OK */
    u1aRet = E_OK;

    /* Write a Forced Stop command to the FACI command issuance area */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_FORCED_STOP;

    /*************************************************************************************/
    /* Forced Stop timeout period (40usec or greater)                                    */
    /* 1 loop clock = Calculated from Loop processing in the CodeFls_Drv_GetRegReady_Asm */
    /*   Setting Value = (40us * CPU operating frequency) / 1 loop clock                 */
    /*************************************************************************************/
    /* Set the monitoring register(FSTATR) and monitoring bit(FRDY) */
    staParam.u4Addr = CODEFLS_STS_REG.FACI[u1FaciNum].u4FSTATRADD;
    staParam.u4Bit  = CODEFLS_U4_REGBIT_FSTATR_FRDY;

    /* Calculate timeout value */
    staParam.u4Time = CodeFls_Drv_Div_Asm((CODEFLS_U4_FORCEDSTOP_TIME * (uint32)CodeFls_u2gCpuFreq), CODEFLS_U4_REGREADY_CLKCNT);

    /* Monitor until the Forced Stop Command process completes */
    u1aCheckTimeOut = CodeFls_Drv_GetRegReady_Asm(&staParam);

    /* Timeout occurred */
    if( CODEFLS_U1_TRUE != u1aCheckTimeOut )
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_InitRegister                                 */
/* Description   | Initialize all FACI flash-related registers.             */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1Request       : Initialization request type        */
/*               | [IN]u1FaciMax       : Maximum number of FACI             */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_InitRegister
(
    VAR(uint8, AUTOMATIC) u1Request,
    VAR(uint8, AUTOMATIC) u1FaciMax
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    /* Number of FaciMax */
    for( u1aLoopCnt = CODEFLS_U1_FACI_0; u1aLoopCnt < u1FaciMax; u1aLoopCnt++ )
    {
        /* Flash sequencer configuration initialization using the flash sequencer configuration initialization register */
        /* == Target Register ==                                                                                        */
        /*  FSADDR_n                                                                                                    */
        /*  FEADDR_n                                                                                                    */
        /*  FCVAPROT_n                                                                                                  */
        /*  FENTRYR_n                                                                                                   */
        /*  FBCCNT_n                                                                                                    */
        /*  FCPSR_n                                                                                                     */
        *(CODEFLS_STS_REG.FACI[u1aLoopCnt].pu2FSUINITR) = (CODEFLS_U2_REGBIT_FSUINITR_SUINIT + CODEFLS_U2_REGBIT_FSUINITR_KEY);

        /* Initializing the Flash Sequencer Configuration Initialization Register */
        *(CODEFLS_STS_REG.FACI[u1aLoopCnt].pu2FSUINITR) = (CODEFLS_U2_REGBIT_FSUINITR_RESET + CODEFLS_U2_REGBIT_FSUINITR_KEY);

        /* Flash Sequencer Termination Error Interrupt Allow Register Initialization */
        *(CODEFLS_STS_REG.FACI[u1aLoopCnt].pu1FAEINT) = CODEFLS_U1_REGBIT_FAEINT_RESET;

        /* FACI Reset Transfer Error Interrupt Allow Register Initialization */
        *(CODEFLS_STS_REG.FACI[u1aLoopCnt].pu1FRTEINT) = CODEFLS_U1_REGBIT_FRTEINT_DISABLE;

        /* Protect Settings - FHVE15/FHVE3 Initialization */
        CodeFls_Drv_sSetProtect(u1aLoopCnt, CODEFLS_U4_REGBIT_FHVE_RESET);

        /* Initializing the Flash ECC Test Mode Register */
        *(CODEFLS_STS_REG.FACI[u1aLoopCnt].pu2FECCTMD) = (CODEFLS_U2_REGBIT_FECCTMD_RESET + CODEFLS_U2_REGBIT_FECCTMD_KEY);
    }

    /* Initializing the FLMD Control Register */
    *(CODEFLS_STS_REG.pu4FLMDCNT) = CODEFLS_U4_REGBIT_FLMDCNT_RESET;

    /* u1Request is CODEFLS_U1_REQ_DEINIT */
    if( CODEFLS_U1_REQ_DEINIT == u1Request )
    {
        /* Number of Auth id */
        for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_AUTHID_NUM; u1aLoopCnt++ )
        {
            /* Initializing the Self-Programming ID Input Register */
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN0) = CODEFLS_U4_REGBIT_CUSTID_RESET;
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN1) = CODEFLS_U4_REGBIT_CUSTID_RESET;
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN2) = CODEFLS_U4_REGBIT_CUSTID_RESET;
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN3) = CODEFLS_U4_REGBIT_CUSTID_RESET;
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN4) = CODEFLS_U4_REGBIT_CUSTID_RESET;
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN5) = CODEFLS_U4_REGBIT_CUSTID_RESET;
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN6) = CODEFLS_U4_REGBIT_CUSTID_RESET;
            *(CODEFLS_STS_REG.ID[u1aLoopCnt].pu4CUSTIDxIN7) = CODEFLS_U4_REGBIT_CUSTID_RESET;
        }
    }
    else
    {
        /* Do Nothing */
    }
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_ResetRegister                                */
/* Description   | Reconfigure the flash-related registers before issuing   */
/*               | the FACI command.                                        */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_ResetRegister
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Initialization of the flash sequencer configuration initialization register - the setting register value is preserved */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FSUINITR) = (CODEFLS_U2_REGBIT_FSUINITR_RESET + CODEFLS_U2_REGBIT_FSUINITR_KEY);

    /* Initializing the Flash ECC Test Mode Register */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu2FECCTMD) = (CODEFLS_U2_REGBIT_FECCTMD_RESET + CODEFLS_U2_REGBIT_FECCTMD_KEY);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_VerifyID                                     */
/* Description   | Controls the connection of the dedicated flash memory    */
/*               | programmer during serial programming, On-chip debugging  */
/*               | connection, and sets the ID used for writes code flash   */
/*               | memory by self-programming.                              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_VerifyID(void)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC)              u1aLoopCnt;
    VAR(uint8, AUTOMATIC)              u1aAuthIdType;
    VAR(uint32, AUTOMATIC)              u4aAuthResult;
    VAR(uint32, AUTOMATIC)              u4aAuthIdArray[CODEFLS_U1_AUTHID_CNT];
    VAR(uint32, AUTOMATIC)              u4aCompbit;
    VAR(volatile uint32, AUTOMATIC)     u4aDummy;
    VAR(Std_ReturnType, AUTOMATIC)  u1aRet;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aIDST;

    /* Set return value to E_OK */
    u1aRet = E_OK;

    /* AuthIdInfoNum with config information */
    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfoNum; u1aLoopCnt++ )
    {
        /* Get ID type for authentication from config */
        u1aAuthIdType = CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthIdType;

        /* Get ID value for authentication from config */
        u4aAuthIdArray[CODEFLS_IDX_0] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_0]  << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_1]  << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_2]  << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_3]);
        u4aAuthIdArray[CODEFLS_IDX_1] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_4]  << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_5]  << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_6]  << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_7]);
        u4aAuthIdArray[CODEFLS_IDX_2] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_8]  << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_9]  << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_10] << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_11]);
        u4aAuthIdArray[CODEFLS_IDX_3] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_12] << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_13] << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_14] << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_15]);
        u4aAuthIdArray[CODEFLS_IDX_4] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_16] << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_17] << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_18] << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_19]);
        u4aAuthIdArray[CODEFLS_IDX_5] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_20] << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_21] << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_22] << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_23]);
        u4aAuthIdArray[CODEFLS_IDX_6] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_24] << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_25] << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_26] << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_27]);
        u4aAuthIdArray[CODEFLS_IDX_7] = (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_28] << CODEFLS_BITSHIFT_24)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_29] << CODEFLS_BITSHIFT_16)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_30] << CODEFLS_BITSHIFT_8)
                                        + (uint32)((uint32)CODEFLS_DEVCFG_DATA.AuthIdSetting->AuthIdInfo[u1aLoopCnt].AuthId[CODEFLS_IDX_31]);

        /* Identity Authentication */
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN0) = u4aAuthIdArray[CODEFLS_IDX_0];
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN1) = u4aAuthIdArray[CODEFLS_IDX_1];
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN2) = u4aAuthIdArray[CODEFLS_IDX_2];
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN3) = u4aAuthIdArray[CODEFLS_IDX_3];
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN4) = u4aAuthIdArray[CODEFLS_IDX_4];
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN5) = u4aAuthIdArray[CODEFLS_IDX_5];
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN6) = u4aAuthIdArray[CODEFLS_IDX_6];
        *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN7) = u4aAuthIdArray[CODEFLS_IDX_7];

        /* Dummy read to wait for register update of ID authentication result */
        u4aDummy = *(CODEFLS_STS_REG.ID[u1aAuthIdType].pu4CUSTIDxIN7);

        /* Reading ID authentication results */
        pu4aIDST = CODEFLS_STS_REG.pu4IDST;
        u4aAuthResult = *(pu4aIDST);

        /* Comparison bit generation */
        u4aCompbit = (uint32)(CODEFLS_U4_VAL_1 << (CODEFLS_U1_BITSHIFT_IDST_CUSTID + u1aAuthIdType) );

        /* Identity authentication results mismatch */
        if( u4aCompbit == (u4aAuthResult & u4aCompbit) )
        {
            /* Set return value to E_NOT_OK */
            u1aRet = E_NOT_OK;
            break;
        }
        else
        {
            /* Do Nothing */
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_EraseOp                                      */
/* Description   | Execute Erase.                                           */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_EraseOp
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Set the erase start address in FSADDR */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSADDR)  = CodeFls_stgMultiOpInfo.u4OpAddr;
    /* Execute the erase command */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_ERASE;
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;

    /* Operation address is less than 64K block start address */
    if( (CodeFls_stgMultiOpInfo.u4BankAddr + CODEFLS_U4_CF1_ADDR_64K_START) > CodeFls_stgMultiOpInfo.u4OpAddr )
    {
        /* Update the operation information to the next block address for 16K blocks */
        CodeFls_stgMultiOpInfo.u4OpAddr += CODEFLS_U4_SMALL_BLOCK_SIZE;
        /* Check remaining size */
        if( CODEFLS_U4_SMALL_BLOCK_SIZE <= CodeFls_stgMultiOpInfo.u4OpSize )
        {
            /* Subtract the erased size from the remaining size */
            CodeFls_stgMultiOpInfo.u4OpSize -= CODEFLS_U4_SMALL_BLOCK_SIZE;
        }
        else
        {
            /* Set remaining size to zero */
            CodeFls_stgMultiOpInfo.u4OpSize = CODEFLS_U4_VAL_0;
        }
    }
    else
    {
        /* Update the operation information to the next block address for 64K blocks */
        CodeFls_stgMultiOpInfo.u4OpAddr += CODEFLS_U4_BLOCK_SIZE;
        /* Check remaining size */
        if( CODEFLS_U4_BLOCK_SIZE <= CodeFls_stgMultiOpInfo.u4OpSize )
        {
            /* Subtract the erased size from the remaining size */
            CodeFls_stgMultiOpInfo.u4OpSize -= CODEFLS_U4_BLOCK_SIZE;
        }
        else
        {
            /* Set remaining size to zero */
            CodeFls_stgMultiOpInfo.u4OpSize = CODEFLS_U4_VAL_0;
        }
    }

    /* Copy Control Address and Size */
    CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
    CodeFls_stgMirrorArea.u4CheckSize = CodeFls_stgMultiOpInfo.u4OpSize;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_WriteOp                                      */
/* Description   | Execute Write.                                           */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_WriteOp
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC)  u1aLoopCnt;
    VAR(uint32, AUTOMATIC)  u4aTempData;
    VAR(uint32, AUTOMATIC)  u4aData;
    VAR(uint16, AUTOMATIC)  u2aIdx;

    /* Set the write start address in FSADDR */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSADDR) = CodeFls_stgMultiOpInfo.u4OpAddr;
    /* Issue Write Command */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_WRITE;
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA) = CODEFLS_U1_TRANSFERSIZE;

    /* Number of write bytes per cycle */
    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_TRANSFERSIZE; u1aLoopCnt++ )
    {
        /* Get write data from operation information */
        /* Setting Write Data to Command Area */
        u2aIdx      = (uint16)((uint16)u1aLoopCnt << CODEFLS_BITSHIFT_2) + CODEFLS_U2_VAL_3;
        u4aTempData = (uint32)(CodeFls_stgMultiOpInfo.pu1BufAddr[u2aIdx]);
        u4aData     = (uint32)(u4aTempData << CODEFLS_BITSHIFT_24);
        u2aIdx      = (uint16)((uint16)u1aLoopCnt << CODEFLS_BITSHIFT_2) + CODEFLS_U2_VAL_2;
        u4aTempData = (uint32)(CodeFls_stgMultiOpInfo.pu1BufAddr[u2aIdx]);
        u4aData    += (uint32)(u4aTempData << CODEFLS_BITSHIFT_16);
        u2aIdx      = (uint16)((uint16)u1aLoopCnt << CODEFLS_BITSHIFT_2) + CODEFLS_U2_VAL_1;
        u4aTempData = (uint32)(CodeFls_stgMultiOpInfo.pu1BufAddr[u2aIdx]);
        u4aData    += (uint32)(u4aTempData << CODEFLS_BITSHIFT_8);
        u2aIdx      = (uint16)((uint16)u1aLoopCnt << CODEFLS_BITSHIFT_2);
        u4aData    += (uint32)(CodeFls_stgMultiOpInfo.pu1BufAddr[u2aIdx]);

        *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4CMDAREA) = u4aData;
    }

    /* Command Execution */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;

    /* Update operation information to the next write data */
    CodeFls_stgMultiOpInfo.u4OpAddr  += CODEFLS_WRITE_SIZE;
    CodeFls_stgMultiOpInfo.pu1BufAddr = &CodeFls_stgMultiOpInfo.pu1BufAddr[CODEFLS_WRITE_SIZE];
    CodeFls_stgMultiOpInfo.u4OpSize  -= CODEFLS_WRITE_SIZE;

    /* Copy Control Address and Size */
    CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
    CodeFls_stgMirrorArea.pu1CheckBuf = CodeFls_stgMultiOpInfo.pu1BufAddr;
    CodeFls_stgMirrorArea.u4CheckSize = CodeFls_stgMultiOpInfo.u4OpSize;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_BlankCheckOp                                 */
/* Description   | executes the blank check.                                */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK : writing in possible - ALL blank                   */
/*               | CODEFLS_U1_BLANKCHECK_NOT_BLANK : writing in impossible  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_BlankCheckOp(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aOpRegSize;
    VAR(uint32, AUTOMATIC) u4aStartAddr;
    VAR(uint32, AUTOMATIC) u4aCheckCnt;
    VAR(uint32, AUTOMATIC) u4aCheckData;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    /* Set return value to E_OK */
    u1aRet = E_OK;

    /* Operation size is greater than or equal to blank check maximum value */
    if( CODEFLS_U4_BLANKCHECK_ALIGN_SIZE < CodeFls_stgMultiOpInfo.u4OpSize )
    {
        /* Set job size to blank maximum value */
        u4aOpRegSize = CODEFLS_U4_BLANKCHECK_ALIGN_SIZE;
    }
    else
    {
        /* Set job size to the value of the operation information */
        u4aOpRegSize = CodeFls_stgMultiOpInfo.u4OpSize;
    }

    /* Change blank check address */
    u4aStartAddr = CODEFLS_U4_FSADDR_UP_ADDR + CodeFls_stgMultiOpInfo.u4OpAddr;

    /* The check number of times calculating */
    u4aCheckCnt = CodeFls_Drv_Div_Asm(u4aOpRegSize, CODEFLS_U1_BLCHK_OFFSET_ADDR);

    /* Calculated number of checks */
    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < u4aCheckCnt; u1aLoopCnt++ )
    {
        /* Blank check area reading */
        u4aCheckData = (*(uint32*)(u4aStartAddr));

        /* The checked area is not blank */
        if( CODEFLS_U1_VAL_0 == (u4aCheckData & CODEFLS_U4_BLCHK_BF_MASK) )
        {
            /* Set return value to CODEFLS_U1_BLANKCHECK_NOT_BLANK */
            u1aRet = CODEFLS_U1_BLANKCHECK_NOT_BLANK;
            break;
        }

        /* Update operation information to the next check address - 32 bytes every */
        u4aStartAddr += CODEFLS_U1_BLCHK_OFFSET_ADDR;
    }

    /* The checked area is all blank */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* Update operation information to the next write data */
        CodeFls_stgMultiOpInfo.u4OpAddr  += u4aOpRegSize;
        CodeFls_stgMultiOpInfo.u4OpSize  -= u4aOpRegSize;

        /* Copy Control Address and Size */
        CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
        CodeFls_stgMirrorArea.u4CheckSize = CodeFls_stgMultiOpInfo.u4OpSize;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_SuspendOp                                    */
/* Description   | executes the suspension.                                 */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum              : FACI Number                 */
/* Return Value  | E_OK                       : Successful completion       */
/*               | E_NOT_OK                   : Failed                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_SuspendOp
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aFSTATR;
    VAR(uint8, AUTOMATIC) u1aFASTAT;

    /* FASTAT read */
    u1aFASTAT = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1FASTAT);

    /* CMDLK bit is 0 */
    if( CODEFLS_U1_REGBIT_FASTAT_CMDLK != (u1aFASTAT & CODEFLS_U1_REGBIT_FASTAT_CMDLK) )
    {
        /* FSTATR read */
        u4aFSTATR = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSTATR);

        /* SUSRDY bit is 1 */
        if( CODEFLS_U4_REGBIT_FSTATR_SUSRDY == (u4aFSTATR & CODEFLS_U4_REGBIT_FSTATR_SUSRDY) )
        {
            /* FRDY bit is 0 */
            if( CODEFLS_U4_REGBIT_FSTATR_FRDY != (u4aFSTATR & CODEFLS_U4_REGBIT_FSTATR_FRDY) )
            {
                /* Set return value to E_NOT_OK */
                u1aRet = E_NOT_OK;
            }
            else
            {
                /* Set return value to E_OK */
                u1aRet = E_OK;
            }
        }
        else
        {
            /* FRDY bit is 0 */
            if( CODEFLS_U4_REGBIT_FSTATR_FRDY != (u4aFSTATR & CODEFLS_U4_REGBIT_FSTATR_FRDY) )
            {
                /* Set return value to E_NOT_OK */
                u1aRet = E_NOT_OK;
            }
            else
            {
                /* Set return value to EOK */
                u1aRet = E_OK;
            }
        }
    }
    else
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_ErrRefresh                                   */
/* Description   | By reading the FACI command publication area, it makes a */
/*               | command lock occur and makes flash sequencer processing  */
/*               | stop and issues a status clearance command and cancels   */
/*               | a command pending-lock, an error.                        */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_ErrRefresh
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(volatile uint8, AUTOMATIC) u1aDummy;

    /* It makes a command pending-lock occur. */
    u1aDummy = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA);  /* Reading of the FACI command publication area */
    u1aDummy = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA);  /* Dummy read */

    /* Executes a status clearance command. */
    CodeFls_Drv_sClearStatus(u1FaciNum);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_CheckReady                                   */
/* Description   | Check the FRDY bit of a flash status registr.            */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum       : FACI Number                        */
/* Return Value  | CODEFLS_U1_TRUE         : FRDY bit =1                    */
/*               | CODEFLS_U1_FALSE        : FRDY bit =0                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Drv_CheckReady
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aFSTATR;

    /* reads a flash status registr */
    u4aFSTATR = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSTATR);

    /* FRDY bit is 1 */
    if( CODEFLS_U4_REGBIT_FSTATR_FRDY == (u4aFSTATR & CODEFLS_U4_REGBIT_FSTATR_FRDY) )
    {
        /* Set return value to CODEFLS_U1_TRUE */
        u1aRet = CODEFLS_U1_TRUE;
    }
    else
    {
        /* Set return value to CODEFLS_U1_FALSE */
        u1aRet = CODEFLS_U1_FALSE;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_CheckError                                   */
/* Description   | Checks the error of a flash sequencer.                   */
/* Preconditions | -                                                        */
/* Parameters    | [IN] u1FaciNum      : FACI Number                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_CheckError
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aFSTATR;

    /* reads a flash status registr */
    u4aFSTATR = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSTATR);

    /* Flash Sequencer Detects Errors */
    if( CODEFLS_U4_REGBIT_FSTATR_NOERR != (u4aFSTATR & CODEFLS_U4_FSTATR_MASK_ERR) )
    {
        /* Issues a forced stop command */
        /* Do not check the results because it is a recovery process after an error occurs. */
        (void)CodeFls_Drv_ForcedStop(u1FaciNum);
        /* Transfers to a read mode */
        (void)CodeFls_Drv_SwitchModeStart(u1FaciNum, CODEFLS_U2_MODE_USER);
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }
    else
    {
        /* Set return value to E_OK */
        u1aRet = E_OK;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_GetClockValue                                */
/* Description   | It get the CPLLCLK clock frequency                       */
/*               | from Configuration Information.                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_GetClockValue(void)
{
    /* CPU clock frequency save to RAM. */
    CodeFls_u2gCpuFreq = CODEFLS_DEVCFG_DATA.ProductSetting->Clock;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_GetMapMode                                   */
/* Description   | Get Map Mode of a cord flash.                            */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_U1_MAPMODE_SINGLE : Single Map Mode              */
/*               | CODEFLS_U1_MAPMODE_DOUBLE : Double Map Mode              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Drv_GetMapMode(void)
{
    /* Variable Declarations */
    VAR(uint32, AUTOMATIC) u4CFMAPSTT;
    VAR(uint8, AUTOMATIC) u1aRet;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aCFMAPSTT;

    /* CFMAPSTT read */
    pu4aCFMAPSTT = CODEFLS_STS_REG.pu4CFMAPSTT;
    u4CFMAPSTT = *(pu4aCFMAPSTT);

    /* Map mode is double map mode */
    if( CODEFLS_U4_REGBIT_CFMAPSTT_DOUBLE == (u4CFMAPSTT & CODEFLS_U4_MASK_CFMAPSTT) )
    {
        /* Set return value to CODEFLS_U1_MAPMODE_DOUBLE */
        u1aRet = CODEFLS_U1_MAPMODE_DOUBLE;
    }
    else
    {
        /* Set return value to CODEFLS_U1_MAPMODE_SINGLE */
        u1aRet = CODEFLS_U1_MAPMODE_SINGLE;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_SetCsaWriteDataChengeArea                    */
/*               | For a valid area switch                                  */
/* Description   | Set the necessary write data for a cord flash            */
/*               | valid area switch.                                       */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_SetCsaWriteDataChengeArea(void)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aLoopCnt;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aAddr;

    /* reading of an area including OPBT13 of the target of the establishment */
    pu4aAddr = (uint32*)CODEFLS_U4_CSAWRITE_ADDR[CODEFLS_IDX_0][CODEFLS_CSA_AREA_FRONT]; /* MISRA DEVIATION */ /* Casting between a object pointer and a generic integer type */

    /* Size of CodeFls_u4gWriteBuffer */
    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_TRANSFERSIZE_HWAREA; u1aLoopCnt++ )
    {
        /* Copy Configration Setting Area Write Area information to CodeFls_u4gWriteBuffer */
        CodeFls_u4gWriteBuffer[u1aLoopCnt] = pu4aAddr[u1aLoopCnt];
    }

    /* Reverses OPBT13.DBMAPSW0 */
    CodeFls_u4gWriteBuffer[CODEFLS_CSA_OPBT13_IDX] = (uint32)(CodeFls_u4gWriteBuffer[CODEFLS_CSA_OPBT13_IDX] ^ CODEFLS_U4_CSA_OPBT13_BIT_DBMAPSW0);

    /* The product type of the configuration information is U2A16 */
    if( CODEFLS_PRODUCT_U2A16 == CODEFLS_DEVCFG_DATA.ProductSetting->ProductType )
    {
        /* Reverses OPBT13.DBMAPSW1 */
        CodeFls_u4gWriteBuffer[CODEFLS_CSA_OPBT13_IDX] = (uint32)(CodeFls_u4gWriteBuffer[CODEFLS_CSA_OPBT13_IDX] ^ CODEFLS_U4_CSA_OPBT13_BIT_DBMAPSW1);
    }
    else
    {
        /* Do Nothing */
    }

    /* Update operation information */
    CodeFls_stgMultiOpInfo.u4OpAddr = CODEFLS_U4_CSAWRITE_ADDR[CODEFLS_IDX_0][CODEFLS_CSA_AREA_BACK];

    /* Set operation mirror information */
    CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_SetCsaWriteDataOtherArea                     */
/* Description   | It establishes the writing in data except a necessary    */
/*               | area for a cord flash valid area switch.                 */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_U1_TRUE     : The Possible Write Area is existed */
/*               | CODEFLS_U1_FALSE    : The Possible Write Area is nothing */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Drv_SetCsaWriteDataOtherArea(void)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;
    VAR(uint8, AUTOMATIC) u1aNextIdx;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aAddr;

    /* Set return value to CODEFLS_U1_FALSE */
    u1aRet = CODEFLS_U1_FALSE;

    /* Size of Configration Setting Area Write Area */
    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < (CODEFLS_U1_WRITEADD_AREA_NUM - CODEFLS_U1_VAL_1); u1aLoopCnt++ )
    {
        /* Configration Setting Area Write Area and the start address of the operation information match */
        if( CODEFLS_U4_CSAWRITE_ADDR[u1aLoopCnt][CODEFLS_CSA_AREA_BACK] == CodeFls_stgMultiOpInfo.u4OpAddr )
        {
            /* it writes and targets the next element */
            u1aNextIdx = u1aLoopCnt + CODEFLS_U1_VAL_1;
            /* Set return value to CODEFLS_U1_TRUE */
            u1aRet = CODEFLS_U1_TRUE;
            break;
        }
        else
        {
            /* Do Nothing */
        }
    }

    /* Return value is CODEFLS_U1_TRUE */
    if( CODEFLS_U1_TRUE == u1aRet )
    {
        /* It does the reading of the area of the target of the establishment */
        pu4aAddr = (uint32*)CODEFLS_U4_CSAWRITE_ADDR[u1aNextIdx][CODEFLS_CSA_AREA_FRONT]; /* MISRA DEVIATION */ /* Casting between a object pointer and a generic integer type */

        /* Size of CodeFls_u4gWriteBuffer */
        for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_TRANSFERSIZE_HWAREA; u1aLoopCnt++ )
        {
            /* Copy Configration Setting Area Write Area information to CodeFls_u4gWriteBuffer */
            CodeFls_u4gWriteBuffer[u1aLoopCnt] = pu4aAddr[u1aLoopCnt];
        }

        /* Update operation information */
        CodeFls_stgMultiOpInfo.u4OpAddr = CODEFLS_U4_CSAWRITE_ADDR[u1aNextIdx][CODEFLS_CSA_AREA_BACK];

        /* Set operation mirror information */
        CodeFls_stgMirrorArea.u4CheckAddr = CodeFls_stgMultiOpInfo.u4OpAddr;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_SetSwitchWriteData                           */
/* Description   | Set the necessary write data for a cord flash            */
/*               | valid area switch.                                       */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_SetSwitchWriteData(void)
{
    /* Variable Declarations */
    VAR(uint32, AUTOMATIC) u4aCVA;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aCVA;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aSVA;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aBVA0;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aBVA1;

    /* CVA read */
    pu4aCVA = CODEFLS_STS_REG.SWAF.pu4CVA;
    u4aCVA = *(pu4aCVA);

    /* CVA is front side */
    if( CODEFLS_U4_REGBIT_SWA_CVA_AREA0 == u4aCVA )
    {
        /* Set CODEFLS_U4_REGBIT_SWA_CVA_AREA1 to Write Data */
        CodeFls_u4gWriteBuffer[CODEFLS_IDX_0] = CODEFLS_U4_REGBIT_SWA_CVA_AREA1;
    }
    else
    {
        /* Set CODEFLS_U4_REGBIT_SWA_CVA_AREA0 to Write Data */
        CodeFls_u4gWriteBuffer[CODEFLS_IDX_0] = CODEFLS_U4_REGBIT_SWA_CVA_AREA0;
    }

    /* Get setting value from front side of switch Area */
    pu4aSVA = CODEFLS_STS_REG.SWAF.pu4SVA;
    pu4aBVA0 = CODEFLS_STS_REG.SWAF.pu4BVA0;
    pu4aBVA1 = CODEFLS_STS_REG.SWAF.pu4BVA1;
    CodeFls_u4gWriteBuffer[CODEFLS_IDX_1] = *(pu4aSVA);
    CodeFls_u4gWriteBuffer[CODEFLS_IDX_2] = *(pu4aBVA0);
    CodeFls_u4gWriteBuffer[CODEFLS_IDX_3] = *(pu4aBVA1);
    CodeFls_u4gWriteBuffer[CODEFLS_IDX_4] = CODEFLS_U4_SWA_RESERVED;
    CodeFls_u4gWriteBuffer[CODEFLS_IDX_5] = CODEFLS_U4_SWA_RESERVED;
    CodeFls_u4gWriteBuffer[CODEFLS_IDX_6] = CODEFLS_U4_SWA_RESERVED;
    CodeFls_u4gWriteBuffer[CODEFLS_IDX_7] = CODEFLS_U4_SWA_RESERVED;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_CheckSwitchArea                              */
/* Description   | It establishes the writing in data except a necessary    */
/*               | area for a cord flash valid area switch.                 */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_U1_TRUE : Switch Area(back side) written         */
/*               | CODEFLS_U1_FALSE: Switch Area(back side) not written     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Drv_CheckSwitchArea(void)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aAnPC;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aAnPC;

    /* Set return value to CODEFLS_U1_FALSE */
    u1aRet = CODEFLS_U1_FALSE;

    /* Read AnPC(back side) */
    pu4aAnPC = CODEFLS_STS_REG.SWAB.pu4AnPC;
    u4aAnPC = *(pu4aAnPC);

    /* Switch Area(back side) written */
    if( CODEFLS_U4_REGBIT_SWA_ANPC_COMP == u4aAnPC )
    {
        /* Set return value to CODEFLS_U1_TRUE */
        u1aRet = CODEFLS_U1_TRUE;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_CsaEraseOp                                   */
/* Description   | Executes the erasure of Configration Setting Area        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_CsaEraseOp(void)
{
    /* Configration Setting Area erase command execute */
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4FSADDR) = CODEFLS_U4_ERASEADD_CSAB;
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_PROPERTY_ERASE;
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_CsaWriteOp                                   */
/* Description   | Executes the write of Configration Setting Area          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_CsaWriteOp(void)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    /* Configration Setting Area write command set */
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4FSADDR) = CodeFls_stgMultiOpInfo.u4OpAddr;
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_PROPERTY_WRITE;
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_TRANSFERSIZE_HWAREA;

    /* Size of CodeFls_u4gWriteBuffer */
    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_TRANSFERSIZE_HWAREA; u1aLoopCnt++ )
    {
        /* Set CodeFls_u4gWriteBuffer information in the command issuance area */
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4CMDAREA) = CodeFls_u4gWriteBuffer[u1aLoopCnt];
    }

    /* Command execute */
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_SwitchEraseOp                                */
/* Description   | Executes the erasure of Switch Area                      */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_SwitchEraseOp(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aVAPC;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aVAPC;

    /* Set return value to E_NOT_OK */
    u1aRet = E_NOT_OK;

    /* VAPC read */
    pu4aVAPC = CODEFLS_STS_REG.TAG.pu4VAPC;
    u4aVAPC = *(pu4aVAPC);

    /* Value of VAPC is TAG Area written */
    if( CODEFLS_U4_REGBIT_TAG_VAPC_VALUE == u4aVAPC )
    {
        /* Switch Area Erase command execute */
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4FSADDR) = CODEFLS_U4_ERASEADD_SWAB;
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_SWITCH_ERASE;
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;

        /* Set return value to E_OK */
        u1aRet = E_OK;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_SwitchWriteOp                                */
/* Description   | Executes the write of Switch Area                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_SwitchWriteOp(void)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    /* Switch Area write command set */
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4FSADDR) = CODEFLS_U4_WRITEADD_SWAB_CVA;
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_SWITCH_WRITE;
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_TRANSFERSIZE_HWAREA;

    /* Size of CodeFls_u4gWriteBuffer */
    for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_TRANSFERSIZE_HWAREA; u1aLoopCnt++ )
    {
        /* Set CodeFls_u4gWriteBuffer information in the command issuance area */
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4CMDAREA) = CodeFls_u4gWriteBuffer[u1aLoopCnt];
    }

    /* Command execute */
    *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_TagEraseOp                                   */
/* Description   | Executes the erasure of TAG Area                         */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_TagEraseOp(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    /* Checks whether or not the erasure and the update of TAG Area are possible */
    u1aRet = CodeFls_Drv_sCheckTagAreaUpdatePre();

    /* Erasure and update of TAG Area possible */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* TAG Area Erase command execute */
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4FSADDR) = CODEFLS_U4_ERASEADD_TAG;
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_TAG_ERASE;
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_TagUpdateOp                                  */
/* Description   | Executes the update of TAG Area                          */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_TagUpdateOp(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;

    /* Checks whether or not the erasure and the update of TAG Area are possible */
    u1aRet = CodeFls_Drv_sCheckTagAreaUpdatePre();

    /* Erasure and update of TAG Area possible */
    if( (Std_ReturnType)E_OK == u1aRet )
    {
        /* TAG Area Update command execute */
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu4FSADDR) = CODEFLS_U4_WRITEADD_TAG_VAF;
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_TAG_UPDATE;
        *(CODEFLS_STS_REG.FACI[CODEFLS_U1_FACI_0].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_EXE;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_FinishSwitchValidArea                        */
/* Description   | It checks whether or not a flash memory measuring area   */
/*               | change ended normally.                                   */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_FinishSwitchValidArea(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aFSWASTAT;
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu1aFSWASTAT;

    /* Set return value to E_NOT_OK */
    u1aRet = E_NOT_OK;

    /* Check FSWASTAT_0.SWAS */
    pu1aFSWASTAT = CODEFLS_STS_REG.pu1FSWASTAT;
    u1aFSWASTAT = *(pu1aFSWASTAT);

    /* Flash memory valid area switch end */
    if( CODEFLS_U1_REGBIT_FSWASTAT_SWAS != (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_SWAS) )
    {
        /* Set return value to E_OK */
        u1aRet = E_OK;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_StartTimer                                   */
/* Description   | Start the LTSC timer.                                    */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_StartTimer(void)
{
    /* Long-Term System Counter Start */
    *(CODEFLS_STS_REG.LTSC.pu4LTSCnTCS) = CODEFLS_U4_REGBIT_LTSC0_TS;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_GetCounterValue                              */
/* Description   | Get the LTSC timer value (Return microseconds).          */
/* Preconditions | -                                                        */
/* Parameters    | [OUT]LTSC timer value buffer address                     */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, MEM_CODE) CodeFls_Drv_GetCounterValue
(
    P2VAR(uint32, AUTOMATIC, MEM_APPL_DATA) u4aLtscCnt
)
{
    /* Variable Declarations */
    VAR(uint32, AUTOMATIC) u4aTempCnt;

    /* Get Long-Term System Counter */
    u4aTempCnt = (uint32)(*(CODEFLS_STS_REG.LTSC.pu4LTSCnCNTL));

    /* Long-Term System Counters of 80 or higher */
    if( u4aTempCnt >= CODEFLS_U4_CLK_HSB )
    {
        /* Set the calculated value as the timer value */
        *u4aLtscCnt = CodeFls_Drv_Div_Asm(u4aTempCnt, CODEFLS_U4_CLK_HSB);
    }
    else
    {
        /* Set 0 as the timer value */
        *u4aLtscCnt = CODEFLS_U4_VAL_0;
    }
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_GetEccErrorAddressRom1bit                    */
/* Description   | This confirms the occurrence of an 1bit ECC error in the */
/*               | target ROM area.                                         */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_U1_ECC_CHECK_OK        : ECC error not occurring */
/*               | CODEFLS_U1_ECC_CHECK_ERROR_1BIT  :                       */
/*               |                               ECC error occurrence(1bit) */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Drv_GetEccErrorAddressRom1bit
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aResult;
    VAR(uint32, AUTOMATIC) u4aRegSER;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;
    VAR(uint32, AUTOMATIC) u4aCheckBit;
    VAR(uint32, AUTOMATIC) u4aErrAddr;
    VAR(uint8, AUTOMATIC) u1aSearch;
    VAR(uint32, AUTOMATIC) u4gPEID;

    /* Set return value to CODEFLS_U1_ECC_CHECK_OK */
    u1aResult = CODEFLS_U1_ECC_CHECK_OK;

    /* Reads the CF_SERSTR register */
    u4aRegSER = CODEFLS_U4_REG_CF_SERSTR; /* MISRA DEVIATION */ /* Casting between a object pointer and a generic integer type */

    u4gPEID = CodeFls_Drv_GetPEID_Asm();

    /* 1bit error */
    if( CODEFLS_U4_CF_SERSTR_RESET != (CODEFLS_U4_CF_SERSTR_ALL & u4aRegSER) )
    {
        /* Number of bits in the CF_SERSTR */
        for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_VAL_4; u1aLoopCnt++ )
        {
            /* Get Checked Bits */
            u4aCheckBit = (uint32)(CODEFLS_U4_VAL_1 << u1aLoopCnt);

            /* CF_SERSTR register has a check target bit of 1 and Code Flash n-th 1-bit error address register value is 0 or 0x08000000 */
            if( u4aCheckBit == (u4aCheckBit & u4aRegSER) )
            {
                if( u4gPEID == CODEFLS_U4_PEID_PE0 )
                {
                    if( (CODEFLS_U4_CF_EADR_INF_FT_PE0 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) ||
                        (CODEFLS_U4_CF_EADR_INF_LD_PE0 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) )
                    {
                        u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt) & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                        /* Address Check */
                        u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                        if( CODEFLS_U1_TRUE == u1aSearch )
                        {
                            /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_1BIT */
                            u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_1BIT;
                        }
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                else if( u4gPEID == CODEFLS_U4_PEID_PE1 )
                {
                    if( (CODEFLS_U4_CF_EADR_INF_FT_PE1 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) ||
                        (CODEFLS_U4_CF_EADR_INF_LD_PE1 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) )
                    {
                        u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt) & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                        /* Address Check */
                        u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                        if( CODEFLS_U1_TRUE == u1aSearch )
                        {
                            /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_1BIT */
                            u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_1BIT;
                        }
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                else if( u4gPEID == CODEFLS_U4_PEID_PE2 )
                {
                    if( (CODEFLS_U4_CF_EADR_INF_FT_PE2 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) ||
                        (CODEFLS_U4_CF_EADR_INF_LD_PE2 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) )
                    {
                        u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt) & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                        /* Address Check */
                        u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                        if( CODEFLS_U1_TRUE == u1aSearch )
                        {
                            /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_1BIT */
                            u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_1BIT;
                        }
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                else if( u4gPEID == CODEFLS_U4_PEID_PE3 )
                {
                    if( (CODEFLS_U4_CF_EADR_INF_FT_PE3 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) ||
                        (CODEFLS_U4_CF_EADR_INF_LD_PE3 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt))) )
                    {
                        u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_nSEADR((uint32)u1aLoopCnt) & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                        /* Address Check */
                        u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                        if( CODEFLS_U1_TRUE == u1aSearch )
                        {
                            /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_1BIT */
                            u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_1BIT;
                        }
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                else
                {
                    /* Do Nothing */
                }

                if( CODEFLS_U1_ECC_CHECK_ERROR_1BIT == u1aResult )
                {
                    break;
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aResult);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_GetEccErrorAddressRom2bit                    */
/* Description   | This confirms the occurrence of an 2bit ECC error in the */
/*               | target ROM area.                                         */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | CODEFLS_U1_ECC_CHECK_OK        : ECC error not occurring */
/*               | CODEFLS_U1_ECC_CHECK_ERROR_2BIT  :                       */
/*               |                               ECC error occurrence(2bit) */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, MEM_CODE) CodeFls_Drv_GetEccErrorAddressRom2bit
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    /* Variable Declarations */
    VAR(uint8, AUTOMATIC) u1aResult;
    VAR(uint32, AUTOMATIC) u4aRegDER;
    VAR(uint32, AUTOMATIC) u4aErrAddr;
    VAR(uint8, AUTOMATIC) u1aSearch;
    VAR(uint32, AUTOMATIC) u4gPEID;

    /* Set return value to CODEFLS_U1_ECC_CHECK_OK */
    u1aResult = CODEFLS_U1_ECC_CHECK_OK;

    /* Reads the CF_DERSTR register */
    u4aRegDER = CODEFLS_U4_REG_CF_DERSTR; /* MISRA DEVIATION */ /* Casting between a object pointer and a generic integer type */

    u4gPEID = CodeFls_Drv_GetPEID_Asm();

    /* CF_DERSTR register is not 0 and Code Flash 1st fatal error address register value is 0 or 0x08000000 */
    if( CODEFLS_U4_CF_DERSTR_RESET != (CODEFLS_U4_CF_DERSTR_ALL & u4aRegDER) )
    {
        if( u4gPEID == CODEFLS_U4_PEID_PE0 )
        {
            if( (CODEFLS_U4_CF_EADR_INF_FT_PE0 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) ||
                (CODEFLS_U4_CF_EADR_INF_LD_PE0 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) )
            {
                u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_00DEADR & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                /* Address Check */
                u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                if( CODEFLS_U1_TRUE == u1aSearch )
                {
                    /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_2BIT */
                    u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_2BIT;
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
        else if( u4gPEID == CODEFLS_U4_PEID_PE1 )
        {
            if( (CODEFLS_U4_CF_EADR_INF_FT_PE1 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) ||
                (CODEFLS_U4_CF_EADR_INF_LD_PE1 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) )
            {
                u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_00DEADR & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                /* Address Check */
                u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                if( CODEFLS_U1_TRUE == u1aSearch )
                {
                    /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_2BIT */
                    u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_2BIT;
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
        else if( u4gPEID == CODEFLS_U4_PEID_PE2 )
        {
            if( (CODEFLS_U4_CF_EADR_INF_FT_PE2 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) ||
                (CODEFLS_U4_CF_EADR_INF_LD_PE2 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) )
            {
                u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_00DEADR & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                /* Address Check */
                u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                if( CODEFLS_U1_TRUE == u1aSearch )
                {
                    /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_2BIT */
                    u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_2BIT;
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
        else if( u4gPEID == CODEFLS_U4_PEID_PE3 )
        {
            if( (CODEFLS_U4_CF_EADR_INF_FT_PE3 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) ||
                (CODEFLS_U4_CF_EADR_INF_LD_PE3 == (CODEFLS_U4_CF_EADR_INF_MASK & CODEFLS_U4_REG_CF_00DEADR)) )
            {
                u4aErrAddr = (uint32)((CODEFLS_U4_REG_CF_00DEADR & CODEFLS_U4_CF_EADR_MASK) << CODEFLS_U4_VAL_2);

                /* Address Check */
                u1aSearch = CodeFls_Drv_sSearchErrorAddress(u4aErrAddr, TargetAddr, TargetSize);
                if( CODEFLS_U1_TRUE == u1aSearch )
                {
                    /* Set return value to CODEFLS_U1_ECC_CHECK_ERROR_2BIT */
                    u1aResult = CODEFLS_U1_ECC_CHECK_ERROR_2BIT;
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aResult);
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | CodeFls_Drv_sSwitchModeCheck                             */
/* Description   | It confirms that a flash sequencer mode change           */
/*               | completed.                                               */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum       : FACI Number                        */
/*               | [IN]u2Mode          : Flash sequencer mode               */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sSwitchModeCheck
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint16, AUTOMATIC) u2Mode
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint16, AUTOMATIC) u2aFENTRYR;
    VAR(CodeFls_GetRegParam, AUTOMATIC) staParam;
    VAR(uint8, AUTOMATIC)              u1aMapMode;

    /* Set return value to E_OK */
    u1aRet = E_OK;

    /* Get map mode */
    u1aMapMode = CodeFls_Drv_GetMapMode();

    /* Switch to Destination Mode is CODEFLS_U2_MODE_USER */
    if( CODEFLS_U2_MODE_USER == u2Mode )
    {
        /* Get flash sequencer mode */
        u2aFENTRYR = CodeFls_Drv_GetFlashMode(u1FaciNum);
    }
    else
    {
        /**************************************************************************************/
        /* P/E mode switch timeout period                                                     */
        /* 1 loop clock = Calculated from Loop processing in the CodeFls_Drv_GetRegReady16bit_Asm */
        /* Setting Value = (timeout period * CPU operating frequency) / 1 loop clock          */
        /**************************************************************************************/
        /* Set the monitoring register(FENTRYR) and monitoring bit(mode) */
        staParam.u4Addr = CODEFLS_STS_REG.FACI[u1FaciNum].u4FENTRYRADD;
        staParam.u4Bit  = (uint32)u2Mode;
        /* Timeout period calculation */
        staParam.u4Time = CodeFls_Drv_Div_Asm((CODEFLS_U4_ICUCPE_TIME * (uint32)CodeFls_u2gCpuFreq), CODEFLS_U4_REGREADY16BIT_CLKCNT);
        /* The occurrence of a time-out is judged in the result of the next flash sequencer mode acquisition */
        CodeFls_Drv_GetRegReady16bit_Asm(&staParam);

        /* Get flash sequencer mode */
        u2aFENTRYR = CodeFls_Drv_GetFlashMode(u1FaciNum);
    }

    /* Flash sequencer mode change Success */
    if( u2aFENTRYR == u2Mode )
    {
        /* Flash sequencer mode is CODEFLS_U2_MODE_USER */
        if( CODEFLS_U2_MODE_USER == u2aFENTRYR )
        {
            if( ((uint8)STD_OFF == CODEFLS_DEVCFG_DATA.PermitSetting->Permit) &&
                (CODEFLS_U1_MAPMODE_DOUBLE == u1aMapMode) )
            {
                /* No process */
            }
            else
            {
                u1aRet = CodeFls_Drv_Clear_Cache_Asm();
            }
        }
        /* In case of the cord flash P/E mode, the data flash P/E mode, it cancels the protection */
        else
        {
            /* cancels the protection */
            CodeFls_Drv_sSetProtect(u1FaciNum, CODEFLS_U4_REGBIT_FHVE_CNT);
        }
    }
    else
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sSetSelfPrg                                  */
/* Description   | It establishes FLMD and does the permission,             */
/*               | the prohibiting establishment of a self programming.     */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum       : FACI Number                        */
/*               | [IN]u4SetVal        : FLMD set value                     */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sSetSelfPrg
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint32, AUTOMATIC) u4SetVal
)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint8, AUTOMATIC) u1aFpmon;
    VAR(uint8, AUTOMATIC) u1aCompVal;

    /* Set return value to E_NOT_OK */
    u1aRet = E_NOT_OK;

    /* Set FLMD */
    *(CODEFLS_STS_REG.pu4FLMDCNT) = u4SetVal;

    /* Set value for the comparison with a flash terminal monitor register to CODEFLS_U1_REGBIT_FPMON_RESET */
    u1aCompVal = CODEFLS_U1_REGBIT_FPMON_RESET;

    /* FLMD set value is CODEFLS_U4_REGBIT_FLMDCNT_SFWE */
    if( CODEFLS_U4_REGBIT_FLMDCNT_SFWE == u4SetVal )
    {
        /* Set value for the comparison with a flash terminal monitor register to CODEFLS_U1_REGBIT_FPMON_SFWE */
        u1aCompVal = CODEFLS_U1_REGBIT_FPMON_SFWE;
    }
    else
    {
        /* Do Nothing */
    }

    /* Read flash terminal monitor register */
    u1aFpmon = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1FPMON);

    /* Compare value and flash terminal monitor register match */
    if( u1aCompVal == (u1aFpmon & CODEFLS_U1_REGBIT_FPMON_SFWE) )
    {
        /* Set return value to E_OK */
        u1aRet = E_OK;
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sClearStatus                                 */
/* Description   | It clears the status of a flash sequencer.               */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) CodeFls_Drv_sClearStatus
(
    VAR(uint8, AUTOMATIC) u1FaciNum
)
{
    /* Variable Declarations */
    VAR(uint32, AUTOMATIC) u4aFSTATR;
    VAR(uint8, AUTOMATIC) u1aFASTAT;

    /* Reading of a flash status registr value */
    u4aFSTATR = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FSTATR);

    /* Illegal command error occur */
    if( CODEFLS_U4_REGBIT_FSTATR_ILGLERR == (u4aFSTATR & CODEFLS_U4_REGBIT_FSTATR_ILGLERR) )
    {
        /* Reading of a flash access status registr */
        u1aFASTAT = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1FASTAT);

        /* CMDLK bit is 0 */
        if( CODEFLS_U1_REGBIT_FASTAT_CMDLK != u1aFASTAT )
        {
            /* It returns an occurrence time against Memory Access, CFAE and DFAE to 0. */
            *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1FASTAT) = CODEFLS_U1_REGBIT_FASTAT_CMDLK;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    /* It issues a status clearance command */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu1CMDAREA) = CODEFLS_U1_FLASH_ACCESS_CMD_CLEARSTAT;
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sSetProtect                                  */
/* Description   | Using the establishment of FHVE15/FHVE3 control-         */
/*               | register,it establishes, cancels the protection.         */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u1FaciNum           : FACI Number                    */
/*               | [IN]u4Mode              : FHVE15/3 set value             */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, MEM_CODE) CodeFls_Drv_sSetProtect
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint32, AUTOMATIC) u4Mode
)
{
    /* Variable Declarations */
    VAR(volatile uint32, AUTOMATIC) u4aDummy;

    /* It writes the value specified by an argument in FHVE15 */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FHVE15) = u4Mode;
    /* It writes the value specified by an argument in FHVE3 */
    *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FHVE3) = u4Mode;

    /* It implements dummy-read and syncp as synchronization handling */
    u4aDummy = *(CODEFLS_STS_REG.FACI[u1FaciNum].pu4FHVE3);
    /* Syncp command execute */
    CodeFls_Drv_Syncp_Asm();
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sCheckTagAreaUpdatePre                       */
/* Description   | Check to implement before the erasure/update of TAG      */
/*               | Area.                                                    */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckTagAreaUpdatePre(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aAnPC;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aAnPC;

    /* Set return value to E_NOT_OK */
    u1aRet = E_NOT_OK;

    /* reads AnPC (back side) */
    pu4aAnPC = CODEFLS_STS_REG.SWAB.pu4AnPC;
    u4aAnPC = *(pu4aAnPC);

    /* It checks whether or not Switch Area (back side) has written notes */
    if( CODEFLS_U4_REGBIT_SWA_ANPC_COMP == u4aAnPC )
    {
        /* It confirms the consistence of Configration Setting Area */
        u1aRet = CodeFls_Drv_sCheckHwAreaCVA();

        /* The configuration setting in the configuration setting area is normal */
        if( (Std_ReturnType)E_OK == u1aRet )
        {
            /* It confirms the consistence of Security Setting Area */
            u1aRet = CodeFls_Drv_sCheckHwAreaSVA();

            /* The configuration setting in the Security Setting Area is normal */
            if( (Std_ReturnType)E_OK == u1aRet )
            {
                /* It confirms the consistence of Block Protection Area */
                u1aRet = CodeFls_Drv_sCheckHwAreaBVA();
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sCheckHwAreaCVA                              */
/* Description   | It checks whether or not Configration Setting Area that  */
/*               | becomes effective after a change is normal.              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckHwAreaCVA(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aCVA;
    VAR(uint8, AUTOMATIC) u1aFSWASTAT;
    VAR(uint32, AUTOMATIC) u4aCSAVOFCn;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aCVA;
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu1aFSWASTAT;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aCSAVOFCn;
    VAR(uint8, AUTOMATIC) u1aIsChenge;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    /* Set return value to E_OK */
    u1aRet = E_OK;
    /* Set change flag to CODEFLS_U1_FALSE */
    u1aIsChenge = CODEFLS_U1_FALSE;

    /* Reads CVA (back side) */
    pu4aCVA = CODEFLS_STS_REG.SWAB.pu4CVA;
    u4aCVA = *(pu4aCVA);

    /* Reads Switch Area Status Register */
    pu1aFSWASTAT = CODEFLS_STS_REG.pu1FSWASTAT;
    u1aFSWASTAT = *(pu1aFSWASTAT);

    /* Configuration setting Valid Area is A55A5AA5 */
    if( CODEFLS_U4_REGBIT_SWA_CVA_AREA0 == u4aCVA )
    {
        /* CFGVA bit is 0 */
        if( CODEFLS_U1_REGBIT_FSWASTAT_CFGVA != (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_CFGVA) )
        {
            /* it supposes that it is normal because it doesn't change */
            /* Do Nothing */
        }
        else
        {
            /* Set change flag to CODEFLS_U1_TRUE */
            u1aIsChenge = CODEFLS_U1_TRUE;
        }
    }
    else if( CODEFLS_U4_REGBIT_SWA_CVA_AREA1 == u4aCVA )
    {/* Configuration setting Valid Area is 5AA5A55A */
        /* CFGVA bit is 1 */
        if( CODEFLS_U1_REGBIT_FSWASTAT_CFGVA == (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_CFGVA) )
        {
            /* it supposes that it is normal because it doesn't change */
            /* Do Nothing */
        }
        else
        {
            /* Set change flag to CODEFLS_U1_TRUE */
            u1aIsChenge = CODEFLS_U1_TRUE;
        }
    }
    else
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }

    /* Change flag is CODEFLS_U1_TRUE */
    if( CODEFLS_U1_TRUE == u1aIsChenge )
    {
        /* Number of CSAVOFCn */
        for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_CSAVOFCN_NUM; u1aLoopCnt++ )
        {
            /* Read CSAVOFCn */
            pu4aCSAVOFCn = CODEFLS_STS_REG.CSA.pu4CSAVOFCn[u1aLoopCnt];
            u4aCSAVOFCn = *(pu4aCSAVOFCn);

            /* CSAVOFCn value is 5AA5A55A */
            if( CODEFLS_U4_REGBIT_CSA_CSAVOFCN_COMP == u4aCSAVOFCn )
            {
                /* Do Nothing */
            }
            else
            {
                /* Set return value to E_NOT_OK */
                u1aRet = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sCheckHwAreaSVA                              */
/* Description   | It checks whether or not Security Setting Area that      */
/*               | becomes effective after a change is normal.              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckHwAreaSVA(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aSVA;
    VAR(uint8, AUTOMATIC) u1aFSWASTAT;
    VAR(uint32, AUTOMATIC) u4aSSAVOFCn;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aSVA;
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu1aFSWASTAT;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aSSAVOFCn;
    VAR(uint8, AUTOMATIC) u1aIsChenge;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    /* Set return value to E_OK */
    u1aRet = E_OK;
    /* Set change flag to CODEFLS_U1_FALSE */
    u1aIsChenge = CODEFLS_U1_FALSE;

    /* Reading SVA (back side) */
    pu4aSVA = CODEFLS_STS_REG.SWAB.pu4SVA;
    u4aSVA = *(pu4aSVA);

    /* Reading Switch Area Status Register */
    pu1aFSWASTAT = CODEFLS_STS_REG.pu1FSWASTAT;
    u1aFSWASTAT = *(pu1aFSWASTAT);

    /* Security Setting Valid Area is A55A5AA5 */
    if( CODEFLS_U4_REGBIT_SWA_SVA_AREA0 == u4aSVA )
    {
        /* SECVA bit is 0 */
        if( CODEFLS_U1_REGBIT_FSWASTAT_SECVA != (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_SECVA)  )
        {
            /* it supposes that it is normal because it doesn't change */
            /* Do Nothing */
        }
        else
        {
            /* Set change flag to CODEFLS_U1_TRUE */
            u1aIsChenge = CODEFLS_U1_TRUE;
        }
    }
    else if( CODEFLS_U4_REGBIT_SWA_SVA_AREA1 == u4aSVA )
    {/* Security Setting Valid Area is 5AA5A55A */
        /* SECVA bit is 1 */
        if( CODEFLS_U1_REGBIT_FSWASTAT_SECVA == (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_SECVA) )
        {
            /* it supposes that it is normal because it doesn't change */
            /* Do Nothing */
        }
        else
        {
            /* Set change flag to CODEFLS_U1_TRUE */
            u1aIsChenge = CODEFLS_U1_TRUE;
        }
    }
    else
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }

    /* Change flag is CODEFLS_U1_TRUE */
    if( CODEFLS_U1_TRUE == u1aIsChenge )
    {
        /* Number of SSAVOFCn */
        for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_SSAVOFCN_NUM; u1aLoopCnt++ )
        {
            /* Read SSAVOFCn */
            pu4aSSAVOFCn = CODEFLS_STS_REG.SVA.pu4SSAVOFCn[u1aLoopCnt];
            u4aSSAVOFCn = *(pu4aSSAVOFCn);

            /* SSAVOFCn value is 5AA5A55A */
            if( CODEFLS_U4_REGBIT_SVA_SSAVOFCN_COMP == u4aSSAVOFCn )
            {
                /* Do Nothing */
            }
            else
            {
                /* Set return value to E_NOT_OK */
                u1aRet = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        /* Do Nothing */
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sCheckHwAreaBVA                              */
/* Description   | It checks whether or not Block Protection Area that      */
/*               | becomes effective after a change is normal.              */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | E_OK                : Successful completion              */
/*               | E_NOT_OK            : Failed                             */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_sCheckHwAreaBVA(void)
{
    /* Variable Declarations */
    VAR(Std_ReturnType, AUTOMATIC) u1aRet;
    VAR(uint32, AUTOMATIC) u4aBVA;
    VAR(uint8, AUTOMATIC) u1aFSWASTAT;
    VAR(uint32, AUTOMATIC) u4aBPAVOFCn;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aBVA0;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aBVA1;
    P2CONST(uint8, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu1aFSWASTAT;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aBPA0VOFCn;
    P2CONST(uint32, AUTOMATIC, MEM_APPL_DATA) AB_83_ConstV pu4aBPA1VOFCn;
    VAR(uint8, AUTOMATIC) u1aIsChenge;
    VAR(uint8, AUTOMATIC) u1aLoopCnt;

    /* Set return value to E_OK */
    u1aRet = E_OK;
    /* Set change flag to CODEFLS_U1_FALSE */
    u1aIsChenge = CODEFLS_U1_FALSE;

    /* Reading BVA0(back side) */
    pu4aBVA0 = CODEFLS_STS_REG.SWAB.pu4BVA0;
    u4aBVA = *(pu4aBVA0);

    /* Reading Switch Area Status Register */
    pu1aFSWASTAT = CODEFLS_STS_REG.pu1FSWASTAT;
    u1aFSWASTAT = *(pu1aFSWASTAT);

    /* Block Protection Valid Area0 is A55A5AA5 */
    if( CODEFLS_U4_REGBIT_SWA_BVA_AREA0 == u4aBVA )
    {
        /* BPVA0 bit is 0 */
        if( CODEFLS_U1_REGBIT_FSWASTAT_BPVA0 != (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_BPVA0) )
        {
            /* it supposes that it is normal because it doesn't change */
            /* Do Nothing */
        }
        else
        {
            /* Set change flag to CODEFLS_U1_TRUE */
            u1aIsChenge = CODEFLS_U1_TRUE;
        }
    }
    else if( CODEFLS_U4_REGBIT_SWA_BVA_AREA1 == u4aBVA )
    {/* Block Protection Valid Area is 5AA5A55A */
        /* BPVA0 bit is 1 */
        if( CODEFLS_U1_REGBIT_FSWASTAT_BPVA0 == (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_BPVA0) )
        {
            /* it supposes that it is normal because it doesn't change */
            /* Do Nothing */
        }
        else
        {
            /* Set change flag to CODEFLS_U1_TRUE */
            u1aIsChenge = CODEFLS_U1_TRUE;
        }
    }
    else
    {
        /* Set return value to E_NOT_OK */
        u1aRet = E_NOT_OK;
    }

    /* Change flag is CODEFLS_U1_TRUE */
    if( CODEFLS_U1_TRUE == u1aIsChenge )
    {
        /* Number of BPA0VOFCn */
        for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_BPA0VOFCN_NUM; u1aLoopCnt++ )
        {
            /* Read BPA0VOFCn */
            pu4aBPA0VOFCn = CODEFLS_STS_REG.BVA.pu4BPA0VOFCn[u1aLoopCnt];
            u4aBPAVOFCn = *(pu4aBPA0VOFCn);

            /* BPA0VOFCn value is 5AA5A55A */
            if( CODEFLS_U4_REGBIT_BVA_BPAVOFCN_COMP == u4aBPAVOFCn )
            {
                /* Do Nothing */
            }
            else
            {
                /* Set return value to E_NOT_OK */
                u1aRet = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        /* Do Nothing */
    }

    /* The product type of the configuration information is U2A16 */
    if( CODEFLS_PRODUCT_U2A16 == CODEFLS_DEVCFG_DATA.ProductSetting->ProductType )
    {
        /* Return value is E_OK */
        if( (Std_ReturnType)E_OK == u1aRet )
        {
            /* Set change flag to CODEFLS_U1_FALSE */
            u1aIsChenge = CODEFLS_U1_FALSE;

            /* Reading BVA1(back side) */
            pu4aBVA1 = CODEFLS_STS_REG.SWAB.pu4BVA1;
            u4aBVA = *(pu4aBVA1);

            /* Reading Switch Area Status Register */
            pu1aFSWASTAT = CODEFLS_STS_REG.pu1FSWASTAT;
            u1aFSWASTAT = *(pu1aFSWASTAT);

            /* Block Protection Valid Area1 is A55A5AA5 */
            if( CODEFLS_U4_REGBIT_SWA_BVA_AREA0 == u4aBVA )
            {
                /* BPVA1 bit is 0 */
                if( CODEFLS_U1_REGBIT_FSWASTAT_BPVA1 != (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_BPVA1) )
                {
                    /* it supposes that it is normal because it doesn't change */
                    /* Do Nothing */
                }
                else
                {
                    /* Set change flag to CODEFLS_U1_TRUE */
                    u1aIsChenge = CODEFLS_U1_TRUE;
                }
            }
            else if( CODEFLS_U4_REGBIT_SWA_BVA_AREA1 == u4aBVA )
            {/* Block Protection Valid Area1 is 5AA5A55A */
                /* BPVA1 bit is 1 */
                if( CODEFLS_U1_REGBIT_FSWASTAT_BPVA1 == (u1aFSWASTAT & CODEFLS_U1_REGBIT_FSWASTAT_BPVA1) )
                {
                    /* it supposes that it is normal because it doesn't change */
                    /* Do Nothing */
                }
                else
                {
                    /* Set change flag to CODEFLS_U1_TRUE */
                    u1aIsChenge = CODEFLS_U1_TRUE;
                }
            }
            else
            {
                /* Set return value to E_NOT_OK */
                u1aRet = E_NOT_OK;
            }

            /* Change flag is CODEFLS_U1_TRUE */
            if( CODEFLS_U1_TRUE == u1aIsChenge )
            {
                /* Number of BPA1VOFCn */
                for( u1aLoopCnt = CODEFLS_U1_VAL_0; u1aLoopCnt < CODEFLS_U1_BPA1VOFCN_NUM; u1aLoopCnt++ )
                {
                    /* Read BPA1VOFCn */
                    pu4aBPA1VOFCn = CODEFLS_STS_REG.BVA.pu4BPA1VOFCn[u1aLoopCnt];
                    u4aBPAVOFCn = *(pu4aBPA1VOFCn);

                    /* BPA1VOFCn is 5AA5A55A */
                    if( CODEFLS_U4_REGBIT_BVA_BPAVOFCN_COMP == u4aBPAVOFCn )
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        /* Set return value to E_NOT_OK */
                        u1aRet = E_NOT_OK;
                        break;
                    }
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* Do Nothing */
        }
    }

    return(u1aRet);
}

/****************************************************************************/
/* Function Name | CodeFls_Drv_sSearchErrorAddress                          */
/* Description   | Check if the specified address is included in the        */
/*               | detection start address to size range.                   */
/* Preconditions | -                                                        */
/* Parameters    | [IN]u4CheckAddr  : Address to be checked                 */
/*               | [IN]TargetAddr   : Start address of detection target     */
/*               | [IN]TargetSize   : Size of the detection target          */
/* Return Value  | CODEFLS_U1_TRUE  : ECC error address found               */
/*               | CODEFLS_U1_FALSE : No matching ECC error address         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, MEM_CODE) CodeFls_Drv_sSearchErrorAddress
(
    VAR(uint32, AUTOMATIC) u4CheckAddr,
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    VAR(uint8, AUTOMATIC) u1aSearch;

    u1aSearch = CODEFLS_U1_FALSE;

    /* Check if the address to be checked is included within the specified area */
    if( (TargetAddr <= u4CheckAddr) && ((TargetAddr + TargetSize) > u4CheckAddr) )
    {
        /* If the address to be checked is included within the specified area,  */
        /* end the search as "ECC error address found.                          */
        u1aSearch = CODEFLS_U1_TRUE;
    }
    return(u1aSearch);
}

#define MEM_STOP_SEC_CODE
#include <Mem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
