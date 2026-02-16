/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Average XXXX Economy application core                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGECON_C_MAJOR                         (2)
#define AVGECON_C_MINOR                         (2)
#define AVGECON_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "avgecon_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AVGECON_C_MAJOR != AVGECON_H_MAJOR) || \
     (AVGECON_C_MINOR != AVGECON_H_MINOR) || \
     (AVGECON_C_PATCH != AVGECON_H_PATCH))
#error "avgecon.c and avgecon.h : source and header files are inconsistent!"
#endif

#if ((AVGECON_C_MAJOR != AVGECON_CFG_H_MAJOR) || \
     (AVGECON_C_MINOR != AVGECON_CFG_H_MINOR) || \
     (AVGECON_C_PATCH != AVGECON_CFG_H_PATCH))
#error "avgecon.c and avgecon_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGECON_RNDHLF_SFT                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1              u1_s_AvgEconImmwRunAct(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_UPDT, const U1 u1_a_INIT);
static U1              u1_s_AvgEconImmwRstChk(const ST_AVGECON_CNTT * stp_a_CNTT);
static U2              u2_s_AvgEconResConv(const ST_AVGECON_CNTT * stp_a_CNTT, U4 u4_a_xecon);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_AvgEconRstImmw(const U1 u1_a_ACTV, const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgEconRstImmw(const U1 u1_a_ACTV, const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD)
{
    U1                                          u1_t_rstimmw;
    U1                                          u1_t_updt;
    U1                                          u1_t_init;
    U1                                          u1_t_accpt;
    U1                                          u1_t_stsbit;

    u1_t_rstimmw = stp_a_var->u1_rstimmw;

    if((u1_t_rstimmw & (U1)TRIPCOM_RSTIMMW_RUN) == (U1)0U){
        /* TRIPCOM_RSTIMMW_UNK or TRIPCOM_RSTIMMW_(SUC or TRIPCOM_RSTIMMW_FAI */
        if((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MARST_IMMW] & stp_a_CNTT->u2_manualreset) != (U2)0U){
            if(u1_a_ACTV == (U1)TRUE){
                u1_t_updt = stp_a_var->u1_initupdt;
                u1_t_init = (U1)FALSE;
            }
            else{
                u1_t_updt = (U1)TRUE;
                u1_t_init = (U1)TRUE;
            }

            u1_t_accpt = u1_s_AvgEconImmwRunAct(stp_a_CNTT, u1_t_updt, u1_t_init);
            if(u1_t_accpt == (U1)TRUE){
                u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_RUN;
            }
            else{
                u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_FAI;
            }
        }
    }
    else{
        /* TRIPCOM_RSTIMMW_RUN */
        u1_t_stsbit = u1_s_AvgEconImmwRstChk(stp_a_CNTT);

        if((u1_t_stsbit & (U1)TRIPCOM_MS_NVMSTS_SUC) != (U1)0x00U){
            u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_SUC;
        }
        else if((u1_t_stsbit & (U1)TRIPCOM_MS_NVMSTS_FAIL) != (U1)0x00U){
            u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_FAI;
        }
        else{
            /* nothing */
        }
    }
    stp_a_var->u1_rstimmw = u1_t_rstimmw;
}

/*===================================================================================================================================*/
/* U2           u2_g_AvgEconCalcTx(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_RSTTRM, const U1 u1_a_UNIT)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_AvgEconCalcTx(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_RSTTRM, const U1 u1_a_UNIT)
{

    U4          u4_t_xecon;
    U2          u2_t_txval;
    U1          u1_t_cnvsts;


    u2_t_txval = stp_a_CNTT->u2_cantx_unknown;

    if (u1_a_RSTTRM == (U1)TRUE) {
        u2_t_txval = stp_a_CNTT->u2_cantx_rstinit;
    }
    else {
        u4_t_xecon  = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_economy_id);
        u1_t_cnvsts = u1_g_TripcomCalcTxCnvtAvgEE(&u4_t_xecon, u1_a_UNIT, stp_a_CNTT->u1_cantx_aprx);
        if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
            u2_t_txval = u2_s_AvgEconResConv(stp_a_CNTT, u4_t_xecon);
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* static U1       u1_s_AvgEconImmwRunAct(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_UPDT, const U1 u1_a_INIT)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_AvgEconImmwRunAct(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_UPDT, const U1 u1_a_INIT)
{
    U1                                          u1_t_accpt;
    U1                                          u1_t_rslt_a;
    U1                                          u1_t_rslt_b;
    U1                                          u1_t_rslt_c;

    u1_t_accpt = (U1)FALSE;

    if(u1_a_UPDT == (U1)TRUE){
        u1_t_rslt_a = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_economy_id);
        u1_t_rslt_b = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_used_id   );
        u1_t_rslt_c = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_odocnt_id );

        if((u1_t_rslt_a != (U1)TRIPCOM_MS_NVMSTS_WAIT) &&
           (u1_t_rslt_b != (U1)TRIPCOM_MS_NVMSTS_WAIT) &&
           (u1_t_rslt_c != (U1)TRIPCOM_MS_NVMSTS_WAIT)){
            if(u1_a_INIT == (U1)TRUE){
                vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_economy_id, (U4)0U);
                vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_used_id,    (U4)0U);
                vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id,  (U4)0U);
            }

            vd_g_TripcomMsSetNvmRqst(stp_a_CNTT->u1_ms_economy_id);
            vd_g_TripcomMsSetNvmRqst(stp_a_CNTT->u1_ms_used_id   );
            vd_g_TripcomMsSetNvmRqst(stp_a_CNTT->u1_ms_odocnt_id );

            u1_t_accpt = (U1)TRUE;
        }
    }
    return(u1_t_accpt);
}

/*===================================================================================================================================*/
/* static U1       u1_s_AvgEconImmwRstChk(const ST_AVGECON_CNTT * stp_a_CNTT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_AvgEconImmwRstChk(const ST_AVGECON_CNTT * stp_a_CNTT)
{
    U1                                          u1_t_tmpbit;
    U1                                          u1_t_stsbit;
    U1                                          u1_t_sucbit;
    U1                                          u1_t_faibit;

    u1_t_stsbit = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_economy_id);

    u1_t_tmpbit = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_used_id);
    u1_t_sucbit = (U1)((u1_t_stsbit & u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_SUC);
    u1_t_faibit = (U1)((u1_t_stsbit | u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_stsbit = u1_t_sucbit | u1_t_faibit;

    u1_t_tmpbit = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_odocnt_id);
    u1_t_sucbit = (U1)((u1_t_stsbit & u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_SUC);
    u1_t_faibit = (U1)((u1_t_stsbit | u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_stsbit = u1_t_sucbit | u1_t_faibit;

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/* static  U2      u2_s_AvgEconResConv(const ST_AVGECON_CNTT * stp_a_CNTT, U4 u4_a_xecon)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_AvgEconResConv(const ST_AVGECON_CNTT * stp_a_CNTT, U4 u4_a_xecon)
{
    U2          u2_t_ret;
    U4          u4_t_remain;
    U4          u4_t_rndhlf;

    u4_t_remain = u4_a_xecon % (U4)(stp_a_CNTT->u2_cantx_resconv);
    u4_t_rndhlf = (U4)(stp_a_CNTT->u2_cantx_resconv) >> AVGECON_RNDHLF_SFT;
    u4_a_xecon /= (U4)(stp_a_CNTT->u2_cantx_resconv);
    if (u4_t_rndhlf < u4_t_remain) {
        u4_a_xecon++;
    }
    u2_t_ret = stp_a_CNTT->u2_cantx_max;
    if (u4_a_xecon < (U4)u2_t_ret) {
        u2_t_ret = (U2)u4_a_xecon;
    }

    return (u2_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.0.1    03/19/2020  YA       Change for 800B CV                                                                                 */
/*  1.0.2    10/07/2020  YA       Change for 800B CV-R                                                                               */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    02/18/2025  MaO(M)   Add privacy data delete/result API                                                                 */
/*  2.2.0    02/13/2026  PG       Changed for BEV FF2                                                                                */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-01   02/13/2026  DR       Deleted not used function in BEV FF2                                                               */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
