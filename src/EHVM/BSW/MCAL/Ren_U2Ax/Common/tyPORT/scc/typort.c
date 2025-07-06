/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : PORT Extension Interface For TOYOTA                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYPORT_C_MAJOR                          (1)
#define TYPORT_C_MINOR                          (0)
#define TYPORT_C_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "typort_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYPORT_C_MAJOR != TYPORT_H_MAJOR) || \
     (TYPORT_C_MINOR != TYPORT_H_MINOR) || \
     (TYPORT_C_PATCH != TYPORT_H_PATCH))
#error "typort.c and typort.h : source and header files are inconsistent!"
#endif

#if ((TYPORT_C_MAJOR != TYPORT_CFG_PRIVATE_H_MAJOR) || \
     (TYPORT_C_MINOR != TYPORT_CFG_PRIVATE_H_MINOR) || \
     (TYPORT_C_PATCH != TYPORT_CFG_PRIVATE_H_PATCH))
#error "typort.c and typort_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* PIC1 Unit/Channel Fix definition */
#define TYPORT_CFG_PIC1_PIC1TAUD0SEL     ((TYPORT_CFG_PIC1_TAUD0TTIN0  * BIT0)          \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN1  * BIT2)          \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN2  * BIT4)          \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN3  * BIT6)          \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN4  * BIT8)          \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN5  * BIT10)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN6  * BIT12)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN7  * BIT14)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN8  * BIT16)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN9  * BIT18)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN10 * BIT20)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN11 * BIT22)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN12 * BIT24)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN13 * BIT26)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN14 * BIT28)         \
                                        + (TYPORT_CFG_PIC1_TAUD0TTIN15 * BIT30))

#define TYPORT_CFG_PIC1_PIC1TAUD1SEL     ((TYPORT_CFG_PIC1_TAUD1TTIN0  * BIT0)          \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN1  * BIT2)          \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN2  * BIT4)          \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN3  * BIT6)          \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN4  * BIT8)          \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN5  * BIT10)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN6  * BIT12)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN7  * BIT14)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN8  * BIT16)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN9  * BIT18)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN10 * BIT20)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN11 * BIT22)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN12 * BIT24)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN13 * BIT26)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN14 * BIT28)         \
                                        + (TYPORT_CFG_PIC1_TAUD1TTIN15 * BIT30))

#define TYPORT_CFG_PIC1_PIC1TAUD2SEL     ((TYPORT_CFG_PIC1_TAUD2TTIN0  * BIT0)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN1  * BIT1)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN2  * BIT2)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN3  * BIT3)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN4  * BIT4)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN5  * BIT5)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN6  * BIT6)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN7  * BIT7)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN8  * BIT8)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN9  * BIT9)          \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN10 * BIT10)         \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN11 * BIT11)         \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN12 * BIT12)         \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN13 * BIT13)         \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN14 * BIT14)         \
                                        + (TYPORT_CFG_PIC1_TAUD2TTIN15 * BIT15))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_tyPortReleasIohold(void);
static void    vd_s_tyPortInitPic(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".TYPORT_TEXT_CODE"
/*===================================================================================================================================*/
/*  void    vd_g_tyPortPreInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_tyPortPreInit(void)
{
    
}

/*===================================================================================================================================*/
/*  void    vd_g_tyPortInit(const U1 u1_a_CFGID)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_CFGID       : Configuration ID                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_tyPortInit(const U1 u1_a_CFGID)
{
    vd_s_tyPortInitPic();
    vd_g_tyPortCalloutInit(u1_a_CFGID);
    vd_s_tyPortReleasIohold();
}

/*===================================================================================================================================*/
/*  static void    vd_s_tyPortReleasIohold(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void  vd_s_tyPortReleasIohold(void)
{
    *REG_STBC_STBCKCPROT = REG_STBC_STBCKCPROT_WRITE_ENABLE;
    *REG_STBC_IOHOLD0 = REG_STBC_RELEASE_IOBUFFERHOLD;
    *REG_STBC_IOHOLD2 = REG_STBC_RELEASE_IOBUFFERHOLD;
    *REG_STBC_STBCKCPROT = REG_STBC_STBCKCPROT_WRITE_DISABLE;
}

/*===================================================================================================================================*/
/*  static void    vd_s_tyPortInitPic(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_tyPortInitPic(void)
{
    ((volatile Pic1_TAUDnSEL_Type*)PIC1_TAUD0SEL_ADR)->unTAUDnSEL.u4Data     = (U4)TYPORT_CFG_PIC1_PIC1TAUD0SEL; /* PIC1TAUD0SEL */
    ((volatile Pic1_TAUDnSEL_Type*)PIC1_TAUD1SEL_ADR)->unTAUDnSEL.u4Data     = (U4)TYPORT_CFG_PIC1_PIC1TAUD1SEL; /* PIC1TAUD1SEL */
    ((volatile Pic1_SelbTaud2I_Type*)PIC1_TAUD2SEL_ADR)->unSelbTaud2I.u2Data = (U2)TYPORT_CFG_PIC1_PIC1TAUD2SEL; /* PIC1SELB_TAUD2I */
}
#pragma ghs section text=default

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/ 9/2025  RY       New.                                                                                               */
/*                                                                                                                                   */
/*  * RY   = Ryosuke Yamada                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
