/* 2.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vadef Electrical System Option.                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_ESOPT_ZN11S19_C_MAJOR             (2)
#define VARDEF_ESOPT_ZN11S19_C_MINOR             (5)
#define VARDEF_ESOPT_ZN11S19_C_PATCH             (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_esopt_cfg_private.h"
#include "vardef_esopt_rx.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_ESOPT_ZN11S19_C_MAJOR != VARDEF_ESOPT_RX_H_MAJOR) || \
     (VARDEF_ESOPT_ZN11S19_C_MINOR != VARDEF_ESOPT_RX_H_MINOR) || \
     (VARDEF_ESOPT_ZN11S19_C_PATCH != VARDEF_ESOPT_RX_H_PATCH))
#error "vardef_esopt_ZN11S19.c and vardef_esopt_rx.h : source and header files are inconsistent!"
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
/*  U1      u1_g_VdfEsoRx_SW_OMRBB(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_OMRBB(void)
{
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_FNC, &u1_t_rx);
    if(u1_t_rx != (U1)0U){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_OMRBB_MLRSEL(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_OMRBB_MLRSEL(void)
{
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MLR_FNC, &u1_t_rx);
    if(u1_t_rx != (U1)0U){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_OMRBB_REVERSE(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_OMRBB_REVERSE(void)
{
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RLM_FNC, &u1_t_rx);
    if(u1_t_rx != (U1)0U){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_OMRBB_AUTO(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_OMRBB_AUTO(void)
{
    static const U1    u1_s_VDF_ESO_OMRBB_MRTR_ON = (U1)1U;
    static const U1    u1_s_VDF_ESO_OMRBB_ARTR_ON = (U1)1U;
    U1                 u1_t_rx_mrtr;
    U1                 u1_t_rx_artr;    
    U1                 u1_t_ava_rx;

    u1_t_rx_mrtr = (U1)0U;
    u1_t_rx_artr = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MRTR_FNC, &u1_t_rx_mrtr);
    (void)Com_ReceiveSignal(ComConf_ComSignal_ARTR_FNC, &u1_t_rx_artr);
    if((u1_t_rx_mrtr == u1_s_VDF_ESO_OMRBB_MRTR_ON) && (u1_t_rx_artr == u1_s_VDF_ESO_OMRBB_ARTR_ON)){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_OMRBB_NONAUTO(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_OMRBB_NONAUTO(void)
{
    static const U1    u1_s_VDF_ESO_OMRBB_MRTR_ON = (U1)1U;
    static const U1    u1_s_VDF_ESO_OMRBB_ARTR_OFF = (U1)0U;
    U1                 u1_t_rx_mrtr;
    U1                 u1_t_rx_artr;  
    U1                 u1_t_ava_rx;

    u1_t_rx_mrtr = (U1)0U;
    u1_t_rx_artr = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MRTR_FNC, &u1_t_rx_mrtr);
    (void)Com_ReceiveSignal(ComConf_ComSignal_ARTR_FNC, &u1_t_rx_artr);
    if((u1_t_rx_mrtr == u1_s_VDF_ESO_OMRBB_MRTR_ON) && (u1_t_rx_artr == u1_s_VDF_ESO_OMRBB_ARTR_OFF)) {
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_OBBPWL(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inactive)                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_OBBPWL(void)
{
    static const U1 u1_s_VDF_ESO_SW_OBBPWL_ACT = (U1)1U;

    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PWL_PRE, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_OBBPWL_ACT){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_SERVICE_POS(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inactive)                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_SERVICE_POS(void)
{
    static const U1 u1_s_VDF_ESO_SW_SERVICE_POS_ACT = (U1)1U;

    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_WSVS_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_SERVICE_POS_ACT){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_AUT(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_AUT(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_AUT = (U1)2U;
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_DRL = (U1)2U;

    U1                 u1_t_autfnc;
    U1                 u1_t_drlfnc;
    U1                 u1_t_ava_rx;

    u1_t_autfnc = (U1)0U;
    u1_t_drlfnc = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_AUT_FNC, &u1_t_autfnc);
    (void)Com_ReceiveSignal(ComConf_ComSignal_DRL_FNC, &u1_t_drlfnc);

    if((u1_t_autfnc == u1_s_VDF_ESO_SW_HEDLMP_AUT) &&
       (u1_t_drlfnc != u1_s_VDF_ESO_SW_HEDLMP_DRL)){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_HED(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_HED(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_HED = (U1)2U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HED_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_HEDLMP_HED){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_TAL(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_TAL(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_TAL = (U1)2U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TAL_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_HEDLMP_TAL){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_TAL_DBL(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_TAL_DBL(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_TAL_DBL = (U1)3U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TAL_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_HEDLMP_TAL_DBL){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_DRLOFF(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_DRLOFF(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_DRLOFF = (U1)2U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_OFF_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_HEDLMP_DRLOFF){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_OFF(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_OFF(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_OFF = (U1)3U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_OFF_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_HEDLMP_OFF){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_OFF_DBL(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_OFF_DBL(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_OFF_DBL = (U1)4U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_OFF_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_HEDLMP_OFF_DBL){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_HEDLMP_DRL(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_HEDLMP_DRL(void)
{
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_DRL = (U1)2U;
    static const U1 u1_s_VDF_ESO_SW_HEDLMP_AUT = (U1)2U;

    U1                 u1_t_drlfnc;
    U1                 u1_t_autfnc;
    U1                 u1_t_ava_rx;

    u1_t_drlfnc = (U1)0U;
    u1_t_autfnc = (U1)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_DRL_FNC, &u1_t_drlfnc);
    (void)Com_ReceiveSignal(ComConf_ComSignal_AUT_FNC, &u1_t_autfnc);

    if((u1_t_drlfnc == u1_s_VDF_ESO_SW_HEDLMP_DRL) &&
       (u1_t_autfnc != u1_s_VDF_ESO_SW_HEDLMP_AUT)){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_FRONT_FOG(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_FRONT_FOG(void)
{
    static const U1 u1_s_VDF_ESO_SW_FRONT_FOG = (U1)2U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FOG_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_FRONT_FOG){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdfEsoRx_SW_REAR_FOG(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ava_rx  : signal status (active/inable)                                                                  */
/*===================================================================================================================================*/
U1      u1_g_VdfEsoRx_SW_REAR_FOG(void)
{
    static const U1 u1_s_VDF_ESO_SW_REAR_FOG = (U1)2U;
    U1                 u1_t_rx;
    U1                 u1_t_ava_rx;

    u1_t_rx = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RFG_FNC, &u1_t_rx);
    if(u1_t_rx == u1_s_VDF_ESO_SW_REAR_FOG){
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_ACT;
    }
    else{
        u1_t_ava_rx = (U1)VDF_ESO_AVA_RX_INA;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.5.0    10/10/2024   KT      Newly Created                                                                                      */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV      10/10/2024   KT      Added function for BEV System_Consideration_1.(MET-B_OMRBB-CSTD-0-)                                */
/*  BEV-2    12/03/2024   HY      Added function for BEV System_Consideration_1.(MET-B_PWLBB-CSTD-0-)                                */
/*  BEV-3    12/16/2024   HT      Added function for BEV System_Consideration_1.(MET-B_WPBB-CSTD-0-)                                 */
/*  BEV-4     2/10/2025   HF      Added function for BEV System_Consideration_1.(MET-B_LMPBB-CSTD-0-)                                */
/*                                                                                                                                   */
/*  * KT = Kenta Takaji, Denso Techno                                                                                                */
/*  * HY = Haruki Yagi, KSE                                                                                                          */
/*  * HT = Hibiki Tanii, KSE                                                                                                         */
/*  * HF = Hinari Fukamachi, KSE                                                                                                     */
/*===================================================================================================================================*/
