/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Multi-media rx multi frame message                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MULMED_MULFR_CFG_C_MAJOR                (1)
#define MULMED_MULFR_CFG_C_MINOR                (1)
#define MULMED_MULFR_CFG_C_PATCH                (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mulmed_mulfr_cfg_private.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "memfill_u1.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MULMED_MULFR_CFG_C_MAJOR != MULMED_MULFR_H_MAJOR) || \
     (MULMED_MULFR_CFG_C_MINOR != MULMED_MULFR_H_MINOR) || \
     (MULMED_MULFR_CFG_C_PATCH != MULMED_MULFR_H_PATCH))
#error "mulmed_mulfr_cfg.c and mulmed_mulfr.h : source and header files are inconsistent!"
#endif

#if ((MULMED_MULFR_CFG_C_MAJOR != MULMED_MULFR_CFG_H_MAJOR) || \
     (MULMED_MULFR_CFG_C_MINOR != MULMED_MULFR_CFG_H_MINOR) || \
     (MULMED_MULFR_CFG_C_PATCH != MULMED_MULFR_CFG_H_PATCH))
#error "mulmed_mulfr_cfg.c and mulmed_mulfr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MULMED_MULFR_CFG_TXTINDNUM                 (58U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2                                          u2_txtsts_frame;
    void    (* const                            fp_vd_SGNLFUNC)(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
    U1                                          u1_modeid_max;
} ST_MULMED_MULFR_RX_TXTSTS;

typedef struct {
    U1                                          u1_rxcnt;
    U1                                          u1p_rxbuff[MULMED_MULFR_CAN_BUFF_SIZE];
} ST_MULMED_MULFR_RX_TXTDAT;

typedef struct {
    U2                                          u2_msg;
    U1                                          u1_txflag;
    U1      (* const                            fp_u1_SGNLFUNC)(const U1 u1_a_VALUE);
} ST_MULMED_MULFR_TX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_MULMED_MULFR_RX_TXTDAT               st_sp_mulmed_mulfr_dat[MULMED_MULFR_NUM_FR];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      u1_s_MulmedMulfrCfgGPCHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgCTSTCHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgNXSTCHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgNM1CHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgNM2CHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgTTLCHGADOM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgSTA1CHGAUDIOM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgSTA2CHGAUDIOM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgSTA3CHGAUDIOM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgSTA4CHGAUDIOM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS1M(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS2M(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS3M(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS4M(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS5M(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS6M(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgLSTCHGCMNM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgFAVCHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgHSTCHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgCDCHGM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgRTCHGVRM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgGTCHGVRM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgCTCHGVRM(const U1 u1_a_VALUE);
static  U1      u1_s_MulmedMulfrCfgDISTCHGM(const U1 u1_a_VALUE);

static  void    vd_s_MulmedMulfrCfgSgnlAVNMS01(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS02(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS03(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS04(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS05(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS06(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS07(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS08(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS09(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS10(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS13(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS14(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS15(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS16(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS18(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS19(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS20(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS21(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS22(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS23(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS25(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS26(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS27(U1 * u1p_a_modeid, U1 * u1p_a_syncid);
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS79(U1 * u1p_a_modeid, U1 * u1p_a_syncid);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV BSW provisionally */
const   U2                                      u2_g_MULMED_MULFR_AUB_MAX       = (U2)MSG_AVNMS79_RXCH1;
const   U2                                      u2_g_MULMED_MULFR_AUB_MIN       = (U2)MSG_AVNMS01_RXCH1;
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MULMED_MULFR_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (MULMED_MULFR_STSBIT_INVALID != COM_TIMEOUT))
#error "mulmed_mulfr status bit and com status bit are inconsistent!"
#endif
/*===================================================================================================================================*/
/* void            vd_g_MulmedMulfrCfgInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedMulfrCfgInit(void)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)MULMED_MULFR_NUM_FR; u4_t_loop++) {
        st_sp_mulmed_mulfr_dat[u4_t_loop].u1_rxcnt = (U1)0U;
        vd_g_MemfillU1(st_sp_mulmed_mulfr_dat[u4_t_loop].u1p_rxbuff, (U1)0U, (U4)MULMED_MULFR_CAN_BUFF_SIZE);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_MulmedMulfrCfgRxTxtSts(const U4 u4_a_MSGIDX, U1 * u1p_a_modeid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_MulmedMulfrCfgRxTxtSts(const U4 u4_a_MSGIDX, U1 * u1p_a_modeid)
{
#if 0   /* BEV BSW provisionally */
    static  const   ST_MULMED_MULFR_RX_TXTSTS   st_sp_RX_MSGS[MULMED_MULFR_NUM_FR]                      = {
        /*      u2_txtsts_frame                      fp_vd_SGNLFUNC                 u1_modeid_max   */
        {   (U2)MSG_AVNMS38_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS01,        (U1)0x03U   },  /* MSG_AVNMS01_RXCH1 */
        {   (U2)MSG_AVNMS38_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS02,        (U1)0x03U   },  /* MSG_AVNMS02_RXCH1 */
        {   (U2)MSG_AVNMS38_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS03,        (U1)0x03U   },  /* MSG_AVNMS03_RXCH1 */
        {   (U2)MSG_AVNMS32_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS04,        (U1)0x0BU   },  /* MSG_AVNMS04_RXCH1 */
        {   (U2)MSG_AVNMS32_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS05,        (U1)0x0BU   },  /* MSG_AVNMS05_RXCH1 */
        {   (U2)MSG_AVNMS50_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS06,        (U1)0x52U   },  /* MSG_AVNMS06_RXCH1 */
        {   (U2)MSG_AVNMS51_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS07,        (U1)0x52U   },  /* MSG_AVNMS07_RXCH1 */
        {   (U2)MSG_AVNMS51_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS08,        (U1)0x52U   },  /* MSG_AVNMS08_RXCH1 */
        {   (U2)MSG_AVNMS51_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS09,        (U1)0x52U   },  /* MSG_AVNMS09_RXCH1 */
        {   (U2)MSG_AVNMS51_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS10,        (U1)0x52U   },  /* MSG_AVNMS10_RXCH1 */
        {   (U2)MSG_AVNMS53_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS13,        (U1)0x52U   },  /* MSG_AVNMS13_RXCH1 */
        {   (U2)MSG_AVNMS53_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS14,        (U1)0x52U   },  /* MSG_AVNMS14_RXCH1 */
        {   (U2)MSG_AVNMS53_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS15,        (U1)0x52U   },  /* MSG_AVNMS15_RXCH1 */
        {   (U2)MSG_AVNMS53_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS16,        (U1)0x52U   },  /* MSG_AVNMS16_RXCH1 */
        {   (U2)MSG_AVNMS53_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS18,        (U1)0x52U   },  /* MSG_AVNMS18_RXCH1 */
        {   (U2)MSG_AVNMS53_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS19,        (U1)0x52U   },  /* MSG_AVNMS19_RXCH1 */
        {   (U2)MSG_AVNMS55_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS20,        (U1)0x52U   },  /* MSG_AVNMS20_RXCH1 */
        {   (U2)MSG_AVNMS33_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS21,        (U1)0x0BU   },  /* MSG_AVNMS21_RXCH1 */
        {   (U2)MSG_AVNMS33_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS22,        (U1)0x0BU   },  /* MSG_AVNMS22_RXCH1 */
        {   (U2)MSG_AVNMS33_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS23,        (U1)0x0BU   },  /* MSG_AVNMS23_RXCH1 */
        {   (U2)MSG_AVNMS44_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS25,        (U1)0x03U   },  /* MSG_AVNMS25_RXCH1 */
        {   (U2)MSG_AVNMS44_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS26,        (U1)0x03U   },  /* MSG_AVNMS26_RXCH1 */
        {   (U2)MSG_AVNMS44_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS27,        (U1)0x03U   },  /* MSG_AVNMS27_RXCH1 */
        {   (U2)MSG_AVNMS74_RXCH1,         &vd_s_MulmedMulfrCfgSgnlAVNMS79,        (U1)0x03U   }   /* MSG_AVNMS79_RXCH1 */
    };
#else
    static  const   ST_MULMED_MULFR_RX_TXTSTS   st_sp_RX_MSGS[MULMED_MULFR_NUM_FR]                      = {
        /*      u2_txtsts_frame                      fp_vd_SGNLFUNC                 u1_modeid_max   */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS01,        (U1)0x03U   },  /* MSG_AVNMS01_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS02,        (U1)0x03U   },  /* MSG_AVNMS02_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS03,        (U1)0x03U   },  /* MSG_AVNMS03_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS04,        (U1)0x0BU   },  /* MSG_AVNMS04_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS05,        (U1)0x0BU   },  /* MSG_AVNMS05_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS06,        (U1)0x52U   },  /* MSG_AVNMS06_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS07,        (U1)0x52U   },  /* MSG_AVNMS07_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS08,        (U1)0x52U   },  /* MSG_AVNMS08_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS09,        (U1)0x52U   },  /* MSG_AVNMS09_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS10,        (U1)0x52U   },  /* MSG_AVNMS10_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS13,        (U1)0x52U   },  /* MSG_AVNMS13_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS14,        (U1)0x52U   },  /* MSG_AVNMS14_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS15,        (U1)0x52U   },  /* MSG_AVNMS15_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS16,        (U1)0x52U   },  /* MSG_AVNMS16_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS18,        (U1)0x52U   },  /* MSG_AVNMS18_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS19,        (U1)0x52U   },  /* MSG_AVNMS19_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS20,        (U1)0x52U   },  /* MSG_AVNMS20_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS21,        (U1)0x0BU   },  /* MSG_AVNMS21_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS22,        (U1)0x0BU   },  /* MSG_AVNMS22_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS23,        (U1)0x0BU   },  /* MSG_AVNMS23_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS25,        (U1)0x03U   },  /* MSG_AVNMS25_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS26,        (U1)0x03U   },  /* MSG_AVNMS26_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS27,        (U1)0x03U   },  /* MSG_AVNMS27_RXCH1 */
        {   (U2)U2_MAX,                    &vd_s_MulmedMulfrCfgSgnlAVNMS79,        (U1)0x03U   }   /* MSG_AVNMS79_RXCH1 */
    };
#endif
    U1                                          u1_t_status;
    U1                                          u1_t_modeid;
    U1                                          u1_t_syncid;


#if 0   /* BEV BSW provisionally */
    u1_t_status = (U1)Com_GetIPDUStatus((PduIdType)(st_sp_RX_MSGS[u4_a_MSGIDX].u2_txtsts_frame)) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_status = (U1)COM_NO_RX;
#endif
    if (u1_t_status == (U1)0U) {
        st_sp_RX_MSGS[u4_a_MSGIDX].fp_vd_SGNLFUNC(&u1_t_modeid, &u1_t_syncid);
        if ((u1_t_modeid <= st_sp_RX_MSGS[u4_a_MSGIDX].u1_modeid_max) &&
            (u1_t_syncid != (U1)MULMED_MULFR_SYNCID_INVALID         ) &&
            (u1_t_syncid != (U1)MULMED_MULFR_SYNCID_INIT            )) {

            (*u1p_a_modeid) = u1_t_modeid;
        }
        else {
            u1_t_status |= (U1)MULMED_MULFR_STSBIT_INVALID;
        }
    }
    else{
        (*u1p_a_modeid) = (U1)0U;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* void            vd_g_MulmedMulfrCfgGetTxtDat(const U4 u4_a_MSGIDX, U1 * u1_ap_bytesgnl)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedMulfrCfgGetTxtDat(const U4 u4_a_MSGIDX, U1 * u1_ap_bytesgnl)
{
    ST_MULMED_MULFR_RX_TXTDAT *                 stp_t_txtdat;


    stp_t_txtdat = &st_sp_mulmed_mulfr_dat[u4_a_MSGIDX];
    vd_g_MemcpyU1(u1_ap_bytesgnl, stp_t_txtdat->u1p_rxbuff, (U4)MULMED_MULFR_CAN_BUFF_SIZE);
    vd_g_MemfillU1(stp_t_txtdat->u1p_rxbuff, (U1)0U,        (U4)MULMED_MULFR_CAN_BUFF_SIZE);
    stp_t_txtdat->u1_rxcnt = (U1)0U;
}

/*===================================================================================================================================*/
/* void            vd_g_MulmedMulfrCfgRxTxtHk(const U2 u2_a_MSG)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedMulfrCfgRxTxtHk(const U2 u2_a_MSG)
{
#if 0   /* BEV BSW provisionally */
    static const U1     u1_tp_TXT_IND[MULMED_MULFR_CFG_TXTINDNUM]       = {
        (U1)0U,                                                              /* MSG_AVNMS01_RXCH1 */
        (U1)1U,                                                              /* MSG_AVNMS02_RXCH1 */
        (U1)2U,                                                              /* MSG_AVNMS03_RXCH1 */
        (U1)3U,                                                              /* MSG_AVNMS04_RXCH1 */
        (U1)4U,                                                              /* MSG_AVNMS05_RXCH1 */
        (U1)5U,                                                              /* MSG_AVNMS06_RXCH1 */
        (U1)6U,                                                              /* MSG_AVNMS07_RXCH1 */
        (U1)7U,                                                              /* MSG_AVNMS08_RXCH1 */
        (U1)8U,                                                              /* MSG_AVNMS09_RXCH1 */
        (U1)9U,                                                              /* MSG_AVNMS10_RXCH1 */
        (U1)10U,                                                             /* MSG_AVNMS13_RXCH1 */
        (U1)11U,                                                             /* MSG_AVNMS14_RXCH1 */
        (U1)12U,                                                             /* MSG_AVNMS15_RXCH1 */
        (U1)13U,                                                             /* MSG_AVNMS16_RXCH1 */
        (U1)14U,                                                             /* MSG_AVNMS18_RXCH1 */
        (U1)15U,                                                             /* MSG_AVNMS19_RXCH1 */
        (U1)16U,                                                             /* MSG_AVNMS20_RXCH1 */
        (U1)17U,                                                             /* MSG_AVNMS21_RXCH1 */
        (U1)18U,                                                             /* MSG_AVNMS22_RXCH1 */
        (U1)19U,                                                             /* MSG_AVNMS23_RXCH1 */
        (U1)20U,                                                             /* MSG_AVNMS25_RXCH1 */
        (U1)21U,                                                             /* MSG_AVNMS26_RXCH1 */
        (U1)22U,                                                             /* MSG_AVNMS27_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS31_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS32_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS33_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS34_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS35_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS36_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS37_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS38_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS39_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS40_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS41_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS42_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS43_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS44_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS45_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS46_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS47_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS48_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS49_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS50_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS51_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS52_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS53_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS55_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS56_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS57_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS58_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS72_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS73_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS74_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS75_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS76_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS77_RXCH1 */
        (U1)U1_MAX,                                                          /* MSG_AVNMS78_RXCH1 */
        (U1)23U                                                              /* MSG_AVNMS79_RXCH1 */
    };
    
    ST_MULMED_MULFR_RX_TXTDAT *                 stp_t_txtdat;
    U1                                          u1_t_buffofs;
    U1                                          u1_t_index;


    u1_t_index = u1_tp_TXT_IND[u2_a_MSG - u2_g_MULMED_MULFR_AUB_MIN];
    if(u1_t_index != (U1)U1_MAX){
        stp_t_txtdat = &st_sp_mulmed_mulfr_dat[u1_t_index];
        u1_t_buffofs = stp_t_txtdat->u1_rxcnt * (U1)MULMED_MULFR_CAN_DLC;
        if (stp_t_txtdat->u1_rxcnt < (U1)MULMED_MULFR_NUM_TXT_MSG) {
            (void)Com_ReadIPDU((PduIdType)u2_a_MSG, &stp_t_txtdat->u1p_rxbuff[u1_t_buffofs]);
            stp_t_txtdat->u1_rxcnt++;
        }
    }
#endif
}

/*===================================================================================================================================*/
/* void            vd_g_MulmedMulfrCfgTxSyncID(const U4 u4_a_MSGIDX, const U1 u1_a_VALUE)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_MulmedMulfrCfgTxSyncID(const U4 u4_a_MSGIDX, const U1 u1_a_VALUE)
{
#if 0   /* BEV BSW provisionally */
    static  const   ST_MULMED_MULFR_TX          st_sp_TX_MSGS[MULMED_MULFR_NUM_FR]                      = {
        {   (U2)MSG_METMS02_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgGPCHGM                          },  /* MSG_AVNMS01_RXCH1 */
        {   (U2)MSG_METMS02_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgCTSTCHGM                        },  /* MSG_AVNMS02_RXCH1 */
        {   (U2)MSG_METMS02_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgNXSTCHGM                        },  /* MSG_AVNMS03_RXCH1 */
        {   (U2)MSG_METMS03_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgNM1CHGM                         },  /* MSG_AVNMS04_RXCH1 */
        {   (U2)MSG_METMS03_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgNM2CHGM                         },  /* MSG_AVNMS05_RXCH1 */
        {   (U2)MSG_METMS04_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgTTLCHGADOM                      },  /* MSG_AVNMS06_RXCH1 */
        {   (U2)MSG_METMS04_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgSTA1CHGAUDIOM                   },  /* MSG_AVNMS07_RXCH1 */
        {   (U2)MSG_METMS04_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgSTA2CHGAUDIOM                   },  /* MSG_AVNMS08_RXCH1 */
        {   (U2)MSG_METMS04_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgSTA3CHGAUDIOM                   },  /* MSG_AVNMS09_RXCH1 */
        {   (U2)MSG_METMS04_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgSTA4CHGAUDIOM                   },  /* MSG_AVNMS10_RXCH1 */
        {   (U2)MSG_METMS05_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgLSTCHGRDOUS1M                   },  /* MSG_AVNMS13_RXCH1 */
        {   (U2)MSG_METMS05_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgLSTCHGRDOUS2M                   },  /* MSG_AVNMS14_RXCH1 */
        {   (U2)MSG_METMS05_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgLSTCHGRDOUS3M                   },  /* MSG_AVNMS15_RXCH1 */
        {   (U2)MSG_METMS05_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgLSTCHGRDOUS4M                   },  /* MSG_AVNMS16_RXCH1 */
        {   (U2)MSG_METMS05_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgLSTCHGRDOUS5M                   },  /* MSG_AVNMS18_RXCH1 */
        {   (U2)MSG_METMS05_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgLSTCHGRDOUS6M                   },  /* MSG_AVNMS19_RXCH1 */
        {   (U2)MSG_METMS06_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgLSTCHGCMNM                      },  /* MSG_AVNMS20_RXCH1 */
        {   (U2)MSG_METMS10_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgFAVCHGM                         },  /* MSG_AVNMS21_RXCH1 */
        {   (U2)MSG_METMS10_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgHSTCHGM                         },  /* MSG_AVNMS22_RXCH1 */
        {   (U2)MSG_METMS10_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgCDCHGM                          },  /* MSG_AVNMS23_RXCH1 */
        {   (U2)MSG_METMS11_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgRTCHGVRM                        },  /* MSG_AVNMS25_RXCH1 */
        {   (U2)MSG_METMS11_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgGTCHGVRM                        },  /* MSG_AVNMS26_RXCH1 */
        {   (U2)MSG_METMS11_TXCH1,         (U1)FALSE,         &u1_s_MulmedMulfrCfgCTCHGVRM                        },  /* MSG_AVNMS27_RXCH1 */
        {   (U2)MSG_METMS02_TXCH1,         (U1)TRUE,          &u1_s_MulmedMulfrCfgDISTCHGM                        }   /* MSG_AVNMS79_RXCH1 */
    };
    U1                                          u1_t_presndval;


    u1_t_presndval = st_sp_TX_MSGS[u4_a_MSGIDX].fp_u1_SGNLFUNC(u1_a_VALUE);
    if ((u1_t_presndval != u1_a_VALUE) && (st_sp_TX_MSGS[u4_a_MSGIDX].u1_txflag ==(U1)TRUE)) {
        Com_TriggerIPDUSend((PduIdType)(st_sp_TX_MSGS[u4_a_MSGIDX].u2_msg));
    }
#endif
}


/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS01(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS01(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_NAV_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_GP_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS02(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS02(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_NAV_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_CTST_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS03(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS03(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_NAV_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_NXST_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS04(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS04(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_TEL_MODE1, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_NM1_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS05(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS05(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_TEL_MODE1, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_NM2_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS06(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS06(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE1, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_TTL_CHG_ADO, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS07(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS07(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_STA1_CHG_AUDIO, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS08(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS08(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_STA2_CHG_AUDIO, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS09(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS09(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_STA3_CHG_AUDIO, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS10(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS10(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_STA4_CHG_AUDIO, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS13(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS13(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE3, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS1, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS14(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS14(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE4, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS2, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS15(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS15(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE4, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS3, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS16(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS16(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE4, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS4, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS18(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS18(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE4, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS5, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS19(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS19(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE4, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS6, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS20(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS20(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUDIO_MODE_CMN, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_CMN, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS21(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS21(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_TEL_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_FAV_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS22(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS22(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_TEL_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_HST_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS23(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS23(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_TEL_MODE2, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_CD_CHG, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS25(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS25(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_VR_DISP_STAT, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_RT_CHG_VR, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS26(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS26(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_VR_DISP_STAT, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_GT_CHG_VR, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS27(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS27(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_VR_DISP_STAT, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_CT_CHG_VR, u1p_a_syncid);
#endif
}

/*===================================================================================================================================*/
/* static  void    vd_s_MulmedMulfrCfgSgnlAVNMS79(U1 * u1p_a_modeid, U1 * u1p_a_syncid)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_MulmedMulfrCfgSgnlAVNMS79(U1 * u1p_a_modeid, U1 * u1p_a_syncid)
{
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_NAV_MODE12, u1p_a_modeid);
    (void)Com_ReceiveSignal(ComConf_ComSignal_DIST_CHG, u1p_a_syncid);
#endif
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgGPCHGM(const U1 u1_a_VALUE)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgGPCHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_GP_CHG_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_GP_CHG_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgCTSTCHGM(const U1 u1_a_VALUE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgCTSTCHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_CTST_CHG_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_CTST_CHG_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgNXSTCHGM(const U1 u1_a_VALUE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgNXSTCHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_NXST_CHG_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_NXST_CHG_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgNM1CHGM(const U1 u1_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgNM1CHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_NM1_CHG_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_NM1_CHG_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgNM2CHGM(const U1 u1_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgNM2CHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_NM2_CHG_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_NM2_CHG_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgTTLCHGADOM(const U1 u1_a_VALUE)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgTTLCHGADOM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_TTL_CHG_ADO_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_TTL_CHG_ADO_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgSTA1CHGAUDIOM(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgSTA1CHGAUDIOM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_STA1_CHG_AUDIO_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_STA1_CHG_AUDIO_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgSTA2CHGAUDIOM(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgSTA2CHGAUDIOM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_STA2_CHG_AUDIO_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_STA2_CHG_AUDIO_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgSTA3CHGAUDIOM(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgSTA3CHGAUDIOM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_STA3_CHG_AUDIO_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_STA3_CHG_AUDIO_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgSTA4CHGAUDIOM(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgSTA4CHGAUDIOM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_STA4_CHG_AUDIO_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_STA4_CHG_AUDIO_M, &u1_a_VALUE); */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_STA4_CHG_AUDIO_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS1M(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS1M(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS1_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS1_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS1_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS2M(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS2M(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS2_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS2_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS2_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS3M(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS3M(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS3_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS3_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS3_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS4M(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS4M(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS4_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS4_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS4_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS5M(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS5M(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS5_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS5_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS5_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS6M(const U1 u1_a_VALUE)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgLSTCHGRDOUS6M(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_RDOUS6_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS6_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_RDOUS6_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgLSTCHGCMNM(const U1 u1_a_VALUE)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgLSTCHGCMNM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_LST_CHG_CMN_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_CMN_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_LST_CHG_CMN_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgFAVCHGM(const U1 u1_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgFAVCHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_FAV_CHG_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_FAV_CHG_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_FAV_CHG_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgHSTCHGM(const U1 u1_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgHSTCHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_HST_CHG_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_HST_CHG_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_HST_CHG_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgCDCHGM(const U1 u1_a_VALUE)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgCDCHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_CD_CHG_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_CD_CHG_M, &u1_a_VALUE);     */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_CD_CHG_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgRTCHGVRM(const U1 u1_a_VALUE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgRTCHGVRM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_RT_CHG_VR_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_RT_CHG_VR_M, &u1_a_VALUE); */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_RT_CHG_VR_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgGTCHGVRM(const U1 u1_a_VALUE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgGTCHGVRM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_GT_CHG_VR_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_GT_CHG_VR_M, &u1_a_VALUE); */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_GT_CHG_VR_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgTTLCHGVRM(const U1 u1_a_VALUE)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgCTCHGVRM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
    /* (void)Com_ReceiveSignal(ComConf_ComSignal_CT_CHG_VR_M, &u1_t_presndval); */
    /* (void)Com_SendSignal(   ComConf_ComSignal_CT_CHG_VR_M, &u1_a_VALUE); */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(   ComConf_ComSignal_CT_CHG_VR_M, &u1_t_presndval);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/* static  U1      u1_s_MulmedMulfrCfgDISTCHGM(const U1 u1_a_VALUE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_MulmedMulfrCfgDISTCHGM(const U1 u1_a_VALUE)
{
    U1          u1_t_presndval;


    u1_t_presndval = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_DIST_CHG_M, &u1_t_presndval);
    (void)Com_SendSignal(   ComConf_ComSignal_DIST_CHG_M, &u1_a_VALUE);    /* COM Tx STUB delete */
#endif
    return (u1_t_presndval);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/03/2018  HY       New.                                                                                               */
/*  1.1.0    10/14/2021  KT       config for 22-24FGM.                                                                               */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * KT   = Kou Tsujii, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
