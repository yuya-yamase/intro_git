/* 1.2.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota Diag on CAN XID / Message Authentication                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TYDOCAN_XID_MA_CFG_H
#define TYDOCAN_XID_MA_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_XID_MA_CFG_H_MAJOR               (1U)
#define TYDOCAN_XID_MA_CFG_H_MINOR               (2U)
#define TYDOCAN_XID_MA_CFG_H_PATCH               (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "int_drv.h"

#include "memcpy_u1.h"
#include "memfill_u1.h"
#include "memcpy_u4.h"
#include "memfill_u4.h"

#include "aip_common.h"
#include "oxcan.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_KZK_NUM_RX                          (2U)
#define TYDC_KZK_RX_D902                         (0U)  /* RID 0xD902      */
#define TYDC_KZK_RX_D903                         (1U)  /* RID 0xD903      */

#define TYDC_KZK_RX_PDU_1                        (0U)  /* KZKSEND1        */
#define TYDC_KZK_RX_PDU_2                        (1U)  /* KZKSEND2        */
#define TYDC_KZK_RX_PDU_3                        (2U)  /* KZKSEND3        */
#define TYDC_KZK_RX_PDU_4                        (3U)  /* KZKSEND4        */
#define TYDC_KZK_RX_PDU_5                        (4U)  /* KZKSEND5        */
#define TYDC_KZK_RX_PDU_6                        (5U)  /* KZKSEND6        */
#define TYDC_KZK_RX_PDU_7                        (6U)  /* KZKSEND7        */
#define TYDC_KZK_RX_PDU_8                        (7U)  /* KZKSEND8        */

#define TYDC_KZK_RX_PDU_IU                       (0U)  /* KZKID, KZKUSAGE */
#define TYDC_KZK_RX_PDU_11                       (1U)  /* KZKVER11        */
#define TYDC_KZK_RX_PDU_12                       (2U)  /* KZKVER12        */
#define TYDC_KZK_RX_PDU_13                       (3U)  /* KZKVER13        */
#define TYDC_KZK_RX_PDU_14                       (4U)  /* KZKVER14        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_DATA_REA_ANS_NB_A901                (16U)

#define OXDC_ROUT_STA_REQ_NB_D902                (0U)
#define OXDC_ROUT_STA_ANS_NB_D902                (1U)

#define OXDC_ROUT_STA_REQ_NB_D903                (0U)
#define OXDC_ROUT_STA_ANS_NB_D903                (1U)

#define OXDC_ROUT_STA_REQ_NB_D904                (64U)
#define OXDC_ROUT_STA_ANS_NB_D904                (50U)

#define OXDC_ROUT_RES_REQ_NB_D904                (0U)
#define OXDC_ROUT_RES_ANS_NB_D904                (50U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U1 *     u1p_KZK_RX;
    U2             u2_pdu_min;
    U2             u2_pdu_max;
}ST_TYDC_KZK_RX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)     ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))
void    vd_g_TyDoCANXidMaInit(void);
void    vd_g_TyDoCANXidMaMainTask(const ST_OXDC_REQ * st_ap_REQ);
U1      u1_g_oXDoCANDtcTrchk_U13A0(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_U2300(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_U2301(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_U2B19(const U2 u2_a_ELPSD);
U1      u1_g_oXDoCANDtcTrchk_U2B1A(const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANRebyId_A901(U1 * u1_ap_ans, const U2 u2_a_ELPSD);         /* Safe Key Number */

U1      u1_g_oXDoCANRoutCorchk_D904(const U1 u1_a_SUBF, const U1 * u1_ap_COR);
U1      u1_g_oXDoCANRoutStart_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutRslt_D904(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

U1      u1_g_oXDoCANRoutStart_D902(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);
U1      u1_g_oXDoCANRoutStart_D903(U1 * u1_ap_ans, const U2 u2_a_ELPSD, U2 * u2_ap_nbyte);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANXidMaCfgSafeKeyNum(U1 * u1_ap_skn);             /* Return TRUE = Valid, FALSE = Invalid                          */
                                                                    /* The array size of u1_ap_skn = TYDC_DATA_REA_NB_A901 and it's  */
                                                                    /* tested in oxdocan_rebyid.c                                    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TyDoCANXidMaCfgInputVoltVal(void);                     /* Return the input Voltage value to record                      */
                                                                    /* in UserDefinedDTC:2300 / 2301                                 */
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && .. */
                                                                    
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_TYDC_KZK_RX    st_gp_TYDC_KZK_RX[TYDC_KZK_NUM_RX];

#endif      /* TYDOCAN_XID_MA_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see tydocan_xid_ma.c                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
