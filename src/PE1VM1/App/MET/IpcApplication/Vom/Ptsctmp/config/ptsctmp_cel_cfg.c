/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Power-train System Coolant Temperature                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSCTMP_CEL_CFG_C_MAJOR                  (2)
#define PTSCTMP_CEL_CFG_C_MINOR                  (1)
#define PTSCTMP_CEL_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ptsctmp_cel_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PTSCTMP_CEL_CFG_C_MAJOR != PTSCTMP_CEL_CFG_H_MAJOR) || \
     (PTSCTMP_CEL_CFG_C_MINOR != PTSCTMP_CEL_CFG_H_MINOR) || \
     (PTSCTMP_CEL_CFG_C_PATCH != PTSCTMP_CEL_CFG_H_PATCH))
#error "ptsctmp_cel_cfg.c and ptsctmp_cel_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((PTSCTMP_CEL_CFG_C_MAJOR != PTSCTMP_CEL_H_MAJOR) || \
     (PTSCTMP_CEL_CFG_C_MINOR != PTSCTMP_CEL_H_MINOR) || \
     (PTSCTMP_CEL_CFG_C_PATCH != PTSCTMP_CEL_H_PATCH))
#error "ptsctmp_cel_cfg.c and ptsctmp_cel.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSCTMP_CANRX_BITMASK                    (0x01ffU) /* GATHW Signal Mask value(9bit data)                                     */
#define PTSCTMP_CANRX_BITLEN                     (5U)
#define PTSCTMP_CANRX_MASK                       (0x001fU)

#define PTSCTMP_GATHW_LSB_TO_0P01                (50U)                                       /* LSB:0.5 -> 0.01             */
#define PTSCTMP_GATHW_OFFSET                     (8000U)                                     /* OFFSE:-80 [cel]             */
#define PTSCTMP_GATHW_OFFSET_TO_OP1              (PTSCTMP_CEL_OFFSET - PTSCTMP_GATHW_OFFSET) /* GATHWOFFSET -> -273.15[cel] */

#define PTSCTMP_CELCHK_NWORD                     (16U)

#define PTSCTMP_GATHW_SENSORFAIL                 (0x003U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PTSCTMP_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (PTSCTMP_STSBIT_INVALID != COM_TIMEOUT))
#error "PTSCTMP_STSBIT_UNKNOWN shall be equal to COM_NO_RX and PTSCTMP_STSBIT_INVALID shall be equal to COM_TIMEOUT."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1         u1_g_PTSCTMP_ADC_CH_WTSSR      = (U1)U1_MAX;
const U1         u1_g_PTSCTMP_ADC_CH_SW5_BEFORE = (U1)U1_MAX;
const U1         u1_g_PTSCTMP_ADC_CH_SW5_AFTER  = (U1)U1_MAX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      u1_s_PtsctmpCanGATHWComRx(U2 * u2p_a_0p01cel);
static  U1      u1_s_PtsctmpCfgWtSwHi(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_PtsctmpCfgCelInst(U2 * u2p_a_0p01cel)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_PtsctmpCfgCelInst(U2 * u2p_a_0p01cel)
{
    U1                   u1_t_stsbit;
    U1                   u1_t_wtsw_hi;

    u1_t_stsbit = u1_s_PtsctmpCanGATHWComRx(u2p_a_0p01cel);

    u1_t_wtsw_hi = u1_s_PtsctmpCfgWtSwHi();
    if(u1_t_wtsw_hi == (U1)TRUE){
        u1_t_stsbit |= (U1)PTSCTMP_STSBIT_WTSW_HI;
    }

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_PtsctmpCfgWtSel(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_PtsctmpCfgWtSel(void)
{
    return((U1)PTSCTMP_WTSEL__SW);
}
/*===================================================================================================================================*/
/*  static  U1      u1_s_PtsctmpCfgWtSwHi(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_PtsctmpCfgWtSwHi(void)
{
    return((U1)FALSE);
}
/*===================================================================================================================================*/
/*  static  U1      u1_s_PtsctmpCanGATHWComRx(U2 * u2p_a_0p01cel)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_PtsctmpCanGATHWComRx(U2 * u2p_a_0p01cel)
{
    static const U4 u4_sp_PTSCTMP_CELCHK[PTSCTMP_CELCHK_NWORD]={        /* Valid range for GATHW */
        (U4)0xfffffff6U,       /*   0-31  */
        (U4)0xffffffffU,       /*  32-63  */
        (U4)0xffffffffU,       /*  64-95  */
        (U4)0xffffffffU,       /*  96-127 */
        (U4)0xffffffffU,       /* 128-159 */
        (U4)0xffffffffU,       /* 160-191 */
        (U4)0xffffffffU,       /* 192-223 */
        (U4)0xffffffffU,       /* 224-255 */
        (U4)0xffffffffU,       /* 256-286 */
        (U4)0xffffffffU,       /* 287-318 */
        (U4)0xffffffffU,       /* 319-350 */
        (U4)0xffffffffU,       /* 351-382 */
        (U4)0xffffffffU,       /* 383-414 */
        (U4)0xffffffffU,       /* 415-446 */
        (U4)0xffffffffU,       /* 447-478 */
        (U4)0xffffffffU        /* 479-511 */
    };

    U4                   u4_t_celchk;

    U2                   u2_t_0p5cel;
    U1                   u1_t_stsbit;
    U1                   u1_t_fltpos;
    U1                   u1_t_bitpos;

    u2_t_0p5cel = (U2)0U;

#if 0   /* BEV BSW provisionally */
    u1_t_stsbit = (U1)Com_GetIPDUStatus(MSG_ENG1G97_RXCH0) & (U1)(COM_TIMEOUT | COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_GATHW, &u2_t_0p5cel);
#else
    u1_t_stsbit = (U1)COM_NO_RX;
#endif
    if ((u1_t_stsbit & (U1)COM_TIMEOUT) != (U1)0U) {
        u2_t_0p5cel = (U2)PTSCTMP_GATHW_SENSORFAIL;
    }
    u2_t_0p5cel = u2_t_0p5cel & (U2)PTSCTMP_CANRX_BITMASK;

    u1_t_fltpos = (U1)(u2_t_0p5cel >> (U2)PTSCTMP_CANRX_BITLEN);
    u1_t_bitpos = (U1)(u2_t_0p5cel & (U2)PTSCTMP_CANRX_MASK);
    if(u1_t_fltpos < (U1)PTSCTMP_CELCHK_NWORD){
        u4_t_celchk = u4_sp_PTSCTMP_CELCHK[u1_t_fltpos] & ((U4)0x00000001U << u1_t_bitpos);
        if(u4_t_celchk == (U4)0U){
            u1_t_stsbit |= (U1)PTSCTMP_STSBIT_UNKNOWN;
        }
    }

    (* u2p_a_0p01cel) = (u2_t_0p5cel * (U2)PTSCTMP_GATHW_LSB_TO_0P01) + (U2)PTSCTMP_GATHW_OFFSET_TO_OP1;

    return(u1_t_stsbit);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/25/2018  AK       New.                                                                                               */
/*  1.1.0     2/28/2019  TN       ptsctmp_cel.* v1.0.0 -> v1.1.0.                                                                    */
/*  1.2.0     6/17/2019  TN       ptsctmp_cel.* v1.1.0 -> v1.2.0.                                                                    */
/*  1.3.0     3/13/2020  HK       ptsctmp_cel.* v1.2.0 -> v1.3.0.                                                                    */
/*  1.4.0     7/ 7/2020  HY       ptsctmp_cel.* v1.3.0 -> v1.4.0.                                                                    */
/*  2.0.0     4/15/2021  TA       ptsctmp_cel.* v1.4.0 -> v2.0.0.                                                                    */
/*  2.0.1    10/18/2021  TA(M)    ptsctmp_cel.* v2.0.0 -> v2.0.1.                                                                    */
/*  2.1.0    12/15/2021  TA(M)    ptsctmp_cel.* v2.0.1 -> v2.1.0.                                                                    */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  08/21/2023  SH       Config merge                                                                                       */
/*                                Change the return value of u1_s_PtsctmpCfgWtSwHi() to FALSE                                        */
/*                                Delete u1_s_PtsctmpCfgWtSwOp()                                                                     */
/* 19PFv3-2  02/12/2024  KH       Apply 19PFv3 configuration                                                                         */
/*                                                                                                                                   */
/*  * AK   = Aiko Kishino, Denso                                                                                                     */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * HK   = Hidehiro Kuroda, Denso Techno                                                                                           */
/*  * HY   = Hiroshige Yanase, Denso Techno                                                                                          */
/*  * TA   = Teruyuki Anjima, DENSO                                                                                                  */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
