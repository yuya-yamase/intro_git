/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* TyDoCAN Service Application Layer / DID 0xF191                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_MET_DID_F191_C_MAJOR             (1)
#define TYDOCAN_MET_DID_F191_C_MINOR             (0)
#define TYDOCAN_MET_DID_F191_C_PATCH             (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxdocan_saif.h"
#include "tydocan_sal.h"

#include "memcpy_u1.h"
#include "memfill_u1.h"

#include "product.h"
#include "lcom_spi_dsal.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_ECU_MINOR                           (0x30U)        /* ASCII CODE 0x30 = "0"                          */
#define OXDC_ECUID_F191_BYTE0                    (0U)
#define OXDC_ECUID_F191_BYTE1                    (1U)
#define OXDC_ECUID_F191_BYTE2                    (2U)           /* ECUID(MET) Start Byte                          */

#define OXDC_ECUID_F191_BYTE15                   (15U)          /* ECUID(HUD) Start Byte                          */
#define OXDC_ECUID_F191_BYTE26                   (26U)          /* ECUID(HUD) Minosr 1st number Start Byte        */
#define OXDC_ECUID_F191_BYTE27                   (27U)          /* ECUID(HUD) Minosr 2nd number Start Byte        */

#define OXDC_ECUID_F191_BYTE28                   (28U)          /* ECUID(EXTDISP) Start Byte                      */
#define OXDC_ECUID_F191_BYTE39                   (39U)          /* ECUID(EXTDISP) Minosr 2nd number Start Byte    */
#define OXDC_ECUID_F191_BYTE40                   (40U)          /* ECUID(EXTDISP) Minosr 2nd number Start Byte    */

#define OXDC_ECUID_F191_ECUNUM                   (0x03U)        /* The output number of ECU Parts Number          */
#define OXDC_ECUID_F191_LENGTH                   (0x0CU)        /* The Length of ECU Parts Number:12digit         */
#define OXDC_ECUID_F191_METID                    (0x01U)        /* ECUID(MET) 0x01 M_MMPHA6DI-CSTD                */
#define OXDC_ECUID_F191_HUDID                    (0x02U)        /* ECUID(HUD) 0x02 M_MMPHA6DI-CSTD                */
#define OXDC_ECUID_F191_EXTDISPID                (0x03U)        /* ECUID(EXTDISP) 0x03 M_MMPHA6DI-CSTD            */

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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_F191(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_F191(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    U1                     u1_tp_pn_tx[OXDC_DATA_REA_ANS_NB_F191];
    U1                     u1_t_pn_chk;
    U1                     u1_t_proc;

    vd_g_MemfillU1(u1_tp_pn_tx, (U1)0x3FU, (U4)OXDC_DATA_REA_ANS_NB_F191);
    u1_tp_pn_tx[OXDC_ECUID_F191_BYTE0]  = (U1)OXDC_ECUID_F191_ECUNUM;
    u1_tp_pn_tx[OXDC_ECUID_F191_BYTE1]  = (U1)OXDC_ECUID_F191_LENGTH;
    /* ECU ID(MET)*/
    u1_tp_pn_tx[OXDC_ECUID_F191_BYTE2]  = (U1)OXDC_ECUID_F191_METID;         /* ECU ID(MET) = 0x01 M_MMPHA6DI-CSTD           */
    u1_t_pn_chk = u1_g_Product((U1)PRDCT_PN_ECU_PN, &u1_tp_pn_tx[OXDC_ECUID_F191_BYTE2 + 1U], (U1)PRDCT_ECU_PN_NBYTE);
    /*    (OXDC_ECUID_F191_BYTE2 + 1U) for MET Product Number Start Position        */

    /* ECU ID(HUD)*/
    u1_tp_pn_tx[OXDC_ECUID_F191_BYTE15] = (U1)OXDC_ECUID_F191_HUDID;         /* ECU ID(HUD) = 0x02 M_MMPHA6DI-CSTD           */
    u1_t_pn_chk  &= u1_g_LComSpiSpnRx((U1)LCOM_SPI_SPN_RX_HUD, &u1_tp_pn_tx[OXDC_ECUID_F191_BYTE15 + 1U], (U1)LCOM_SPI_SPN_NB_HUD);
    /*    (OXDC_ECUID_F191_BYTE15 + 1U) for HUD Product Number Start Position       */
    if(u1_t_pn_chk == (U1)TRUE){
        u1_tp_pn_tx[OXDC_ECUID_F191_BYTE26] = (U1)OXDC_ECU_MINOR;
        u1_tp_pn_tx[OXDC_ECUID_F191_BYTE27] = (U1)OXDC_ECU_MINOR;
    }
    else{
        /*Do Nothing*/
    }

    /* ECU ID(EXTDISP)*/
    u1_tp_pn_tx[OXDC_ECUID_F191_BYTE28] = (U1)OXDC_ECUID_F191_EXTDISPID;     /* ECU ID(EXTDISP) = 0x03 M_MMPHA6DI-CSTD       */
    u1_t_pn_chk  &= u1_g_LComSpiSpnRx((U1)LCOM_SPI_SPN_RX_DISP, &u1_tp_pn_tx[OXDC_ECUID_F191_BYTE28 + 1U], (U1)LCOM_SPI_SPN_NB_DISP);
    /*    (OXDC_ECUID_F191_BYTE28 + 1U) for EXTDISP Product Number Start Position   */
    if(u1_t_pn_chk == (U1)TRUE){
        u1_tp_pn_tx[OXDC_ECUID_F191_BYTE39] = (U1)OXDC_ECU_MINOR;
        u1_tp_pn_tx[OXDC_ECUID_F191_BYTE40] = (U1)OXDC_ECU_MINOR;
    }
    else{
        /*Do Nothing*/
    }

    vd_g_MemcpyU1(u1_ap_ans, &u1_tp_pn_tx[0], (U4)OXDC_DATA_REA_ANS_NB_F191);
    u1_t_proc = (U1)OXDC_SAL_PROC_FIN;

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/ 30/2024  TK       New.                                                                                              */
/*                                                                                                                                   */
/*  * TK = Toru Kamishina, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
