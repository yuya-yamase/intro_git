/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Battery Power                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define BATTPOW_C_MAJOR                          (2)
#define BATTPOW_C_MINOR                          (0)
#define BATTPOW_C_PATCH                          (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "battpow_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((BATTPOW_C_MAJOR != BATTPOW_H_MAJOR) || \
     (BATTPOW_C_MINOR != BATTPOW_H_MINOR) || \
     (BATTPOW_C_PATCH != BATTPOW_H_PATCH))
#error "battpow.c and battpow.h : source and header files are inconsistent!"
#endif

#if ((BATTPOW_C_MAJOR != BATTPOW_CFG_H_MAJOR) || \
     (BATTPOW_C_MINOR != BATTPOW_CFG_H_MINOR) || \
     (BATTPOW_C_PATCH != BATTPOW_CFG_H_PATCH))
#error "battpow.c and battpow_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define BATTPOW_SOCDSP_UNKNOWN                   (0x7FU)                        /* SOCDSP Unknown                                    */
#define BATTPOW_SOCINDLL_UNKNOWN                 (0x00U)                        /* SOCINDLL Unknown                                  */

#define BATTPOW_STS_SFT_SOCDSP                   (2U)                           /* SOCDSP Status Shift                               */
#define BATTPOW_STS_NUM                          (16U)                          /* Number of Battpow Status                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1              u1_s_battpow_socdsp_val;                                /* SOCDSP Value                                      */
static  U1              u1_s_battpow_socindll_val;                              /* SOCINDLL Value                                    */
static  U1              u1_s_battpow_dig_status;                                /* Digital Status                                    */
static  U1              u1_s_battpow_anaseg_status;                             /* Analog Segment Status                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1    u1_s_BattpowDigStsChk(const U1 u1_a_SOCDSP_STS, const U1 u1_a_SOCINDLL_STS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_BattpowInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_BattpowInit(void)
{
    u1_s_battpow_socdsp_val    = (U1)BATTPOW_SOCDSP_UNKNOWN;
    u1_s_battpow_socindll_val  = (U1)BATTPOW_SOCINDLL_UNKNOWN;
    u1_s_battpow_dig_status    = (U1)BATTPOW_STSBIT_UNKNOWN;
    u1_s_battpow_anaseg_status = (U1)BATTPOW_STSBIT_UNKNOWN;
}

/*===================================================================================================================================*/
/*  void    vd_g_BattpowMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_BattpowMainTask(void)
{
    U1                  u1_t_socdsp_stsbit;                                     /* SOCDSP Status                                     */
    U1                  u1_t_socindll_stsbit;                                   /* SOCINDLL Status                                   */
    U1                  u1_t_igsts;                                             /* Ig Status                                         */
    U1                  u1_t_get_ptsys;                                         /* PTSYS judge result                                */
    U1                  u1_t_socdsp;                                            /* SOCDSP Value                                      */
    U1                  u1_t_socindll;                                          /* SOCINDLL Value                                    */

    u1_t_socdsp        = (U1)BATTPOW_SOCDSP_UNKNOWN;
    u1_t_socindll      = (U1)BATTPOW_SOCINDLL_UNKNOWN;

    u1_t_get_ptsys     = u1_g_BattpowCfgPtsysJudge();

    if((u1_t_get_ptsys == (U1)BATTPOW_SOCMON_PHEV)||
       (u1_t_get_ptsys == (U1)BATTPOW_SOCMON_BEV)){
        u1_t_socdsp_stsbit = u1_g_BattpowCfgSOCDSP(&u1_t_socdsp);

        if(u1_t_socdsp_stsbit != (U1)BATTPOW_STSBIT_VALID){
            u1_t_socdsp = (U1)BATTPOW_SOCDSP_UNKNOWN;
        }

        if(u1_t_get_ptsys == (U1)BATTPOW_SOCMON_PHEV){
            u1_t_igsts = u1_g_BattpowIgnOn();
            if(u1_t_igsts == (U1)TRUE){
                u1_t_socindll_stsbit = u1_g_BattpowCfgSOCINDLL(&u1_t_socindll);
                if(u1_t_socindll_stsbit == (U1)BATTPOW_STSBIT_UNKNOWN){
                    u1_t_socindll = (U1)BATTPOW_SOCINDLL_UNKNOWN;
                }
                else if((u1_t_socindll_stsbit & (U1)BATTPOW_STSBIT_INVALID) != (U1)0U){
                    u1_t_socindll = u1_s_battpow_socindll_val;
                }
                else{
                    /* Do Nothing */
                }
            }
            else{
                u1_t_socindll_stsbit = (U1)BATTPOW_STSBIT_VALID;
            }
        }
        else{ /* BEV */
            u1_t_socindll_stsbit = (U1)BATTPOW_STSBIT_VALID;
        }
    }
    else
    {
        u1_t_socdsp_stsbit   = (U1)BATTPOW_STSBIT_INVALID;
        u1_t_socindll_stsbit = (U1)BATTPOW_STSBIT_INVALID;
    }

    u1_s_battpow_dig_status    = u1_s_BattpowDigStsChk(u1_t_socdsp_stsbit, u1_t_socindll_stsbit);
    u1_s_battpow_anaseg_status = u1_t_socdsp_stsbit;
    u1_s_battpow_socdsp_val    = u1_t_socdsp;
    u1_s_battpow_socindll_val  = u1_t_socindll;
}

/*===================================================================================================================================*/
/* static U1       u1_s_BattpowDigStsChk(const U1 u1_a_SOCDSP_STS, const U1 u1_a_SOCINDLL_STS)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_SOCDSP_STS   : SOCDSP Signal Status                                                                */
/*                  const U1 u1_a_SOCINDLL_STS : SOCINDLL Signal Status                                                              */
/*  Return:         U1       u1_t_stsbit       : Digital Status                                                                      */
/*===================================================================================================================================*/
static U1       u1_s_BattpowDigStsChk(const U1 u1_a_SOCDSP_STS, const U1 u1_a_SOCINDLL_STS)
{
    static  const   U1  u1_sp_BATTPOW_STS[BATTPOW_STS_NUM] = {                  /* Battpow Digital Stauts Table                      */
        (U1)BATTPOW_STSBIT_VALID,
        (U1)BATTPOW_STSBIT_UNKNOWN,
        (U1)BATTPOW_STSBIT_VALID,
        (U1)BATTPOW_STSBIT_VALID,
        (U1)BATTPOW_STSBIT_UNKNOWN,
        (U1)BATTPOW_STSBIT_UNKNOWN,
        (U1)BATTPOW_STSBIT_UNKNOWN,
        (U1)BATTPOW_STSBIT_UNKNOWN,
        (U1)BATTPOW_STSBIT_INVALID,
        (U1)BATTPOW_STSBIT_INVALID,
        (U1)BATTPOW_STSBIT_INVALID,
        (U1)BATTPOW_STSBIT_INVALID,
        (U1)BATTPOW_STSBIT_INVALID,
        (U1)BATTPOW_STSBIT_INVALID,
        (U1)BATTPOW_STSBIT_INVALID,
        (U1)BATTPOW_STSBIT_INVALID
    };
    U1                 u1_t_stsbit;                                             /* Digital Status                                    */
    U1                 u1_t_stschk;                                             /* Digital Status Check                              */

    u1_t_stschk  = (u1_a_SOCDSP_STS << BATTPOW_STS_SFT_SOCDSP);
    u1_t_stschk |= u1_a_SOCINDLL_STS;

    if(u1_t_stschk >= (U1)BATTPOW_STS_NUM){
        u1_t_stsbit = (U1)BATTPOW_STSBIT_INVALID;
    }
    else {
        u1_t_stsbit = u1_sp_BATTPOW_STS[u1_t_stschk];
    }

    return (u1_t_stsbit);
}

/*===================================================================================================================================*/
/* U1              u1_g_BattpowDigPct(U1 * const u1p_a_dsp, U1 * const u1p_a_indll)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 * const u1p_a_dsp               : SOCDSP Value                                                                */
/*                  U1 * const u1p_a_indll             : SOCINDLL Value                                                              */
/*  Return:         U1         u1_s_battpow_dig_status : Digital Status                                                              */
/*===================================================================================================================================*/
U1              u1_g_BattpowDigPct(U1 * const u1p_a_dsp, U1 * const u1p_a_indll)
{
    if (u1p_a_dsp   != vdp_PTR_NA) {
        (*u1p_a_dsp)   = u1_s_battpow_socdsp_val;
    }
    if (u1p_a_indll != vdp_PTR_NA) {
        (*u1p_a_indll) = u1_s_battpow_socindll_val;
    }

    return (u1_s_battpow_dig_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_BattpowAnaPct(U1 * const u1p_a_dsp)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1 * const u1p_a_dsp                  : SOCDSP Value                                                             */
/*  Return:         U1         u1_s_battpow_anaseg_status : Analog Segment Status                                                    */
/*===================================================================================================================================*/
U1              u1_g_BattpowAnaPct(U1 * const u1p_a_dsp)
{
    if (u1p_a_dsp != vdp_PTR_NA) {
        (*u1p_a_dsp) = u1_s_battpow_socdsp_val;
    }

    return (u1_s_battpow_anaseg_status);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    06/14/2018  HY       New.                                                                                               */
/*  1.1.0    03/11/2020  TA       battpow.c. v1.0.0 -> v1.1.0.                                                                       */
/*  1.2.0    09/02/2020  TA       Addition of SOCINDLL signal judgment and change of I/F                                             */
/*                                Response to QAC.                                                                                   */
/*           10/07/2020  TA       Response to CodeSonar.                                                                             */
/*  1.2.1    12/01/2020  TA       Add Comment.                                                                                       */
/*           01/08/2021  TA       Change to not keep SOCINDLL during IGOFF.                                                          */
/*  2.0.0    08/04/2021  TK       vd_g_BattpowMainTask() : Logic change.                                                             */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 12/11/2023  SN       Change vd_g_BattpowMainTask get ptsys value.                                                       */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * TA   = Tsubasa Aki, Denso Techno                                                                                               */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
