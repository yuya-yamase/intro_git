/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  F-spo Sensor                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FSPOSNSR_C_MAJOR                         (2)
#define FSPOSNSR_C_MINOR                         (1)
#define FSPOSNSR_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fsposnsr_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((FSPOSNSR_C_MAJOR != FSPOSNSR_H_MAJOR) || \
     (FSPOSNSR_C_MINOR != FSPOSNSR_H_MINOR) || \
     (FSPOSNSR_C_PATCH != FSPOSNSR_H_PATCH))
#error "fsposnsr.c and fsposnsr.h : source and header files are inconsistent!"
#endif

#if ((FSPOSNSR_C_MAJOR != FSPOSNSR_CFG_H_MAJOR) || \
     (FSPOSNSR_C_MINOR != FSPOSNSR_CFG_H_MINOR) || \
     (FSPOSNSR_C_PATCH != FSPOSNSR_CFG_H_PATCH))
#error "fsposnsr.c and fsposnsr_cfg_private.h : source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_fsposnr_eng1s98rcvd;                               /* ENG1S98 receive flag                                      */
static U1       u1_s_fsposnr_vsc1g12rcvd;                               /* VSC1G12 receive flag                                      */
static U1       u1_s_fsposnr_vsc1g30rcvd;                               /* VSC1G30 receive flag                                      */
static U1       u1_s_fsposnr_eng1g17rcvd;                               /* ENG1G17 receive flag                                      */

static U2       u2_s_fsposnr_sigsts;                                    /* Signal status                                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_FsposnsrGetVsc1g12(ST_FSPOSNSR_INC_VSC1G12* stp_a_incarg);
static U1       u1_s_FsposnsrGetVsc1g30(ST_FSPOSNSR_INC_VSC1G30* stp_a_incarg);
static U1       u1_s_FsposnsrGetEng1g17(ST_FSPOSNSR_INC_ENG1G17* stp_a_incarg);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_FsposnsrBon(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FsposnsrBon(void)
{
    u2_s_fsposnr_sigsts  = (U2)FSPOSNSR_SIGSTS_INIT;

    vd_FSPOSNSR_BRAMWRT_U2(u2_s_fsposnr_sigsts);

    u1_s_fsposnr_eng1s98rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g12rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g30rcvd = (U1)FALSE;
    u1_s_fsposnr_eng1g17rcvd = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  void    vd_g_FsposnsrWkup(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FsposnsrWkup(void)
{
    U1                      u1_t_rimsts;

    u1_t_rimsts = u1_FSPOSNSR_BRAMREAD(&u2_s_fsposnr_sigsts);
    if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
        u2_s_fsposnr_sigsts = (U2)FSPOSNSR_SIGSTS_INIT;
    }

    vd_FSPOSNSR_BRAMWRT_U2(u2_s_fsposnr_sigsts);

    u1_s_fsposnr_eng1s98rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g12rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g30rcvd = (U1)FALSE;
    u1_s_fsposnr_eng1g17rcvd = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  void    vd_g_FsposnsrIgon(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FsposnsrIgon(void)
{
    u1_s_fsposnr_eng1s98rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g12rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g30rcvd = (U1)FALSE;
    u1_s_fsposnr_eng1g17rcvd = (U1)FALSE;

    u2_s_fsposnr_sigsts &= (U2)FSPOSNSR_SIGSTS_IGONMASK;
}

/*===================================================================================================================================*/
/*  void vd_g_FsposnsrIgoff(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FsposnsrIgoff(void)
{
    u1_s_fsposnr_eng1s98rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g12rcvd = (U1)FALSE;
    u1_s_fsposnr_vsc1g30rcvd = (U1)FALSE;
    u1_s_fsposnr_eng1g17rcvd = (U1)FALSE;
}


/*===================================================================================================================================*/
/*  void    vd_g_Fsposnsr10msTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Attention:      Register for 10msHi event                                                                                        */
/*===================================================================================================================================*/
void    vd_g_Fsposnsr10msTask(void)
{
    ST_FSPOSNSR_INCARG      st_t_incarg;
    U1                      u1_t_rcvd;

    u1_t_rcvd  = u1_s_FsposnsrGetVsc1g12(&st_t_incarg.st_inc_vsc1g12);
    u1_t_rcvd |= u1_s_FsposnsrGetVsc1g30(&st_t_incarg.st_inc_vsc1g30);
    u1_t_rcvd |= u1_s_FsposnsrGetEng1g17(&st_t_incarg.st_inc_eng1g17);

    st_t_incarg.u1_rcvd    = u1_t_rcvd;
    st_t_incarg.u2_sigfail = u2_s_fsposnr_sigsts;

    vd_FSPOSNSR_BRAMWRT_U2(u2_s_fsposnr_sigsts);
    vd_FSPOSNSR_EVTINC(&st_t_incarg);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_FsposnsrGetVsc1g12(ST_FSPOSNSR_INC_VSC1G12* stp_a_incarg)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      ST_FSPOSNSR_INC_VSC1G12* stp_a_incarg                                                                            */
/*  Return:         U1 u1_t_rcvd                                                                                                     */
/*===================================================================================================================================*/
static U1       u1_s_FsposnsrGetVsc1g12(ST_FSPOSNSR_INC_VSC1G12* stp_a_incarg)
{
    U1 u1_t_failon;
    U1 u1_t_rcvd;
    U1 u1_t_igon;

    u1_t_rcvd = (U1)0U;

    stp_a_incarg->s2_gxhr0 = (S2)0U;
    stp_a_incarg->s2_gyhr0 = (S2)0U;
    stp_a_incarg->u1_gxf   = (U1)0U;
    stp_a_incarg->u1_gyf   = (U1)0U;
    stp_a_incarg->u1_gxiv  = (U1)0U;
    stp_a_incarg->u1_gyiv  = (U1)0U;

    u1_t_igon = u1_FSPOSNSR_IG_ISON();
    if(u1_t_igon == (U1)TRUE){
        if(u1_s_fsposnr_vsc1g12rcvd == (U1)TRUE){
            u1_t_rcvd = (U1)FSPOSNSR_SET_VSC1G12RCVD;

            vd_FSPOSNSR_RXMSG_V_GXHR0(&stp_a_incarg->s2_gxhr0);
            vd_FSPOSNSR_RXMSG_V_GYHR0(&stp_a_incarg->s2_gyhr0);
            vd_FSPOSNSR_RXMSG_VSC_GXF(&stp_a_incarg->u1_gxf);
            vd_FSPOSNSR_RXMSG_VSC_GYF(&stp_a_incarg->u1_gyf);
            vd_FSPOSNSR_RXMSG_VSC_GXIV(&stp_a_incarg->u1_gxiv);
            vd_FSPOSNSR_RXMSG_VSC_GYIV(&stp_a_incarg->u1_gyiv);

            u1_s_fsposnr_vsc1g12rcvd = (U1)FALSE;

            u2_s_fsposnr_sigsts &= (U2)FSPOSNSR_RST_VSC1G12FAIL;
        }
        else{
            u1_t_failon  = u1_FSPOSNSR_RXMSG_VSC1G12STS();
            u1_t_failon &= (U1)(FSPOSNSR_COM_TIMEOUT | FSPOSNSR_COM_NO_RX);
            if(u1_t_failon != (U1)0U){
                u2_s_fsposnr_sigsts |= (U2)FSPOSNSR_SET_VSC1G12FAIL;
            }
            else{
                u2_s_fsposnr_sigsts &= (U2)FSPOSNSR_RST_VSC1G12FAIL;
            }
        }
    }
    return(u1_t_rcvd);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_FsposnsrGetVsc1g30(ST_FSPOSNSR_INC_VSC1G30* stp_a_incarg )                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      ST_FSPOSNSR_INC_VSC1G30* stp_a_incarg                                                                            */
/*  Return:         U1 u1_t_rcvd                                                                                                     */
/*===================================================================================================================================*/
static U1       u1_s_FsposnsrGetVsc1g30(ST_FSPOSNSR_INC_VSC1G30* stp_a_incarg)
{
    U1                      u1_t_failon;
    U1                      u1_t_rcvd;
    U1                      u1_t_igon;

    u1_t_rcvd = (U1)0U;

    stp_a_incarg->u1_fbkdrsys = (U1)0U;
    stp_a_incarg->s2_fbkdr_ax = (S2)0;

    u1_t_igon = u1_FSPOSNSR_IG_ISON();
    if(u1_t_igon == (U1)TRUE){
        if(u1_s_fsposnr_vsc1g30rcvd == (U1)TRUE){
            u1_t_rcvd = (U1)FSPOSNSR_SET_VSC1G30RCVD;

            vd_FSPOSNSR_RXMSG_FBKDRSYS(&stp_a_incarg->u1_fbkdrsys);
            vd_FSPOSNSR_RXMSG_FBKDR_AX(&stp_a_incarg->s2_fbkdr_ax);

            u1_s_fsposnr_vsc1g30rcvd = (U1)FALSE;

            u2_s_fsposnr_sigsts &= (U2)FSPOSNSR_RST_VSC1G30FAIL;
        }
        else{
            u1_t_failon  = u1_FSPOSNSR_RXMSG_VSC1G30STS();
            u1_t_failon &= (U1)(FSPOSNSR_COM_TIMEOUT | FSPOSNSR_COM_NO_RX);
            if(u1_t_failon != (U1)0U){
                u2_s_fsposnr_sigsts |= (U2)FSPOSNSR_SET_VSC1G30FAIL;
            }
            else{
                u2_s_fsposnr_sigsts &= (U2)FSPOSNSR_RST_VSC1G30FAIL;
            }
        }
    }
    return(u1_t_rcvd);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_FsposnsrGetEng1g17(ST_FSPOSNSR_INC_ENG1G17* stp_a_incarg)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      ST_FSPOSNSR_INC_ENG1G17* stp_a_incarg                                                                            */
/*  Return:         U1 u1_t_rcvd                                                                                                     */
/*===================================================================================================================================*/
static U1       u1_s_FsposnsrGetEng1g17(ST_FSPOSNSR_INC_ENG1G17* stp_a_incarg)
{
    static const U2         u2_s_FSPO_ENG1G17_TO_THRESH = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    U1                      u1_t_failon;
    U1                      u1_t_rcvd;
    U1                      u1_t_igon;

    u1_t_rcvd = (U1)0U;

    stp_a_incarg->u2_bpom  = (U2)0U;
    stp_a_incarg->u2_bthoe = (U2)0U;

    u1_t_igon = u1_FSPOSNSR_IG_ISON();
    
    if(u1_t_igon == (U1)TRUE){
        if(u1_s_fsposnr_eng1g17rcvd == (U1)TRUE){

            u1_t_rcvd = (U1)FSPOSNSR_SET_ENG1G17RCVD;

            vd_FSPOSNSR_RXMSG_B_POM(&stp_a_incarg->u2_bpom);
            vd_FSPOSNSR_RXMSG_B_THOE(&stp_a_incarg->u2_bthoe);

            u1_s_fsposnr_eng1g17rcvd = (U1)FALSE;

            u2_s_fsposnr_sigsts &= (U2)FSPOSNSR_RST_ENG1G17FAIL;
        }
        else{
            u1_t_failon   = u1_FSPOSNSR_RXMSG_ENG1G17STS(u2_s_FSPO_ENG1G17_TO_THRESH);
            u1_t_failon  &= ((U1)FSPOSNSR_COM_TIMEOUT | (U1)FSPOSNSR_COM_NO_RX);

            if(u1_t_failon != (U1)0U){
                u2_s_fsposnr_sigsts |= (U2)FSPOSNSR_SET_ENG1G17FAIL;
            }
            else{
                u2_s_fsposnr_sigsts &= (U2)FSPOSNSR_RST_ENG1G17FAIL;
            }
        }
    }
    return(u1_t_rcvd);
}

/*===================================================================================================================================*/
/*  void    vd_g_FsposnsrCanRxEng1s98(void)                                                                                          */
/*  Attention : Call timing is when the message is received [Call from RxHook in CAN]                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FsposnsrCanRxEng1s98(void)
{
    /* Not applicable */
    u1_s_fsposnr_eng1s98rcvd = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  void    vd_g_FsposnsrCanRxVsc1g12(void)                                                                                          */
/*  Attention : Call timing is when the message is received [Call from RxHook in CAN]                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FsposnsrCanRxVsc1g12(void)
{
    u1_s_fsposnr_vsc1g12rcvd = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void    vd_g_FsposnsrCanRxVsc1g30(void)                                                                                          */
/*  Attention : Call timing is when the message is received [Call from RxHook in CAN]                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FsposnsrCanRxVsc1g30(void)
{
    u1_s_fsposnr_vsc1g30rcvd = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void    vd_g_FsposnsrCanRxEng1g17(void)                                                                                          */
/*  Attention : Call timing is when the message is received [Call from RxHook in CAN]                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FsposnsrCanRxEng1g17(void)
{
    u1_s_fsposnr_eng1g17rcvd = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  U2 u2_g_FsposnsrGetSigSts(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U2 u2_s_fsposnr_sigsts                                                                                           */
/*===================================================================================================================================*/
U2 u2_g_FsposnsrGetSigSts(void)
{
    return(u2_s_fsposnr_sigsts);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  0.0.0           04/15/2013  YK      New.                                                                                         */
/*  0.0.1           05/08/2013  YK      Support for sample software.                                                                 */
/*  0.0.2           05/28/2013  YK      Separated from the fspo _ cmn module. (Clarification of module function arrangement.)        */
/*  0.0.3           11/22/2013  YK      Support for HV/CONV separation                                                               */
/*                                      and review of the process for determining the destination variation.                         */
/*  0.0.3           11/22/2013  YK      VSC1F06 Remove Unwanted Action. backup RAM leakage.                                          */
/*  1.0.0           02/10/2015  TO      945A 1A Supported                                                                            */
/*                                      (frame,Signal change : VSC1F06->VSC1S06, PMCF->PBRKF, PMCS->PBRKS, PMC->PBRK)                */
/*  1.0.1           04/08/2015  TO      fsposnsr Brake oil pressure(VSC1S06) fixed 740A bug list No.455.                             */
/*                                      (Different types of operators)                                                               */
/*                                       -GL1Z signal is initialized : Changed U2->U1                                                */
/*                                       -GL2Z signal is inilialized : Changed U2->U1                                                */
/*  1.0.2           06/07/2017  SM      Delete:#pragma segment                                                                       */
/*  2.0.0           12/13/2021  SK      Add engine Ration speed judge process for B_PINM                                             */
/*  2.1.0           02/18/2023  KO      Add judgment processing in ENG1G02 and ENG1G17 frames                                        */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 07/02/2024  KH       Delete function for ENG1S98 frame (except Hook function)                                           */
/*  19PFv3-2 07/09/2024  KH       Delete function for ENG1G02 frame                                                                  */
/*                                                                                                                                   */
/*  * YK = Yosuke Kawahara, NCOS                                                                                                     */
/*  * TO = Takeshi Otoi                                                                                                              */
/*  * SM = Shouhei Matsumoto                                                                                                         */
/*  * KO = Kazuya Ota                                                                                                                */
/*  * KH = Kiko Huerte, DTPH                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
