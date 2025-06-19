/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Inter-Vm Data SHaring                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_CFG_C_MAJOR                        (1)
#define IVDSH_CFG_C_MINOR                        (0)
#define IVDSH_CFG_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ivdsh_cfg_private.h"
#include "ehvm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((IVDSH_CFG_C_MAJOR != IVDSH_H_MAJOR) || \
     (IVDSH_CFG_C_MINOR != IVDSH_H_MINOR) || \
     (IVDSH_CFG_C_PATCH != IVDSH_H_PATCH))
#error "ivdsh_cfg.c and ivdsh.h : source and header files are inconsistent!"
#endif

#if ((IVDSH_CFG_C_MAJOR != IVDSH_CFG_H_MAJOR) || \
     (IVDSH_CFG_C_MINOR != IVDSH_CFG_H_MINOR) || \
     (IVDSH_CFG_C_PATCH != IVDSH_CFG_H_PATCH))
#error "ivdsh_cfg.c and ivdsh_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_WORD_LEN                           (4U)       /* 4byte */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4                          u4_gp_ivdsh_buf[IVDSH_DID_BUFLEN_TX + (IVDSH_DID_BUFLEN_RX * IVDSH_NUM_RXBUF)];

U1                          u1_gp_ivdsh_rcvd[IVDSH_NUM_RX];
U1                          u1_gp_ivdsh_buf_rd[IVDSH_NUM_RX];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_IVDSH_DID          st_gp_IVDSH_CFG_DID[IVDSH_DID_NUM_TX + IVDSH_DID_NUM_RX] =
{
    /* u2_offset,    u2_nword   */
    /*--------------------------*/
    /* Transmit                 */
    /*--------------------------*/
    {(U2)0U,         (U2)1U     },      /* IVDSH_DID_TX_CPREQ_006 */
    {(U2)1U,         (U2)1U     },      /* IVDSH_DID_TX_CPREQ_008 */
    {(U2)2U,         (U2)1U     },      /* IVDSH_DID_TX_CPREQ_029 */
    {(U2)3U,         (U2)1U     },      /* IVDSH_DID_TX_CPREQ_032 */
    {(U2)4U,         (U2)1U     },      /* IVDSH_DID_TX_CPREQ_035 */
    {(U2)5U,         (U2)1U     },      /* IVDSH_DID_TX_CPREQ_038 */
    /*--------------------------*/
    /* Recieve from VM#1        */
    /*--------------------------*/
    {(U2)6U,        (U2)1U      }       /* @todo A.Motomatsu : Dummy definition for build. Config without send/receive not thought through */
    /*--------------------------*/
    /* Recieve from VM#2        */
    /*--------------------------*/
    /*--------------------------*/
    /* Recieve from VM#3        */
    /*--------------------------*/
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                    u1_gp_IVDSH_RX_BY_DID[IVDSH_DID_NUM_TX + IVDSH_DID_NUM_RX] =
{
    /*--------------------------*/
    /* Transmit                 */
    /*--------------------------*/
    (U1)U1_MAX,                         /* IVDSH_DID_TX_CPREQ_006 */
    (U1)U1_MAX,                         /* IVDSH_DID_TX_CPREQ_008 */
    (U1)U1_MAX,                         /* IVDSH_DID_TX_CPREQ_029 */
    (U1)U1_MAX,                         /* IVDSH_DID_TX_CPREQ_032 */
    (U1)U1_MAX,                         /* IVDSH_DID_TX_CPREQ_035 */
    (U1)U1_MAX,                         /* IVDSH_DID_TX_CPREQ_038 */
    /*--------------------------*/
    /* Recieve from VM#1        */
    /*--------------------------*/
    (U1)0U                              /* @todo A.Motomatsu : Dummy definition for build. Config without send/receive not thought through */
    /*--------------------------*/
    /* Recieve from VM#2        */
    /*--------------------------*/
    /*--------------------------*/
    /* Recieve from VM#3        */
    /*--------------------------*/
};
const U2                    u2_g_IVDSH_DID_NUM_TX = (U2)IVDSH_DID_NUM_TX;
const U2                    u2_g_IVDSH_DID_NUM_RX = (U2)IVDSH_DID_NUM_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_g_IVDSH_CH_TX = (U2)16U;     /* TX  = VCC Ch.16 : VM0 Inter-VM Sharing Data Tx */
const ST_IVDSH_RX           st_gp_IVDSH_CFG_RX[IVDSH_NUM_RX] = {
    /* u2_ch,       u2_nword                   */
    {(U2)U2_MAX,    (U2)IVDSH_DID_BUFLEN_RX    }        /* @todo A.Motomatsu : Dummy definition for build. Config without send/receive not thought through */
};
const U1                    u1_g_IVDSH_NUM_RX = (U1)IVDSH_NUM_RX;

const U2                    u2_g_IVDSH_BUFLEN_RX = (U2)IVDSH_DID_BUFLEN_RX;
const U2                    u2_g_IVDSH_BUFLEN_TX = (U2)IVDSH_DID_BUFLEN_TX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_iVDshMainRx(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_iVDshCfgInit(void)
{
    U4        u4_t_lpcnt;

#if 0 /* @todo A.Motomatsu start: Dummy definition for avoid run-time error. Config without send/receive not thought through */
    /* @todo A.Motomatsu start: VCC may be lost or corrupted if sent before clear; VCC clear timing must be redesigned  */
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_IVDSH_NUM_RX; u4_t_lpcnt++){
        (void)ehvm_vcc_clear_channel((U4)st_gp_IVDSH_CFG_RX[u4_t_lpcnt].u2_ch);
    }
    /* @todo A.Motomatsu end: VCC may be lost or corrupted if sent before clear; VCC clear timing must be redesigned  */
#endif /* @todo A.Motomatsu end: Dummy definition for avoid run-time error. Config without send/receive not thought through */

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)IVDSH_DID_BUFLEN_TX; u4_t_lpcnt++){
        u4_gp_ivdsh_buf[u4_t_lpcnt] = (U4)0U;
    }
    for(; u4_t_lpcnt < (U4)IVDSH_DID_BUFLEN_RX; u4_t_lpcnt++){
        u4_gp_ivdsh_buf[                                    u4_t_lpcnt] = (U4)0U;     /* Initialize IVDSH_RXBUF_0 */
        u4_gp_ivdsh_buf[(IVDSH_NUM_RXBUF * IVDSH_RXBUF_1) + u4_t_lpcnt] = (U4)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_iVDshMainRx(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_iVDshCfgTransmit(const U4 u4_a_CH, const U4 * u4_ap_TXBUF, const U2 u2_a_NWORD)
{
    (void)ehvm_vcc_transmit(u4_a_CH, u4_ap_TXBUF, (U4)(u2_a_NWORD * (U2)IVDSH_WORD_LEN));
}
/*===================================================================================================================================*/
/*  U1      u1_g_iVDshCfgReceive(const U4 u4_a_CH, U4 * u4_ap_rxbuf, const U2 u2_a_NWORD)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_iVDshCfgReceive(const U4 u4_a_CH, U4 * u4_ap_rxbuf, const U2 u2_a_NWORD)
{
#if 0 /* @todo A.Motomatsu start: Dummy definition for build. Config without send/receive not thought through */
    static const U1     u1_sp_IVDSH_RCVCNT_MAX = (U1)2U;    /* VCC Ring Element Count = 2 */

    U4                  u4_t_lpcnt;
    U4                  u4_t_ack;

    U1                  u1_t_vcc_ret;
    U1                  u1_t_act;

    u1_t_act = (U1)FALSE;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_sp_IVDSH_RCVCNT_MAX; u4_t_lpcnt++)
    {
        u1_t_vcc_ret = ehvm_vcc_receive(u4_a_CH, &u4_ap_rxbuf[0U], (u2_a_NWORD * (U2)IVDSH_WORD_LEN), &u4_t_ack);
        if((u1_t_vcc_ret == (U1)E_EHVM_RECEIVE_QUEUE_EMPTY      ) ||
           (u4_t_ack     != (U4)(u2_a_NWORD * (U2)IVDSH_WORD_LEN))){
            break;
        }else{
            u1_t_act = (U1)TRUE;
        }
    }

    return(u1_t_act);
#endif /* @todo A.Motomatsu end: Dummy definition for build. Config without send/receive not thought through */
    return((U1)FALSE);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    06/13/2025  AM       New.                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * AM   = Akira Motomatsu, Denso                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
