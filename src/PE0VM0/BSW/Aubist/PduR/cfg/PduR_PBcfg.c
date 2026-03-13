/* pdur_pbcfg_c_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PDUR/PBCFG/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_pdur_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )

#include <pdur/bsw_pdur.h>

#include "../inc/bsw_pdur_rt.h"
#include "PduR_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/******************************************/
/*                                        */
/* Upper Component I-PDU Table            */
/*                                        */
/******************************************/
/* I-PDU Table */
#if ( BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE )

#if ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) && (BSW_PDUR_CFG_MSGCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2ComRoutingTbl[BSW_PDUR_CFG_MSGCOM_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
    ((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0000U)  /* [0] up:BDC1S81_Rx_CANFD_G2M_1_BUS, low:BDC1S81_Rx_CANFD_G2M_1_BUS */
   ,((BswU2)BSW_PDUR_LOCOMP_CANIF  | (BswU2)0x0001U)  /* [1] up:BDC1S91_Rx_CANFD_G2M_2_BUS, low:BDC1S91_Rx_CANFD_G2M_2_BUS */
};
#endif

#if ( ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) && (BSW_PDUR_CFG_MSGDCM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DcmRoutingTbl[BSW_PDUR_CFG_MSGDCM_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) && (BSW_PDUR_CFG_MSGLDCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LdComRoutingTbl[BSW_PDUR_CFG_MSGLDCOM_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD1_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1RoutingTbl[BSW_PDUR_CFG_MSGCDD1_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD2_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2RoutingTbl[BSW_PDUR_CFG_MSGCDD2_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPUP_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpUpRoutingTbl[BSW_PDUR_CFG_MSGJ1939TPUP_NUM] =
{
    /* PDU ID (Lower Component | ID)   */
};
#endif

#endif /* (BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE) */


/******************************************/
/*                                        */
/* Lower Component I-PDU Table            */
/*                                        */
/******************************************/
#if ( BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE )

#if ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stCanIfRoutingTbl[BSW_PDUR_CFG_MSGCANIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
    { ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0000U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [0] up:BDC1S81_Rx_CANFD_G2M_1_BUS, low:BDC1S81_Rx_CANFD_G2M_1_BUS */
   ,{ ((BswU2)BSW_PDUR_UPCOMP_COM      | (BswU2)0x0001U),    (BswU2)BSW_PDUR_INVALID_PDUID }                      /* [1] up:BDC1S91_Rx_CANFD_G2M_2_BUS, low:BDC1S91_Rx_CANFD_G2M_2_BUS */
};
#endif /* ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stLinIfRoutingTbl[BSW_PDUR_CFG_MSGLINIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stSoAdIfRoutingTbl[BSW_PDUR_CFG_MSGSOADIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stDoIPIfRoutingTbl[BSW_PDUR_CFG_MSGDOIPIF_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) && (BSW_PDUR_CFG_MSGCANTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stCanTpRoutingTbl[BSW_PDUR_CFG_MSGCANTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) && (BSW_PDUR_CFG_MSGCANTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) && (BSW_PDUR_CFG_MSGLINTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stLinTpRoutingTbl[BSW_PDUR_CFG_MSGLINTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) && (BSW_PDUR_CFG_MSGLINTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stSoAdTpRoutingTbl[BSW_PDUR_CFG_MSGSOADTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPTP_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stDoIPTpRoutingTbl[BSW_PDUR_CFG_MSGDOIPTP_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPTP_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) )
BswConst Bsw_PduR_RoutingType bsw_pdur_stJ1939TpLoRoutingTbl[BSW_PDUR_CFG_MSGJ1939TPLO_NUM] =
{
    /* I-PDU ID (Upper Component | ID)           ,    SecOC ID                      */
};
#endif /* ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) ) */

/******************************************/
/*                                        */
/* IpduM I-PDU Table                      */
/*                                        */
/******************************************/
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )

#if ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) && (BSW_PDUR_CFG_MSGCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2ComIpduMTbl[BSW_PDUR_CFG_MSGCOM_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) && (BSW_PDUR_CFG_MSGDCM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DcmIpduMTbl[BSW_PDUR_CFG_MSGDCM_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) && (BSW_PDUR_CFG_MSGLDCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LdComIpduMTbl[BSW_PDUR_CFG_MSGLDCOM_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD1_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1IpduMTbl[BSW_PDUR_CFG_MSGCDD1_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD2_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2IpduMTbl[BSW_PDUR_CFG_MSGCDD2_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPUP_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpUpIpduMTbl[BSW_PDUR_CFG_MSGJ1939TPUP_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2CanIfIpduMTbl[BSW_PDUR_CFG_MSGCANIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) && (BSW_PDUR_CFG_MSGCANIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LinIfIpduMTbl[BSW_PDUR_CFG_MSGLINIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) && (BSW_PDUR_CFG_MSGLINIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2SoAdIfIpduMTbl[BSW_PDUR_CFG_MSGSOADIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DoIPIfIpduMTbl[BSW_PDUR_CFG_MSGDOIPIF_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) && (BSW_PDUR_CFG_MSGDOIPIF_NUM != 0U) ) */

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpLoIpduMTbl[BSW_PDUR_CFG_MSGJ1939TPLO_NUM] =
{
    /* IpduM I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPLO_NUM != 0U) ) */

#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */

/******************************************/
/*                                        */
/* SomeIpTp I-PDU Table                   */
/*                                        */
/******************************************/
#if ( BSW_BSWM_CS_FUNC_SOMEIPTP == BSW_USE )

#if ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2SoAdIfSomeIpTpTbl[BSW_PDUR_CFG_MSGSOADIF_NUM] =
{
    /* SomeIpTp I-PDU ID */
};
#endif /* ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADIF_NUM != 0U) ) */

#endif /* (BSW_BSWM_CS_FUNC_SOMEIPTP == BSW_USE) */

/******************************************/
/*                                        */
/* SecOC I-PDU Table                      */
/*                                        */
/******************************************/
#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) && (BSW_PDUR_CFG_IPDU_MA == BSW_USE) )

#if ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) && (BSW_PDUR_CFG_MSGCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2ComSecOCTbl[BSW_PDUR_CFG_MSGCOM_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) && (BSW_PDUR_CFG_MSGDCM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2DcmSecOCTbl[BSW_PDUR_CFG_MSGDCM_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) && (BSW_PDUR_CFG_MSGLDCOM_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2LdComSecOCTbl[BSW_PDUR_CFG_MSGLDCOM_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD1_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1SecOCTbl[BSW_PDUR_CFG_MSGCDD1_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_CFG_MSGCDD2_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2SecOCTbl[BSW_PDUR_CFG_MSGCDD2_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif

#if ( (BSW_BSWM_CS_FUNC_J1939TP == BSW_USE) && (BSW_PDUR_CFG_MSGJ1939TPUP_NUM != 0U) )
BswConst PduIdType bsw_pdur_u2J1939TpUpSecOCTbl[BSW_PDUR_CFG_MSGJ1939TPUP_NUM] =
{
    /* SecOC I-PDU ID */
};
#endif
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) && (BSW_PDUR_CFG_IPDU_MA == BSW_USE) */

#endif /* (BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_NOUSE) */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (BSW_BSWM_CS_FUNC_PDUR == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/22                                             */
/*  v1-0-1          :2018/01/30                                             */
/*  v1-1-0          :2019/01/15                                             */
/*  v1-2-0          :2019/11/05                                             */
/*  v2-0-0          :2021/02/12                                             */
/*  v3-0-0          :2025/01/23                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
