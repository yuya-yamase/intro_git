/* bsw_pdur_config_c_v2-2-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/PDUR/CONFIG/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <cs/bsw_cs_system_memmap_pre.h>
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#include <cs/bsw_cs_system_memmap_post.h>

#if (BSW_BSWM_CS_FUNC_PDUR == BSW_USE)

#include <cs/bsw_cs_system_memmap_pre.h>

#include <pdur/bsw_pdur.h>
#include <com/bsw_com.h>
#include <ldcom/bsw_ldcom_cbk.h>
#include <ipdum/bsw_ipdum.h>
#include <ipdum/bsw_ipdum_cbk.h>

#include "../../BswM_CS/inc/bsw_bswm_cs_connector.h"
#include "../inc/bsw_pdur_inf.h"
#include "../inc/bsw_pdur_rt.h"
#include "../cfg/PduR_Cfg.h"

#if (BSW_BSWM_CS_FUNC_CANIF == BSW_USE)
#include <canif/bsw_canif.h>
#endif /* (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CANTP == BSW_USE)
#include "../../BswM_Can/inc/bsw_bswm_can_connector.h"
#endif /* (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) */

#include <cs/bsw_cs_system_memmap_post.h>

#if (BSW_BSWM_CS_FUNC_LINIF == BSW_USE)
#include <LinIf.h>
#endif /* (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_LINTP == BSW_USE)
#include <LinTp.h>
#endif /* (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SOAD == BSW_USE)
#include <soad/bsw_soad.h>
#endif /* (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_DOIP == BSW_USE)
#include <doip/bsw_doip.h>
#endif /* (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SECOC == BSW_USE)
#include <SecOC.h>
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE)
#include <SomeIpTp.h>
#endif /* (BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE) */

#include <cs/bsw_cs_system_memmap_pre.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Number of elements in dummy table */
#define BSW_PDUR_TBL_DUMMY_SIZE        (1U)

/* Zero cost operation definition setting */
#if( BSW_PDUR_CFG_ZEROCOSTOPERATION == BSW_USE )
#if( BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_CAN )
#define BSW_PDUR_ZEROCOSTOPERATION (BSW_PDUR_ZEROCOST_CAN)
#elif( BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_LIN )
#define BSW_PDUR_ZEROCOSTOPERATION (BSW_PDUR_ZEROCOST_LIN)
#elif( BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_ETH )
#define BSW_PDUR_ZEROCOSTOPERATION (BSW_PDUR_ZEROCOST_ETH)
#elif( BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_CDD1 )
#define BSW_PDUR_ZEROCOSTOPERATION (BSW_PDUR_ZEROCOST_CDD1)
#elif( BSW_COMM_BUSTYPE(0) == BSW_COMM_BUS_TYPE_CDD2 )
#define BSW_PDUR_ZEROCOSTOPERATION (BSW_PDUR_ZEROCOST_CDD2)
#else
#error "BSW_COMM_CFG_BUS_TYPE_0 Defined Value Illegal"
#endif
#else
#define BSW_PDUR_ZEROCOSTOPERATION (BSW_PDUR_ZEROCOST_NOUSE)
#endif

/* Switching the configuration table */
#if( BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE )
#define BSW_PDUR_COM_ROUTINGTBL        ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) ? (&bsw_pdur_u2ComRoutingTbl[0U]) : (&bsw_pdur_u2DummyUpRoutingTbl[0U]) )
#define BSW_PDUR_DCM_ROUTINGTBL        ( (BSW_BSWM_CS_FUNC_DCM == BSW_USE) ? (&bsw_pdur_u2DcmRoutingTbl[0U]) : (&bsw_pdur_u2DummyUpRoutingTbl[0U]) )
#define BSW_PDUR_LDCOM_ROUTINGTBL      ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) ? (&bsw_pdur_u2LdComRoutingTbl[0U]) : (&bsw_pdur_u2DummyUpRoutingTbl[0U]) )
#define BSW_PDUR_CDD1_ROUTINGTBL       ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) ? (&bsw_pdur_u2Cdd1RoutingTbl[0U]) : (&bsw_pdur_u2DummyUpRoutingTbl[0U]) )
#define BSW_PDUR_CDD2_ROUTINGTBL       ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) ? (&bsw_pdur_u2Cdd2RoutingTbl[0U]) : (&bsw_pdur_u2DummyUpRoutingTbl[0U]) )

#define BSW_PDUR_CANIF_ROUTINGTBL      ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) ? (&bsw_pdur_stCanIfRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_CANTP_ROUTINGTBL      ( (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) ? (&bsw_pdur_stCanTpRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_LINIF_ROUTINGTBL      ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) ? (&bsw_pdur_stLinIfRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_LINTP_ROUTINGTBL      ( (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) ? (&bsw_pdur_stLinTpRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_SOADIF_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) ? (&bsw_pdur_stSoAdIfRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_SOADTP_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) ? (&bsw_pdur_stSoAdTpRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_DOIPIF_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) ? (&bsw_pdur_stDoIPIfRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_DOIPTP_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) ? (&bsw_pdur_stDoIPTpRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_CDD1IF_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_CDD1IF == BSW_USE) ? (&bsw_pdur_stCdd1IfRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_CDD1TP_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_CDD1TP == BSW_USE) ? (&bsw_pdur_stCdd1TpRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_CDD2IF_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_CDD2IF == BSW_USE) ? (&bsw_pdur_stCdd2IfRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )
#define BSW_PDUR_CDD2TP_ROUTINGTBL     ( (BSW_BSWM_CS_FUNC_CDD2TP == BSW_USE) ? (&bsw_pdur_stCdd2TpRoutingTbl[0U]) : (&bsw_pdur_stDummyRoutingTbl[0U]) )

#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#define BSW_PDUR_COM_IPDUMLOTBL         ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) ? (&bsw_pdur_u2ComIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_DCM_IPDUMLOTBL         ( (BSW_BSWM_CS_FUNC_DCM == BSW_USE) ? (&bsw_pdur_u2DcmIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_LDCOM_IPDUMLOTBL       ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) ? (&bsw_pdur_u2LdComIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_CDD1_IPDUMLOTBL        ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) ? (&bsw_pdur_u2Cdd1IpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_CDD2_IPDUMLOTBL        ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) ? (&bsw_pdur_u2Cdd2IpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_CANIF_IPDUMLOTBL       ( (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) ? (&bsw_pdur_u2CanIfIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_LINIF_IPDUMLOTBL       ( (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) ? (&bsw_pdur_u2LinIfIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_SOADIF_IPDUMLOTBL      ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) ? (&bsw_pdur_u2SoAdIfIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_DOIPIF_IPDUMLOTBL      ( (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) ? (&bsw_pdur_u2DoIPIfIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_CDD1IF_IPDUMLOTBL      ( (BSW_BSWM_CS_FUNC_CDD1IF == BSW_USE) ? (&bsw_pdur_u2Cdd1IfIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#define BSW_PDUR_CDD2IF_IPDUMLOTBL      ( (BSW_BSWM_CS_FUNC_CDD2IF == BSW_USE) ? (&bsw_pdur_u2Cdd2IfIpduMTbl[0U]) : (&bsw_pdur_u2DummyIpduMTbl[0U]) )
#else
#define BSW_PDUR_COM_IPDUMLOTBL         (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_DCM_IPDUMLOTBL         (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_LDCOM_IPDUMLOTBL       (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_CDD1_IPDUMLOTBL        (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_CDD2_IPDUMLOTBL        (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_CANIF_IPDUMLOTBL       (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_LINIF_IPDUMLOTBL       (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_SOADIF_IPDUMLOTBL      (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_DOIPIF_IPDUMLOTBL      (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_CDD1IF_IPDUMLOTBL      (&bsw_pdur_u2DummyIpduMTbl[0U])
#define BSW_PDUR_CDD2IF_IPDUMLOTBL      (&bsw_pdur_u2DummyIpduMTbl[0U])
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */

#if ( BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE )
#define BSW_PDUR_SOADIF_SOMEIPTPLOTBL   ( (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) ? (&bsw_pdur_u2SoAdIfSomeIpTbl[0U]) : (&bsw_pdur_u2DummySomeIpTpTbl[0U]) )
#else
#define BSW_PDUR_SOADIF_SOMEIPTPLOTBL   (&bsw_pdur_u2DummySomeIpTpTbl[0U])
#endif /* (BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE) */

#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) && (BSW_PDUR_CFG_IPDU_MA == BSW_USE) )
#define BSW_PDUR_COM_SECOCUPTBL         ( (BSW_BSWM_CS_FUNC_COM == BSW_USE) ? (&bsw_pdur_u2ComSecOCTbl[0U]) : (&bsw_pdur_u2DummySecOCTbl[0U]) )
#define BSW_PDUR_DCM_SECOCUPTBL         ( (BSW_BSWM_CS_FUNC_DCM == BSW_USE) ? (&bsw_pdur_u2DcmSecOCTbl[0U]) : (&bsw_pdur_u2DummySecOCTbl[0U]) )
#define BSW_PDUR_LDCOM_SECOCUPTBL       ( (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) ? (&bsw_pdur_u2LdComSecOCTbl[0U]) : (&bsw_pdur_u2DummySecOCTbl[0U]) )
#define BSW_PDUR_CDD1_SECOCUPTBL        ( (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) ? (&bsw_pdur_u2Cdd1SecOCTbl[0U]) : (&bsw_pdur_u2DummySecOCTbl[0U]) )
#define BSW_PDUR_CDD2_SECOCUPTBL        ( (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) ? (&bsw_pdur_u2Cdd2SecOCTbl[0U]) : (&bsw_pdur_u2DummySecOCTbl[0U]) )
#else
#define BSW_PDUR_COM_SECOCUPTBL         (&bsw_pdur_u2DummySecOCTbl[0U])
#define BSW_PDUR_DCM_SECOCUPTBL         (&bsw_pdur_u2DummySecOCTbl[0U])
#define BSW_PDUR_LDCOM_SECOCUPTBL       (&bsw_pdur_u2DummySecOCTbl[0U])
#define BSW_PDUR_CDD1_SECOCUPTBL        (&bsw_pdur_u2DummySecOCTbl[0U])
#define BSW_PDUR_CDD2_SECOCUPTBL        (&bsw_pdur_u2DummySecOCTbl[0U])
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) && (BSW_PDUR_CFG_IPDU_MA == BSW_USE) */
#endif /* ( BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE ) */

/* Switching function pointers by using/not using components */
#if (BSW_BSWM_CS_FUNC_CANTX == BSW_USE)
#define BSW_PDUR_CANIF_TRANSMIT_FUNC   (&CanIf_Transmit)
#define BSW_PDUR_CANIF_CANCELTX_FUNC   (&CanIf_ClearTransmitRequest)
#define BSW_PDUR_CANIF_GETTXID_FUNC    (&CanIf_GetTxCanId)
#else
#define BSW_PDUR_CANIF_TRANSMIT_FUNC   (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_CANIF_CANCELTX_FUNC   (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_CANIF_GETTXID_FUNC    (&bsw_pdur_dummy_ComGetTxId)
#endif /* (BSW_BSWM_CS_FUNC_CANTX == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CANRX == BSW_USE)
#define BSW_PDUR_CANIF_GETRXID_FUNC    (&CanIf_GetRxCanId)
#define BSW_PDUR_CANIF_GETCURRXID_FUNC (&CanIf_GetCurrentRxCanId)
#else
#define BSW_PDUR_CANIF_GETRXID_FUNC    (&bsw_pdur_dummy_ComGetRxId)
#define BSW_PDUR_CANIF_GETCURRXID_FUNC (&bsw_pdur_dummy_ComGetCrrntRxId)
#endif /* (BSW_BSWM_CS_FUNC_CANRX == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_LINTX == BSW_USE)
#define BSW_PDUR_LINIF_TRANSMIT_FUNC   (&LinIf_Transmit)
#define BSW_PDUR_LINIF_CANCELTX_FUNC   (&LinIf_CancelTransmit)
#else
#define BSW_PDUR_LINIF_TRANSMIT_FUNC   (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_LINIF_CANCELTX_FUNC   (&bsw_pdur_dummy_CancelTransmit)
#endif /* (BSW_BSWM_CS_FUNC_LINTX == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_ETHTX == BSW_USE)
#define BSW_PDUR_SOADIF_TRANSMIT_FUNC  (&SoAd_IfTransmit)
#define BSW_PDUR_SOADIF_CANCELTX_FUNC  (&SoAd_IfCancelTransmit)
#else
#define BSW_PDUR_SOADIF_TRANSMIT_FUNC  (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_SOADIF_CANCELTX_FUNC  (&bsw_pdur_dummy_CancelTransmit)
#endif /* (BSW_BSWM_CS_FUNC_ETHTX == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD1TX == BSW_USE)
#define BSW_PDUR_CDD1IF_TRANSMIT_FUNC  (&bsw_bswm_cs_Cdd1IfTransmit)
#define BSW_PDUR_CDD1IF_CANCELTX_FUNC  (&bsw_bswm_cs_Cdd1IfCancelTransmit)
#define BSW_PDUR_CDD1IF_GETTXID_FUNC   (&bsw_bswm_cs_Cdd1IfGetTxId)
#else
#define BSW_PDUR_CDD1IF_TRANSMIT_FUNC  (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_CDD1IF_CANCELTX_FUNC  (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_CDD1IF_GETTXID_FUNC   (&bsw_pdur_dummy_ComGetTxId)
#endif /* (BSW_BSWM_CS_FUNC_CDD1TX == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD1RX == BSW_USE)
#define BSW_PDUR_CDD1IF_GETRXID_FUNC   (&bsw_bswm_cs_Cdd1IfGetRxId)
#else
#define BSW_PDUR_CDD1IF_GETRXID_FUNC   (&bsw_pdur_dummy_ComGetRxId)
#endif /* (BSW_BSWM_CS_FUNC_CANRX == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD2TX == BSW_USE)
#define BSW_PDUR_CDD2IF_TRANSMIT_FUNC  (&bsw_bswm_cs_Cdd2IfTransmit)
#define BSW_PDUR_CDD2IF_CANCELTX_FUNC  (&bsw_bswm_cs_Cdd2IfCancelTransmit)
#define BSW_PDUR_CDD2IF_GETTXID_FUNC   (&bsw_bswm_cs_Cdd2IfGetTxId)
#else
#define BSW_PDUR_CDD2IF_TRANSMIT_FUNC  (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_CDD2IF_CANCELTX_FUNC  (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_CDD2IF_GETTXID_FUNC   (&bsw_pdur_dummy_ComGetTxId)
#endif /* (BSW_BSWM_CS_FUNC_CDD1TX == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD2RX == BSW_USE)
#define BSW_PDUR_CDD2IF_GETRXID_FUNC   (&bsw_bswm_cs_Cdd2IfGetRxId)
#else
#define BSW_PDUR_CDD2IF_GETRXID_FUNC   (&bsw_pdur_dummy_ComGetRxId)
#endif /* (BSW_BSWM_CS_FUNC_CANRX == BSW_USE) */

#if( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#define BSW_PDUR_IPDUM_TRANSMIT_FUNC        (&IpduM_Transmit)
#define BSW_PDUR_IPDUM_CANCELTX_FUNC        (&IpduM_CancelTransmit)
#define BSW_PDUR_IPDUM_TRIGGERTX_FUNC       (&IpduM_TriggerTransmit)
#define BSW_PDUR_IPDUM_TXCONF_FUNC          (&IpduM_TxConfirmation)
#define BSW_PDUR_IPDUM_RXIND_FUNC           (&IpduM_RxIndication)
#else
#define BSW_PDUR_IPDUM_TRANSMIT_FUNC        (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_IPDUM_CANCELTX_FUNC        (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_IPDUM_TRIGGERTX_FUNC       (&bsw_pdur_dummy_TriggerTransmit)
#define BSW_PDUR_IPDUM_TXCONF_FUNC          (&bsw_pdur_dummy_TxConfirmation)
#define BSW_PDUR_IPDUM_RXIND_FUNC           (&bsw_pdur_dummy_RxIndication)
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */

#if( BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE )
#define BSW_PDUR_SOMEIPTP_TRANSMIT_FUNC     (&SomeIpTp_Transmit)
#define BSW_PDUR_SOMEIPTP_CANCELTX_FUNC     (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_SOMEIPTP_TRIGRTX_FUNC      (&SomeIpTp_TriggerTransmit)
#define BSW_PDUR_SOMEIPTP_TXCONF_FUNC       (&SomeIpTp_TxConfirmation)
#define BSW_PDUR_SOMEIPTP_RXIND_FUNC        (&SomeIpTp_RxIndication)
#else
#define BSW_PDUR_SOMEIPTP_TRANSMIT_FUNC     (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_SOMEIPTP_CANCELTX_FUNC     (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_SOMEIPTP_TRIGRTX_FUNC      (&bsw_pdur_dummy_TriggerTransmit)
#define BSW_PDUR_SOMEIPTP_TXCONF_FUNC       (&bsw_pdur_dummy_TxConfExt)
#define BSW_PDUR_SOMEIPTP_RXIND_FUNC        (&bsw_pdur_dummy_RxIndication)
#endif /* (BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE) */

/* Message authentication per I-PDU Used/not used */
#if( BSW_BSWM_CS_FUNC_SECOC == BSW_USE )
#define BSW_PDUR_IPDU_MA                    (BSW_PDUR_CFG_IPDU_MA)
#else
#define BSW_PDUR_IPDU_MA                    (BSW_NOUSE)
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE ) */

/******************************************/
/* Zero-cost operation               */
/******************************************/
/* Function switch */
#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_CAN)
#define BSW_PDUR_COMTRANSMIT_LOFUNC    BSW_PDUR_CANIF_TRANSMIT_FUNC
#define BSW_PDUR_COMCANCELTX_LOFUNC    BSW_PDUR_CANIF_CANCELTX_FUNC
#define BSW_PDUR_TRIGGERTX_UPFUNC      (&bsw_pdur_dummy_TriggerTransmit) /* CAN does not use TriggerTransmit */
#define BSW_PDUR_TXCONF_UPFUNC         (&Com_TxConfirmation)
#define BSW_PDUR_RXIND_UPFUNC          (&Com_RxIndication)
#define BSW_PDUR_DCMTRANSMIT_LOFUNC    (&bsw_bswm_can_CanTpTransmit)
#define BSW_PDUR_DCMCANCELTX_LOFUNC    (&bsw_bswm_can_CanTpCancelTransmit)
#define BSW_PDUR_DCMCANCELRX_LOFUNC    (&bsw_bswm_can_CanTpCancelReceive)
#define BSW_PDUR_SOR_UPFUNC            (&bsw_bswm_cs_DcmStartOfReception)
#define BSW_PDUR_COPYRXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyRxData)
#define BSW_PDUR_COPYTXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyTxData)
#define BSW_PDUR_TPRXIND_UPFUNC        (&bsw_bswm_cs_DcmTpRxIndication)
#define BSW_PDUR_TPTXCONF_UPFUNC       (&bsw_bswm_cs_DcmTpTxConfirmation)
#define BSW_PDUR_COMGETTXID_LOFUNC     BSW_PDUR_CANIF_GETTXID_FUNC
#define BSW_PDUR_COMGETRXID_LOFUNC     BSW_PDUR_CANIF_GETRXID_FUNC
#define BSW_PDUR_LDCOMTRANSMIT_LOFUNC  (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_LDCOMCANCELTX_LOFUNC  (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_COMGETTXMODE_UPFUNC   (&Com_GetCurrentTxMode)

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_LIN)
#define BSW_PDUR_COMTRANSMIT_LOFUNC    BSW_PDUR_LINIF_TRANSMIT_FUNC
#define BSW_PDUR_COMCANCELTX_LOFUNC    BSW_PDUR_LINIF_CANCELTX_FUNC
#define BSW_PDUR_TRIGGERTX_UPFUNC      (&Com_TriggerTransmit)
#define BSW_PDUR_TXCONF_UPFUNC         (&Com_TxConfirmation)
#define BSW_PDUR_RXIND_UPFUNC          (&Com_RxIndication)
#define BSW_PDUR_DCMTRANSMIT_LOFUNC    (&LinTp_Transmit)
#define BSW_PDUR_DCMCANCELTX_LOFUNC    (&LinTp_CancelTransmit)
#define BSW_PDUR_DCMCANCELRX_LOFUNC    (&LinTp_CancelReceive)
#define BSW_PDUR_SOR_UPFUNC            (&bsw_bswm_cs_DcmStartOfReception)
#define BSW_PDUR_COPYRXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyRxData)
#define BSW_PDUR_COPYTXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyTxData)
#define BSW_PDUR_TPRXIND_UPFUNC        (&bsw_bswm_cs_DcmTpRxIndication)
#define BSW_PDUR_TPTXCONF_UPFUNC       (&bsw_bswm_cs_DcmTpTxConfirmation)
#define BSW_PDUR_COMGETTXID_LOFUNC     (&bsw_pdur_dummy_ComGetTxId)
#define BSW_PDUR_COMGETRXID_LOFUNC     (&bsw_pdur_dummy_ComGetRxId)
#define BSW_PDUR_LDCOMTRANSMIT_LOFUNC  (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_LDCOMCANCELTX_LOFUNC  (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_COMGETTXMODE_UPFUNC   (&Com_GetCurrentTxMode)

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_ETH)
#define BSW_PDUR_COMTRANSMIT_LOFUNC    (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_COMCANCELTX_LOFUNC    (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_TRIGGERTX_UPFUNC      (&LdCom_TriggerTransmit)
#define BSW_PDUR_TXCONF_UPFUNC         (&LdCom_TxConfirmation)
#define BSW_PDUR_RXIND_UPFUNC          (&LdCom_RxIndication)
#define BSW_PDUR_DCMTRANSMIT_LOFUNC    (&DoIP_TpTransmit)
#define BSW_PDUR_DCMCANCELTX_LOFUNC    (&DoIP_TpCancelTransmit)
#define BSW_PDUR_DCMCANCELRX_LOFUNC    (&DoIP_TpCancelReceive)
#define BSW_PDUR_SOR_UPFUNC            (&bsw_bswm_cs_DcmStartOfReception)
#define BSW_PDUR_COPYRXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyRxData)
#define BSW_PDUR_COPYTXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyTxData)
#define BSW_PDUR_TPRXIND_UPFUNC        (&bsw_bswm_cs_DcmTpRxIndication)
#define BSW_PDUR_TPTXCONF_UPFUNC       (&bsw_bswm_cs_DcmTpTxConfirmation)
#define BSW_PDUR_COMGETTXID_LOFUNC     (&bsw_pdur_dummy_ComGetTxId)
#define BSW_PDUR_COMGETRXID_LOFUNC     (&bsw_pdur_dummy_ComGetRxId)
#define BSW_PDUR_LDCOMTRANSMIT_LOFUNC  BSW_PDUR_SOADIF_TRANSMIT_FUNC
#define BSW_PDUR_LDCOMCANCELTX_LOFUNC  BSW_PDUR_SOADIF_CANCELTX_FUNC
#define BSW_PDUR_COMGETTXMODE_UPFUNC   (&bsw_pdur_dummy_ComGetTxMode)

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_CDD1)
#define BSW_PDUR_COMTRANSMIT_LOFUNC    BSW_PDUR_CDD1IF_TRANSMIT_FUNC
#define BSW_PDUR_COMCANCELTX_LOFUNC    BSW_PDUR_CDD1IF_CANCELTX_FUNC
#define BSW_PDUR_TRIGGERTX_UPFUNC      (&Com_TriggerTransmit)
#define BSW_PDUR_TXCONF_UPFUNC         (&Com_TxConfirmation)
#define BSW_PDUR_RXIND_UPFUNC          (&Com_RxIndication)
#define BSW_PDUR_DCMTRANSMIT_LOFUNC    (&bsw_bswm_cs_Cdd1TpTransmit)
#define BSW_PDUR_DCMCANCELTX_LOFUNC    (&bsw_bswm_cs_Cdd1TpCancelTransmit)
#define BSW_PDUR_DCMCANCELRX_LOFUNC    (&bsw_bswm_cs_Cdd1TpCancelReceive)
#define BSW_PDUR_SOR_UPFUNC            (&bsw_bswm_cs_DcmStartOfReception)
#define BSW_PDUR_COPYRXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyRxData)
#define BSW_PDUR_COPYTXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyTxData)
#define BSW_PDUR_TPRXIND_UPFUNC        (&bsw_bswm_cs_DcmTpRxIndication)
#define BSW_PDUR_TPTXCONF_UPFUNC       (&bsw_bswm_cs_DcmTpTxConfirmation)
#define BSW_PDUR_COMGETTXID_LOFUNC     (&bsw_pdur_dummy_ComGetTxId)
#define BSW_PDUR_COMGETRXID_LOFUNC     (&bsw_pdur_dummy_ComGetRxId)
#define BSW_PDUR_LDCOMTRANSMIT_LOFUNC  (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_LDCOMCANCELTX_LOFUNC  (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_COMGETTXMODE_UPFUNC   (&Com_GetCurrentTxMode)

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_CDD2)
#define BSW_PDUR_COMTRANSMIT_LOFUNC    BSW_PDUR_CDD2IF_TRANSMIT_FUNC
#define BSW_PDUR_COMCANCELTX_LOFUNC    BSW_PDUR_CDD2IF_CANCELTX_FUNC
#define BSW_PDUR_TRIGGERTX_UPFUNC      (&Com_TriggerTransmit)
#define BSW_PDUR_TXCONF_UPFUNC         (&Com_TxConfirmation)
#define BSW_PDUR_RXIND_UPFUNC          (&Com_RxIndication)
#define BSW_PDUR_DCMTRANSMIT_LOFUNC    (&bsw_bswm_cs_Cdd2TpTransmit)
#define BSW_PDUR_DCMCANCELTX_LOFUNC    (&bsw_bswm_cs_Cdd2TpCancelTransmit)
#define BSW_PDUR_DCMCANCELRX_LOFUNC    (&bsw_bswm_cs_Cdd2TpCancelReceive)
#define BSW_PDUR_SOR_UPFUNC            (&bsw_bswm_cs_DcmStartOfReception)
#define BSW_PDUR_COPYRXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyRxData)
#define BSW_PDUR_COPYTXDATA_UPFUNC     (&bsw_bswm_cs_DcmCopyTxData)
#define BSW_PDUR_TPRXIND_UPFUNC        (&bsw_bswm_cs_DcmTpRxIndication)
#define BSW_PDUR_TPTXCONF_UPFUNC       (&bsw_bswm_cs_DcmTpTxConfirmation)
#define BSW_PDUR_COMGETTXID_LOFUNC     (&bsw_pdur_dummy_ComGetTxId)
#define BSW_PDUR_COMGETRXID_LOFUNC     (&bsw_pdur_dummy_ComGetRxId)
#define BSW_PDUR_LDCOMTRANSMIT_LOFUNC  (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_LDCOMCANCELTX_LOFUNC  (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_COMGETTXMODE_UPFUNC   (&Com_GetCurrentTxMode)

#else   /* Zero cost operation unused */
#define BSW_PDUR_COMTRANSMIT_LOFUNC    (&bsw_pdur_rt_ComTransmitMultiP)
#define BSW_PDUR_COMCANCELTX_LOFUNC    (&bsw_pdur_rt_ComCancelTxMultiP)
#define BSW_PDUR_TRIGGERTX_UPFUNC      (&bsw_pdur_rt_TriggerTxMultiP)
#define BSW_PDUR_TXCONF_UPFUNC         (&bsw_pdur_rt_TxConfirmMultiP)
#define BSW_PDUR_RXIND_UPFUNC          (&bsw_pdur_rt_RxIndMultiP)
#define BSW_PDUR_DCMTRANSMIT_LOFUNC    (&bsw_pdur_rt_DcmTransmitMultiP)
#define BSW_PDUR_DCMCANCELTX_LOFUNC    (&bsw_pdur_rt_DcmCancelTxMultiP)
#define BSW_PDUR_DCMCANCELRX_LOFUNC    (&bsw_pdur_rt_DcmCancelRxMultiP)
#define BSW_PDUR_SOR_UPFUNC            (&bsw_pdur_rt_SORMultiP)
#define BSW_PDUR_COPYRXDATA_UPFUNC     (&bsw_pdur_rt_CopyRxDataMultiP)
#define BSW_PDUR_COPYTXDATA_UPFUNC     (&bsw_pdur_rt_CopyTxDataMultiP)
#define BSW_PDUR_TPRXIND_UPFUNC        (&bsw_pdur_rt_TpRxIndMultiP)
#define BSW_PDUR_TPTXCONF_UPFUNC       (&bsw_pdur_rt_TpTxConfirmMultiP)
#define BSW_PDUR_COMGETTXID_LOFUNC     (&bsw_pdur_rt_ComGetTxIdMultiP)
#define BSW_PDUR_COMGETRXID_LOFUNC     (&bsw_pdur_rt_ComGetRxIdMultiP)
#define BSW_PDUR_LDCOMTRANSMIT_LOFUNC  (&bsw_pdur_rt_LdComTransmitMultiP)
#define BSW_PDUR_LDCOMCANCELTX_LOFUNC  (&bsw_pdur_rt_LdComCancelTxMultiP)
#define BSW_PDUR_COMGETTXMODE_UPFUNC   (&bsw_pdur_rt_ComGetTxModeMultiP)
#endif

#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)
#define BSW_PDUR_COMTRANSMIT_FUNC      BSW_PDUR_COMTRANSMIT_LOFUNC
#define BSW_PDUR_COMCANCELTX_FUNC      BSW_PDUR_COMCANCELTX_LOFUNC
#define BSW_PDUR_COMGETTXID_FUNC       BSW_PDUR_COMGETTXID_LOFUNC
#define BSW_PDUR_COMGETRXID_FUNC       BSW_PDUR_COMGETRXID_LOFUNC
#else
#define BSW_PDUR_COMTRANSMIT_FUNC      (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_COMCANCELTX_FUNC      (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_COMGETTXID_FUNC       (&bsw_pdur_dummy_ComGetTxId)
#define BSW_PDUR_COMGETRXID_FUNC       (&bsw_pdur_dummy_ComGetRxId)
#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE)
#define BSW_PDUR_LDCOMTRANSMIT_FUNC    BSW_PDUR_LDCOMTRANSMIT_LOFUNC
#define BSW_PDUR_LDCOMCANCELTX_FUNC    BSW_PDUR_LDCOMCANCELTX_LOFUNC
#else
#define BSW_PDUR_LDCOMTRANSMIT_FUNC    (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_LDCOMCANCELTX_FUNC    (&bsw_pdur_dummy_CancelTransmit)
#endif /* (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) */

#if ( (BSW_BSWM_CS_FUNC_DCM == BSW_USE) )
#define BSW_PDUR_DCMTRANSMIT_FUNC      BSW_PDUR_DCMTRANSMIT_LOFUNC
#define BSW_PDUR_DCMCANCELTX_FUNC      BSW_PDUR_DCMCANCELTX_LOFUNC
#define BSW_PDUR_DCMCANCELRX_FUNC      BSW_PDUR_DCMCANCELRX_LOFUNC
#else
#define BSW_PDUR_DCMTRANSMIT_FUNC      (&bsw_pdur_dummy_Transmit)
#define BSW_PDUR_DCMCANCELTX_FUNC      (&bsw_pdur_dummy_CancelTransmit)
#define BSW_PDUR_DCMCANCELRX_FUNC      (&bsw_pdur_dummy_CancelReceive)
#endif /* ( (BSW_BSWM_CS_FUNC_DCM == BSW_USE) ) */

#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)

#define BSW_PDUR_TRIGGERTX_FUNC        BSW_PDUR_TRIGGERTX_UPFUNC
#define BSW_PDUR_TXCONF_FUNC           BSW_PDUR_TXCONF_UPFUNC
#define BSW_PDUR_RXIND_FUNC            BSW_PDUR_RXIND_UPFUNC
#define BSW_PDUR_SOR_FUNC              BSW_PDUR_SOR_UPFUNC
#define BSW_PDUR_COPYRXDATA_FUNC       BSW_PDUR_COPYRXDATA_UPFUNC
#define BSW_PDUR_COPYTXDATA_FUNC       BSW_PDUR_COPYTXDATA_UPFUNC
#define BSW_PDUR_TPRXIND_FUNC          BSW_PDUR_TPRXIND_UPFUNC
#define BSW_PDUR_TPTXCONF_FUNC         BSW_PDUR_TPTXCONF_UPFUNC
#define BSW_PDUR_COMGETTXMODE_FUNC     BSW_PDUR_COMGETTXMODE_UPFUNC

#else

#if ((BSW_BSWM_CS_FUNC_COM == BSW_USE) || (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE))
#define BSW_PDUR_TRIGGERTX_FUNC        BSW_PDUR_TRIGGERTX_UPFUNC
#define BSW_PDUR_TXCONF_FUNC           BSW_PDUR_TXCONF_UPFUNC
#define BSW_PDUR_RXIND_FUNC            BSW_PDUR_RXIND_UPFUNC
#define BSW_PDUR_COMGETTXMODE_FUNC     BSW_PDUR_COMGETTXMODE_UPFUNC
#else
#define BSW_PDUR_TRIGGERTX_FUNC        (&bsw_pdur_dummy_TriggerTransmit)
#define BSW_PDUR_TXCONF_FUNC           (&bsw_pdur_dummy_TxConfirmation)
#define BSW_PDUR_RXIND_FUNC            (&bsw_pdur_dummy_RxIndication)
#define BSW_PDUR_COMGETTXMODE_FUNC     (&bsw_pdur_dummy_ComGetTxMode)
#endif /* ((BSW_BSWM_CS_FUNC_COM == BSW_USE) || (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE)) */

#if ((BSW_BSWM_CS_FUNC_DCM == BSW_USE))
#define BSW_PDUR_SOR_FUNC              BSW_PDUR_SOR_UPFUNC
#define BSW_PDUR_COPYRXDATA_FUNC       BSW_PDUR_COPYRXDATA_UPFUNC
#define BSW_PDUR_COPYTXDATA_FUNC       BSW_PDUR_COPYTXDATA_UPFUNC
#define BSW_PDUR_TPRXIND_FUNC          BSW_PDUR_TPRXIND_UPFUNC
#define BSW_PDUR_TPTXCONF_FUNC         BSW_PDUR_TPTXCONF_UPFUNC
#else
#define BSW_PDUR_SOR_FUNC              (&bsw_pdur_dummy_StartOfRecept)
#define BSW_PDUR_COPYRXDATA_FUNC       (&bsw_pdur_dummy_CopyRxData)
#define BSW_PDUR_COPYTXDATA_FUNC       (&bsw_pdur_dummy_CopyTxData)
#define BSW_PDUR_TPRXIND_FUNC          (&bsw_pdur_dummy_TpRxIndication)
#define BSW_PDUR_TPTXCONF_FUNC         (&bsw_pdur_dummy_TpTxConfirmation)
#endif /* ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) */

#endif /* (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE) */

/* PDU ID to notify */
#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_CAN)
#define BSW_PDUR_COMPMASK_ZEROCOST     BSW_PDUR_ID_MASK
#define BSW_PDUR_IFCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_CANIF
#define BSW_PDUR_TPCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_CANTP

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_LIN)
#define BSW_PDUR_COMPMASK_ZEROCOST     BSW_PDUR_ID_MASK
#define BSW_PDUR_IFCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_LINIF
#define BSW_PDUR_TPCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_LINTP

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_ETH)
#define BSW_PDUR_COMPMASK_ZEROCOST     BSW_PDUR_ID_MASK
#define BSW_PDUR_IFCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_SOADIF
#define BSW_PDUR_TPCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_DOIPTP

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_CDD1)
#define BSW_PDUR_COMPMASK_ZEROCOST     BSW_PDUR_ID_MASK
#define BSW_PDUR_IFCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_CDD1IF
#define BSW_PDUR_TPCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_CDD1TP

#elif (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_CDD2)
#define BSW_PDUR_COMPMASK_ZEROCOST     BSW_PDUR_ID_MASK
#define BSW_PDUR_IFCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_CDD2IF
#define BSW_PDUR_TPCOMPSET_ZEROCOST    BSW_PDUR_LOCOMP_CDD2TP

#else   /* Zero cost operation unused */
#define BSW_PDUR_COMPMASK_ZEROCOST     (0xFFFFU)
#define BSW_PDUR_IFCOMPSET_ZEROCOST    (0x0000U)
#define BSW_PDUR_TPCOMPSET_ZEROCOST    (0x0000U)
#endif

#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)
#define BSW_PDUR_GETIPDUID_FUNC        (&bsw_pdur_inf_GetIpduIdMulti)
#else
#define BSW_PDUR_GETIPDUID_FUNC        (&bsw_pdur_inf_GetIpduIdSingle)
#endif /* (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE) */

#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)
#define BSW_PDUR_GETLPDUID_FUNC     (&bsw_pdur_inf_ComGetLpduIdMulti)
#else
#define BSW_PDUR_GETLPDUID_FUNC     (&bsw_pdur_inf_ComGetLpduIdSingle)
#endif /* (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE) */

#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)
#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)
#define BSW_PDUR_COMGETLPDUID_FUNC     (&bsw_pdur_inf_ComGetLpduIdMulti)
#else
#define BSW_PDUR_COMGETLPDUID_FUNC     (&bsw_pdur_inf_ComGetLpduIdSingle)
#endif /* (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE) */
#else
#define BSW_PDUR_COMGETLPDUID_FUNC     (&bsw_pdur_inf_dummy_GetLpduId)
#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

#if ((BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE))
#define BSW_PDUR_CDD1GETLPDUID_FUNC    (&bsw_pdur_inf_Cdd1GetLpduIdMulti)
#else
#define BSW_PDUR_CDD1GETLPDUID_FUNC    (&bsw_pdur_inf_dummy_GetLpduId)
#endif /* ((BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) && (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)) */

#if ((BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE))
#define BSW_PDUR_CDD2GETLPDUID_FUNC    (&bsw_pdur_inf_Cdd2GetLpduIdMulti)
#else
#define BSW_PDUR_CDD2GETLPDUID_FUNC    (&bsw_pdur_inf_dummy_GetLpduId)
#endif /* ((BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) && (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)) */

#define BSW_PDUR_DUMMYGETLPDUID_FUNC   (&bsw_pdur_inf_dummy_GetLpduId)

/******************************************/
/* Definitions for subcomponents of PduR       */
/******************************************/
/* Macro definition for bsw_pdur_rt_CompTbl */
#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)

#if (BSW_BSWM_CS_FUNC_CANIF == BSW_USE)
#define BSW_PDUR_CANIF_FUNC            (&bsw_pdur_rt_CanIfFuncTbl)
#else
#define BSW_PDUR_CANIF_FUNC            (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CANTP == BSW_USE)
#define BSW_PDUR_CANTP_FUNC            (&bsw_pdur_rt_CanTpFuncTbl)
#else
#define BSW_PDUR_CANTP_FUNC            (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_LINIF == BSW_USE)
#define BSW_PDUR_LINIF_FUNC            (&bsw_pdur_rt_LinIfFuncTbl)
#else
#define BSW_PDUR_LINIF_FUNC            (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_LINTP == BSW_USE)
#define BSW_PDUR_LINTP_FUNC            (&bsw_pdur_rt_LinTpFuncTbl)
#else
#define BSW_PDUR_LINTP_FUNC            (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SOAD == BSW_USE)
#define BSW_PDUR_SOADIF_FUNC           (&bsw_pdur_rt_SoAdIfFuncTbl)
#else
#define BSW_PDUR_SOADIF_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) */

#if ((BSW_BSWM_CS_FUNC_SOAD == BSW_USE) && (BSW_PDUR_CFG_MSGSOADTP_NUM > 0U))
#define BSW_PDUR_SOADTP_FUNC           (&bsw_pdur_rt_SoAdTpFuncTbl)
#else
#define BSW_PDUR_SOADTP_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_DOIP == BSW_USE)
#define BSW_PDUR_DOIPIF_FUNC           (&bsw_pdur_rt_DoIPIfFuncTbl)
#else
#define BSW_PDUR_DOIPIF_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_DOIP == BSW_USE)
#define BSW_PDUR_DOIPTP_FUNC           (&bsw_pdur_rt_DoIPTpFuncTbl)
#else
#define BSW_PDUR_DOIPTP_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD1IF == BSW_USE)
#define BSW_PDUR_CDD1IF_FUNC           (&bsw_pdur_rt_Cdd1IfFuncTbl)
#else
#define BSW_PDUR_CDD1IF_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_CDD1IF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD1TP == BSW_USE)
#define BSW_PDUR_CDD1TP_FUNC           (&bsw_pdur_rt_Cdd1TpFuncTbl)
#else
#define BSW_PDUR_CDD1TP_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_CDD1TP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD2IF == BSW_USE)
#define BSW_PDUR_CDD2IF_FUNC           (&bsw_pdur_rt_Cdd2IfFuncTbl)
#else
#define BSW_PDUR_CDD2IF_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_CDD2IF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD2TP == BSW_USE)
#define BSW_PDUR_CDD2TP_FUNC           (&bsw_pdur_rt_Cdd2TpFuncTbl)
#else
#define BSW_PDUR_CDD2TP_FUNC           (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_CDD2TP == BSW_USE) */

#endif /* (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE) */

/******************************************/
/* Definitions for higher-level components of PduR       */
/******************************************/
#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)
#define BSW_PDUR_COM_FUNC              (&bsw_pdur_ComFuncTbl)
#else
#define BSW_PDUR_COM_FUNC              (&bsw_pdur_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

#if ((BSW_BSWM_CS_FUNC_DCM == BSW_USE))
#define BSW_PDUR_DCM_FUNC              (&bsw_pdur_DcmFuncTbl)
#else
#define BSW_PDUR_DCM_FUNC              (&bsw_pdur_DummyFuncTbl)
#endif /* ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) */

#if (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE)
#define BSW_PDUR_LDCOM_FUNC            (&bsw_pdur_LdComFuncTbl)
#else
#define BSW_PDUR_LDCOM_FUNC            (&bsw_pdur_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE)
#define BSW_PDUR_CDD1_FUNC             (&bsw_pdur_Cdd1FuncTbl)
#else
#define BSW_PDUR_CDD1_FUNC             (&bsw_pdur_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE)
#define BSW_PDUR_CDD2_FUNC             (&bsw_pdur_Cdd2FuncTbl)
#else
#define BSW_PDUR_CDD2_FUNC             (&bsw_pdur_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) */


/******************************************/
/* Definition for SecOC                            */
/******************************************/
#if (BSW_BSWM_CS_FUNC_SECOC == BSW_USE)
#define BSW_PDUR_SECOC_FUNC            (&bsw_pdur_SecOCFuncTbl)
#else
#define BSW_PDUR_SECOC_FUNC            (&bsw_pdur_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SECOC == BSW_USE)
#define BSW_PDUR_SECOCIF_FUNC          (&bsw_pdur_rt_SecOCIfFuncTbl)
#define BSW_PDUR_SECOCTP_FUNC          (&bsw_pdur_rt_SecOCTpFuncTbl)
#else
#define BSW_PDUR_SECOCIF_FUNC          (&bsw_pdur_rt_DummyFuncTbl)
#define BSW_PDUR_SECOCTP_FUNC          (&bsw_pdur_rt_DummyFuncTbl)
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) */

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
#if (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE)
/* When zero cost operation is not used */

/* MISRA DEVIATION: may be unused data */
static BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_DummyFuncTbl =
{
    &bsw_pdur_dummy_Transmit,
    &bsw_pdur_dummy_CancelTransmit,
    &bsw_pdur_dummy_CancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};

/* Message count */
BswConst BswU2 bsw_pdur_u2ComMsgNum    = (BswU2)BSW_PDUR_CFG_MSGCOM_NUM;
BswConst BswU2 bsw_pdur_u2DcmMsgNum    = (BswU2)BSW_PDUR_CFG_MSGDCM_NUM;
BswConst BswU2 bsw_pdur_u2LdComMsgNum  = (BswU2)BSW_PDUR_CFG_MSGLDCOM_NUM;
BswConst BswU2 bsw_pdur_u2Cdd1MsgNum   = (BswU2)BSW_PDUR_CFG_MSGCDD1_NUM;
BswConst BswU2 bsw_pdur_u2Cdd2MsgNum   = (BswU2)BSW_PDUR_CFG_MSGCDD2_NUM;

BswConst BswU2 bsw_pdur_u2UpCompMsgNumTbl[BSW_PDUR_MAX_UPCMPNUM] =
{
    (BswU2)BSW_PDUR_CFG_MSGCOM_NUM,
    (BswU2)BSW_PDUR_CFG_MSGDCM_NUM,
    (BswU2)BSW_PDUR_CFG_MSGLDCOM_NUM,
    (BswU2)BSW_PDUR_CFG_MSGCDD1_NUM,
    (BswU2)BSW_PDUR_CFG_MSGCDD2_NUM
};

BswConst BswU2 bsw_pdur_u2LoCompMsgNumTbl[BSW_PDUR_MAX_LOCMPNUM] =
{
    (BswU2)BSW_PDUR_CFG_MSGCANIF_NUM,
    (BswU2)BSW_PDUR_CFG_MSGCANTP_NUM,
    (BswU2)BSW_PDUR_CFG_MSGLINIF_NUM,
    (BswU2)BSW_PDUR_CFG_MSGLINTP_NUM,
    (BswU2)BSW_PDUR_CFG_MSGSOADIF_NUM,
    (BswU2)BSW_PDUR_CFG_MSGSOADTP_NUM,
    (BswU2)BSW_PDUR_CFG_MSGDOIPIF_NUM,
    (BswU2)BSW_PDUR_CFG_MSGDOIPTP_NUM,
    (BswU2)BSW_PDUR_CFG_MSGCDD1IF_NUM,
    (BswU2)BSW_PDUR_CFG_MSGCDD1TP_NUM,
    (BswU2)BSW_PDUR_CFG_MSGCDD2IF_NUM,
    (BswU2)BSW_PDUR_CFG_MSGCDD2TP_NUM
};

/* Table for getting routing destination information */
BswConst   PduIdType* BswConst bsw_pdur_u2UpCompRoutingTbl[BSW_PDUR_MAX_UPCMPNUM] =
{
    BSW_PDUR_COM_ROUTINGTBL,
    BSW_PDUR_DCM_ROUTINGTBL,
    BSW_PDUR_LDCOM_ROUTINGTBL,
    BSW_PDUR_CDD1_ROUTINGTBL,
    BSW_PDUR_CDD2_ROUTINGTBL
};

BswConst   Bsw_PduR_RoutingType* BswConst bsw_pdur_stLoCompRoutingTbl[BSW_PDUR_MAX_LOCMPNUM] =
{
    BSW_PDUR_CANIF_ROUTINGTBL,
    BSW_PDUR_CANTP_ROUTINGTBL,
    BSW_PDUR_LINIF_ROUTINGTBL,
    BSW_PDUR_LINTP_ROUTINGTBL,
    BSW_PDUR_SOADIF_ROUTINGTBL,
    BSW_PDUR_SOADTP_ROUTINGTBL,
    BSW_PDUR_DOIPIF_ROUTINGTBL,
    BSW_PDUR_DOIPTP_ROUTINGTBL,
    BSW_PDUR_CDD1IF_ROUTINGTBL,
    BSW_PDUR_CDD1TP_ROUTINGTBL,
    BSW_PDUR_CDD2IF_ROUTINGTBL,
    BSW_PDUR_CDD2TP_ROUTINGTBL
};

/* Table for getting routing destination information */
BswConst   PduIdType* BswConst bsw_pdur_ptIpduMUpRoutingTbl[BSW_PDUR_MAX_UPCMPNUM] =
{
    BSW_PDUR_COM_IPDUMLOTBL,
    BSW_PDUR_DCM_IPDUMLOTBL,
    BSW_PDUR_LDCOM_IPDUMLOTBL,
    BSW_PDUR_CDD1_IPDUMLOTBL,
    BSW_PDUR_CDD2_IPDUMLOTBL
};

BswConst   PduIdType* BswConst bsw_pdur_ptIpduMLoRoutingTbl[BSW_PDUR_MAX_LOCMPNUM] =
{
    BSW_PDUR_CANIF_IPDUMLOTBL,
    &bsw_pdur_u2DummyIpduMTbl[0U],
    BSW_PDUR_LINIF_IPDUMLOTBL,
    &bsw_pdur_u2DummyIpduMTbl[0U],
    BSW_PDUR_SOADIF_IPDUMLOTBL,
    &bsw_pdur_u2DummyIpduMTbl[0U],
    BSW_PDUR_DOIPIF_IPDUMLOTBL,
    &bsw_pdur_u2DummyIpduMTbl[0U],
    BSW_PDUR_CDD1IF_IPDUMLOTBL,
    &bsw_pdur_u2DummyIpduMTbl[0U],
    BSW_PDUR_CDD2IF_IPDUMLOTBL,
    &bsw_pdur_u2DummyIpduMTbl[0U]
};

/* Table for getting routing destination information (SomeIpTp) */
BswConst   PduIdType* BswConst bsw_pdur_ptSomeIpTpLoRoutingTbl[BSW_PDUR_MAX_LOCMPNUM] =
{
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    BSW_PDUR_SOADIF_SOMEIPTPLOTBL,
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
    &bsw_pdur_u2DummySomeIpTpTbl[0U],
};

/* Table for getting routing destination information (SecOC) */
BswConst   PduIdType* BswConst bsw_pdur_u2SecOCUpRoutingTbl[BSW_PDUR_MAX_UPCMPNUM] =
{
    BSW_PDUR_COM_SECOCUPTBL,
    BSW_PDUR_DCM_SECOCUPTBL,
    BSW_PDUR_LDCOM_SECOCUPTBL,
    BSW_PDUR_CDD1_SECOCUPTBL,
    BSW_PDUR_CDD2_SECOCUPTBL
};

/******************************************/
/* Definitions for subcomponents of PduR       */
/******************************************/
#if (BSW_BSWM_CS_FUNC_CANIF == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_CanIfFuncTbl =
{
    BSW_PDUR_CANIF_TRANSMIT_FUNC,
    BSW_PDUR_CANIF_CANCELTX_FUNC,
    &bsw_pdur_dummy_CancelReceive,
    BSW_PDUR_CANIF_GETTXID_FUNC,
    BSW_PDUR_CANIF_GETRXID_FUNC,
    BSW_PDUR_CANIF_GETCURRXID_FUNC
};
#if (BSW_PDUR_CFG_MSGCANIF_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stCanIfRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
BswConst PduIdType bsw_pdur_u2CanIfIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (PduIdType)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */
#endif /* (BSW_PDUR_CFG_MSGCANIF_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_CANIF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CANTP == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_CanTpFuncTbl =
{
    &bsw_bswm_can_CanTpTransmit,
    &bsw_bswm_can_CanTpCancelTransmit,
    &bsw_bswm_can_CanTpCancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGCANTP_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stCanTpRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#endif /* (BSW_PDUR_CFG_MSGCANTP_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_CANTP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_LINIF == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_LinIfFuncTbl =
{
    BSW_PDUR_LINIF_TRANSMIT_FUNC,
    BSW_PDUR_LINIF_CANCELTX_FUNC,
    &bsw_pdur_dummy_CancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGLINIF_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stLinIfRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
BswConst PduIdType bsw_pdur_u2LinIfIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (PduIdType)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */
#endif /* (BSW_PDUR_CFG_MSGLINIF_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_LINIF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_LINTP == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_LinTpFuncTbl =
{
    &LinTp_Transmit,
    &LinTp_CancelTransmit,
    &LinTp_CancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGLINTP_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stLinTpRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#endif /* (BSW_PDUR_CFG_MSGLINTP_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_LINTP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SOAD == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SoAdIfFuncTbl =
{
    BSW_PDUR_SOADIF_TRANSMIT_FUNC,
    BSW_PDUR_SOADIF_CANCELTX_FUNC,
    &bsw_pdur_dummy_CancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGSOADIF_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stSoAdIfRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
BswConst PduIdType bsw_pdur_u2SoAdIfIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (PduIdType)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */
#if ( BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE )
BswConst PduIdType bsw_pdur_u2SoAdIfSomeIpTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};
#endif /* (BSW_BSWM_CS_FUNC_SOMEIP == BSW_USE) */
#endif /* (BSW_PDUR_CFG_MSGSOADIF_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SOAD == BSW_USE)
#if (BSW_PDUR_CFG_MSGSOADTP_NUM > 0U)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SoAdTpFuncTbl =
{
    &SoAd_TpTransmit,
    &SoAd_TpCancelTransmit,
    &SoAd_TpCancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#else
BswConst Bsw_PduR_RoutingType bsw_pdur_stSoAdTpRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#endif /* (BSW_PDUR_CFG_MSGSOADTP_NUM > 0U) */
#endif /* (BSW_BSWM_CS_FUNC_SOAD == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_DOIP == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_DoIPIfFuncTbl =
{
    &DoIP_IfTransmit,
    &DoIP_IfCancelTransmit,
    &bsw_pdur_dummy_CancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGDOIPIF_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stDoIPIfRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
BswConst PduIdType bsw_pdur_u2DoIPIfIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (PduIdType)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */
#endif /* (BSW_PDUR_CFG_MSGDOIPIF_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_DOIP == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_DoIPTpFuncTbl =
{
    &DoIP_TpTransmit,
    &DoIP_TpCancelTransmit,
    &DoIP_TpCancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGDOIPTP_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stDoIPTpRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#endif /* (BSW_PDUR_CFG_MSGDOIPTP_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_DOIP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD1IF == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd1IfFuncTbl =
{
    BSW_PDUR_CDD1IF_TRANSMIT_FUNC,
    BSW_PDUR_CDD1IF_CANCELTX_FUNC,
    &bsw_pdur_dummy_CancelReceive,
    BSW_PDUR_CDD1IF_GETTXID_FUNC,
    BSW_PDUR_CDD1IF_GETRXID_FUNC,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGCDD1IF_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stCdd1IfRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
BswConst PduIdType bsw_pdur_u2Cdd1IfIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (PduIdType)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */
#endif /* (BSW_PDUR_CFG_MSGCDD1IF_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_CDD1IF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD1TP == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd1TpFuncTbl =
{
    &bsw_bswm_cs_Cdd1TpTransmit,
    &bsw_bswm_cs_Cdd1TpCancelTransmit,
    &bsw_bswm_cs_Cdd1TpCancelReceive,
    &bsw_bswm_cs_Cdd1TpGetTxId,
    &bsw_bswm_cs_Cdd1TpGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGCDD1TP_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stCdd1TpRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#endif /* (BSW_PDUR_CFG_MSGCDD1TP_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_CDD1TP == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD2IF == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd2IfFuncTbl =
{
    BSW_PDUR_CDD2IF_TRANSMIT_FUNC,
    BSW_PDUR_CDD2IF_CANCELTX_FUNC,
    &bsw_pdur_dummy_CancelReceive,
    BSW_PDUR_CDD2IF_GETTXID_FUNC,
    BSW_PDUR_CDD2IF_GETRXID_FUNC,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGCDD2IF_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stCdd2IfRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
BswConst PduIdType bsw_pdur_u2Cdd2IfIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (PduIdType)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_USE) */
#endif /* (BSW_PDUR_CFG_MSGCDD2IF_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_CDD2IF == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_CDD2TP == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_Cdd2TpFuncTbl =
{
    &bsw_bswm_cs_Cdd2TpTransmit,
    &bsw_bswm_cs_Cdd2TpCancelTransmit,
    &bsw_bswm_cs_Cdd2TpCancelReceive,
    &bsw_bswm_cs_Cdd2TpGetTxId,
    &bsw_bswm_cs_Cdd2TpGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#if (BSW_PDUR_CFG_MSGCDD2TP_NUM == 0U)
BswConst Bsw_PduR_RoutingType bsw_pdur_stCdd2TpRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    { (BswU2)0x0000U, (BswU2)0x0000U }
};
#endif /* (BSW_PDUR_CFG_MSGCDD2TP_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_CDD2TP == BSW_USE) */

BswConst   Bsw_PduR_LoCompInfoType* BswConst bsw_pdur_rt_CompTbl[ BSW_PDUR_MAX_LOCMPNUM ] =
{
    BSW_PDUR_CANIF_FUNC,
    BSW_PDUR_CANTP_FUNC,
    BSW_PDUR_LINIF_FUNC,
    BSW_PDUR_LINTP_FUNC,
    BSW_PDUR_SOADIF_FUNC,
    BSW_PDUR_SOADTP_FUNC,
    BSW_PDUR_DOIPIF_FUNC,
    BSW_PDUR_DOIPTP_FUNC,
    BSW_PDUR_CDD1IF_FUNC,
    BSW_PDUR_CDD1TP_FUNC,
    BSW_PDUR_CDD2IF_FUNC,
    BSW_PDUR_CDD2TP_FUNC
};

/******************************************/
/* Definitions for higher-level components of PduR       */
/******************************************/
#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)
BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_ComFuncTbl =
{
    &Com_TriggerTransmit,
    &Com_TxConfirmation,
    &Com_RxIndication,
    &Com_StartOfReception,
    &Com_CopyRxData,
    &Com_CopyTxData,
    &Com_TpRxIndication,
    &Com_TpTxConfirmation,
    &Com_GetCurrentTxMode
};
#if (BSW_PDUR_CFG_MSGCOM_NUM == 0U)
BswConst PduIdType bsw_pdur_u2ComRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (BswU2)0x0000U
};
#endif /* (BSW_PDUR_CFG_MSGCOM_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCOM_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2ComIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCOM_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCOM_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2ComSecOCTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCOM_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

#if ((BSW_BSWM_CS_FUNC_DCM == BSW_USE))
BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_DcmFuncTbl =
{
    &bsw_pdur_dummy_TriggerTransmit,
    &bsw_bswm_cs_DcmTxConfirmation,
    &bsw_pdur_dummy_RxIndication,
    &bsw_bswm_cs_DcmStartOfReception,
    &bsw_bswm_cs_DcmCopyRxData,
    &bsw_bswm_cs_DcmCopyTxData,
    &bsw_bswm_cs_DcmTpRxIndication,
    &bsw_bswm_cs_DcmTpTxConfirmation,
    &bsw_pdur_dummy_ComGetTxMode
};
#if (BSW_PDUR_CFG_MSGDCM_NUM == 0U)
BswConst PduIdType bsw_pdur_u2DcmRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (BswU2)0x0000U
};
#endif /* (BSW_PDUR_CFG_MSGDCM_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGDCM_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2DcmIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGDCM_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGDCM_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2DcmSecOCTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGDCM_NUM == 0U) */
#endif /* ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) */

#if (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE)
BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_LdComFuncTbl =
{
    &LdCom_TriggerTransmit,
    &LdCom_TxConfirmation,
    &LdCom_RxIndication,
    &LdCom_StartOfReception,
    &LdCom_CopyRxData,
    &LdCom_CopyTxData,
    &LdCom_TpRxIndication,
    &LdCom_TpTxConfirmation,
    &bsw_pdur_dummy_ComGetTxMode
};
#if (BSW_PDUR_CFG_MSGLDCOM_NUM == 0U)
BswConst PduIdType bsw_pdur_u2LdComRoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (BswU2)0x0000U
};
#endif /* (BSW_PDUR_CFG_MSGLDCOM_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGLDCOM_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2LdComIpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_LDCOM_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGLDCOM_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2LdComSecOCTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGLDCOM_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE)
BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_Cdd1FuncTbl =
{
    &bsw_bswm_cs_Cdd1UpTriggerTx,
    &bsw_bswm_cs_Cdd1UpTxConfirmation,
    &bsw_bswm_cs_Cdd1UpRxIndication,
    &bsw_bswm_cs_Cdd1UpStartOfReception,
    &bsw_bswm_cs_Cdd1UpCopyRxData,
    &bsw_bswm_cs_Cdd1UpCopyTxData,
    &bsw_bswm_cs_Cdd1UpTpRxIndication,
    &bsw_bswm_cs_Cdd1UpTpTxConfirmation,
    &bsw_pdur_dummy_ComGetTxMode
};
#if (BSW_PDUR_CFG_MSGCDD1_NUM == 0U)
BswConst PduIdType bsw_pdur_u2Cdd1RoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (BswU2)0x0000U
};
#endif /* (BSW_PDUR_CFG_MSGCDD1_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD1_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1IpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD1_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD1_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2Cdd1SecOCTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD1_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_UPPERCDD1 == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE)
BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_Cdd2FuncTbl =
{
    &bsw_bswm_cs_Cdd2UpTriggerTx,
    &bsw_bswm_cs_Cdd2UpTxConfirmation,
    &bsw_bswm_cs_Cdd2UpRxIndication,
    &bsw_bswm_cs_Cdd2UpStartOfReception,
    &bsw_bswm_cs_Cdd2UpCopyRxData,
    &bsw_bswm_cs_Cdd2UpCopyTxData,
    &bsw_bswm_cs_Cdd2UpTpRxIndication,
    &bsw_bswm_cs_Cdd2UpTpTxConfirmation,
    &bsw_pdur_dummy_ComGetTxMode
};
#if (BSW_PDUR_CFG_MSGCDD2_NUM == 0U)
BswConst PduIdType bsw_pdur_u2Cdd2RoutingTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
    (BswU2)0x0000U
};
#endif /* (BSW_PDUR_CFG_MSGCDD2_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD2_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2IpduMTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)0x0000U
};
#endif /* (BSW_BSWM_CS_FUNC_IPDUM == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD2_NUM == 0U) */
#if ( (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD2_NUM == 0U) )
BswConst PduIdType bsw_pdur_u2Cdd2SecOCTbl[BSW_PDUR_TBL_DUMMY_SIZE] = 
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_NOUSE) || (BSW_PDUR_CFG_IPDU_MA == BSW_NOUSE) || (BSW_PDUR_CFG_MSGCDD2_NUM == 0U) */
#endif /* (BSW_BSWM_CS_FUNC_UPPERCDD2 == BSW_USE) */

BswConst   Bsw_PduR_UpCompInfoType* BswConst bsw_pdur_UpperCompFuncTbl[ BSW_PDUR_MAX_UPCMPNUM ] =
{
    BSW_PDUR_COM_FUNC,
    BSW_PDUR_DCM_FUNC,
    BSW_PDUR_LDCOM_FUNC,
    BSW_PDUR_CDD1_FUNC,
    BSW_PDUR_CDD2_FUNC
};

/******************************************/
/* Definition for SecOC                            */
/******************************************/
#if (BSW_BSWM_CS_FUNC_SECOC == BSW_USE)
BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SecOCIfFuncTbl =
{
    &SecOC_IfTransmit,
    &SecOC_IfCancelTransmit,
    &bsw_pdur_dummy_CancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};

BswConst   Bsw_PduR_LoCompInfoType bsw_pdur_rt_SecOCTpFuncTbl =
{
    &SecOC_TpTransmit,
    &SecOC_TpCancelTransmit,
    &SecOC_TpCancelReceive,
    &bsw_pdur_dummy_ComGetTxId,
    &bsw_pdur_dummy_ComGetRxId,
    &bsw_pdur_dummy_ComGetCrrntRxId
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) */

#if (BSW_BSWM_CS_FUNC_SECOC == BSW_USE)
BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_SecOCFuncTbl =
{
    &SecOC_TriggerTransmit,
    &SecOC_TxConfirmation,
    &SecOC_RxIndication,
    &SecOC_StartOfReception,
    &SecOC_CopyRxData,
    &SecOC_CopyTxData,
    &SecOC_TpRxIndication,
    &SecOC_TpTxConfirmation,
    &bsw_pdur_dummy_ComGetTxMode
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) */

/* Component ID conversion table */
#if (BSW_BSWM_CS_FUNC_SECOC == BSW_USE)
BswConst PduIdType bsw_pdur_u2SecOCToUpCompIdTbl[BSW_PDUR_MAX_UPCMPNUM] =
{
    (BswU2)BSW_PDUR_UPCOMP_COM
   ,(BswU2)BSW_PDUR_UPCOMP_DCM
   ,(BswU2)BSW_PDUR_UPCOMP_LDCOM
   ,(BswU2)BSW_PDUR_UPCOMP_CDD1
   ,(BswU2)BSW_PDUR_UPCOMP_CDD2
};
BswConst PduIdType bsw_pdur_u2SecOCToLoCompIdTbl[BSW_PDUR_MAX_LOCMPNUM] =
{
    (BswU2)BSW_PDUR_LOCOMP_CANIF
   ,(BswU2)BSW_PDUR_LOCOMP_CANTP
   ,(BswU2)BSW_PDUR_LOCOMP_LINIF
   ,(BswU2)BSW_PDUR_LOCOMP_LINTP
   ,(BswU2)BSW_PDUR_LOCOMP_SOADIF
   ,(BswU2)BSW_PDUR_LOCOMP_SOADTP
   ,(BswU2)BSW_PDUR_LOCOMP_DOIPIF
   ,(BswU2)BSW_PDUR_LOCOMP_DOIPTP
   ,(BswU2)BSW_PDUR_LOCOMP_CDD1IF
   ,(BswU2)BSW_PDUR_LOCOMP_CDD1TP
   ,(BswU2)BSW_PDUR_LOCOMP_CDD2IF
   ,(BswU2)BSW_PDUR_LOCOMP_CDD2TP
};
#else
BswConst PduIdType bsw_pdur_u2SecOCToUpCompIdTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
   (BswU2)BSW_PDUR_INVALID_PDUID
};
BswConst PduIdType bsw_pdur_u2SecOCToLoCompIdTbl[BSW_PDUR_TBL_DUMMY_SIZE] =
{
   (BswU2)BSW_PDUR_INVALID_PDUID
};
#endif /* (BSW_BSWM_CS_FUNC_SECOC == BSW_USE) */


/******************************************/
/* Definition for IpduM                            */
/******************************************/
BswConst   Bsw_PduR_IpduMInfoType bsw_pdur_rt_IpduMFuncTbl =
{
    BSW_PDUR_IPDUM_TRANSMIT_FUNC,
    BSW_PDUR_IPDUM_CANCELTX_FUNC,
    BSW_PDUR_IPDUM_TRIGGERTX_FUNC,
    BSW_PDUR_IPDUM_TXCONF_FUNC,
    BSW_PDUR_IPDUM_RXIND_FUNC
};

/******************************************/
/* Definition for SomeIpTp                         */
/******************************************/
BswConst   Bsw_PduR_SomeIpTpInfoType bsw_pdur_rt_SomeIpTpFuncTbl =
{
    BSW_PDUR_SOMEIPTP_TRANSMIT_FUNC,
    BSW_PDUR_SOMEIPTP_CANCELTX_FUNC,
    BSW_PDUR_SOMEIPTP_TRIGRTX_FUNC,
    BSW_PDUR_SOMEIPTP_TXCONF_FUNC,
    BSW_PDUR_SOMEIPTP_RXIND_FUNC
};

BswConst Bsw_PduR_LoCompInfoType* BswConst bsw_pdur_rom_ptSecOCIfLoFunc = BSW_PDUR_SECOCIF_FUNC;
BswConst Bsw_PduR_LoCompInfoType* BswConst bsw_pdur_rom_ptSecOCTpLoFunc = BSW_PDUR_SECOCTP_FUNC;
BswConst Bsw_PduR_UpCompInfoType* BswConst bsw_pdur_rom_ptSecOCUpFunc = BSW_PDUR_SECOC_FUNC;

BswConst   Bsw_PduR_UpCompInfoType bsw_pdur_DummyFuncTbl =
{
    &bsw_pdur_dummy_TriggerTransmit,
    &bsw_pdur_dummy_TxConfirmation,
    &bsw_pdur_dummy_RxIndication,
    &bsw_pdur_dummy_StartOfRecept,
    &bsw_pdur_dummy_CopyRxData,
    &bsw_pdur_dummy_CopyTxData,
    &bsw_pdur_dummy_TpRxIndication,
    &bsw_pdur_dummy_TpTxConfirmation,
    &bsw_pdur_dummy_ComGetTxMode
};

BswConst   PduIdType bsw_pdur_u2DummyUpRoutingTbl[ BSW_PDUR_TBL_DUMMY_SIZE ] =
{
    ((BswU2)BSW_PDUR_LOCOMP_CANIF | (BswU2)0x0000U)
};

BswConst   Bsw_PduR_RoutingType bsw_pdur_stDummyRoutingTbl[ BSW_PDUR_TBL_DUMMY_SIZE ] =
{
    { ((BswU2)BSW_PDUR_UPCOMP_COM | (BswU2)0x0000U), (BswU2)0xFFFFU }
};


BswConst   PduIdType bsw_pdur_u2DummyIpduMTbl[ BSW_PDUR_TBL_DUMMY_SIZE ] =
{
    (PduIdType)0x0000U
};

BswConst   PduIdType bsw_pdur_u2DummySomeIpTpTbl[ BSW_PDUR_TBL_DUMMY_SIZE ] =
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};

BswConst   PduIdType bsw_pdur_u2DummySecOCTbl[ BSW_PDUR_TBL_DUMMY_SIZE ] =
{
    (BswU2)BSW_PDUR_INVALID_PDUID
};

BswConst   BswU1 bsw_pdur_u1IpduMFunc = (BswU1)BSW_BSWM_CS_FUNC_IPDUM;
BswConst   BswU1 bsw_pdur_u1SomeIpTpFunc = (BswU1)BSW_BSWM_CS_FUNC_SOMEIP;
BswConst   BswU1 bsw_pdur_u1IPduMA    = (BswU1)BSW_PDUR_IPDU_MA;
#endif /* (BSW_PDUR_ZEROCOSTOPERATION == BSW_PDUR_ZEROCOST_NOUSE) */

/* L-PDUID conversion function table (Com,Dcm,LdCom,CDD1,CDD2)*/
BswConst Bsw_PduR_GetLpduIdType bsw_pdur_rom_ptGetLIdFuncTbl[ BSW_PDUR_MAX_UPCMPNUM ] =
{
    BSW_PDUR_COMGETLPDUID_FUNC,
    BSW_PDUR_DUMMYGETLPDUID_FUNC,
    BSW_PDUR_DUMMYGETLPDUID_FUNC,
    BSW_PDUR_CDD1GETLPDUID_FUNC,
    BSW_PDUR_CDD2GETLPDUID_FUNC
};

/* Function Pointer for Zero Cost Operation Switching */
#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)
Std_ReturnType (* BswConst bsw_pdur_rom_ptComTransmitFunc)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr ) = BSW_PDUR_COMTRANSMIT_FUNC;
Std_ReturnType (* BswConst bsw_pdur_rom_ptComCancelTxFunc)( PduIdType TxPduId ) = BSW_PDUR_COMCANCELTX_FUNC;
#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

#if ((BSW_BSWM_CS_FUNC_DCM == BSW_USE))
Std_ReturnType (* BswConst bsw_pdur_rom_ptDcmTransmitFunc)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr ) = BSW_PDUR_DCMTRANSMIT_FUNC;
Std_ReturnType (* BswConst bsw_pdur_rom_ptDcmCancelTxFunc)( PduIdType TxPduId ) = BSW_PDUR_DCMCANCELTX_FUNC;
Std_ReturnType (* BswConst bsw_pdur_rom_ptDcmCancelRxFunc)( PduIdType RxPduId ) = BSW_PDUR_DCMCANCELRX_FUNC;
#endif /* ((BSW_BSWM_CS_FUNC_DCM == BSW_USE)) */

#if (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE)
Std_ReturnType (* BswConst bsw_pdur_rom_ptLdComTransmitFn)( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr ) = BSW_PDUR_LDCOMTRANSMIT_FUNC;
Std_ReturnType (* BswConst bsw_pdur_rom_ptLdComCancelTxFn)( PduIdType TxPduId ) = BSW_PDUR_LDCOMCANCELTX_FUNC;
#endif /* (BSW_BSWM_CS_FUNC_LDCOM == BSW_USE) */

Std_ReturnType (* BswConst bsw_pdur_rom_ptTriggerTxFunc)( PduIdType TxPduId, PduInfoType* PduInfoPtr ) = BSW_PDUR_TRIGGERTX_FUNC;
void (* BswConst bsw_pdur_rom_ptTxConfFunc)( PduIdType TxPduId, Std_ReturnType result ) = BSW_PDUR_TXCONF_FUNC;
void (* BswConst bsw_pdur_rom_ptRxIndFunc)( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr ) = BSW_PDUR_RXIND_FUNC;
BufReq_ReturnType (* BswConst bsw_pdur_rom_ptSorFunc)( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr ) = BSW_PDUR_SOR_FUNC;
BufReq_ReturnType (* BswConst bsw_pdur_rom_ptCopyRxDataFunc)( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr ) = BSW_PDUR_COPYRXDATA_FUNC;
BufReq_ReturnType (* BswConst bsw_pdur_rom_ptCopyTxDataFunc)( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr ) = BSW_PDUR_COPYTXDATA_FUNC;
void (* BswConst bsw_pdur_rom_ptTpRxIndFunc)( PduIdType id, Std_ReturnType result ) = BSW_PDUR_TPRXIND_FUNC;
void (* BswConst bsw_pdur_rom_ptTpTxConfFunc)( PduIdType id, Std_ReturnType result ) = BSW_PDUR_TPTXCONF_FUNC;
Com_TxModeType (* BswConst bsw_pdur_rom_ptComGetTxMode)( PduIdType TxPduId )  = BSW_PDUR_COMGETTXMODE_FUNC;

#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)
BswConst Bsw_PduR_ComGetTxIdType bsw_pdur_rom_ptComGetTxIdFunc = BSW_PDUR_COMGETTXID_FUNC;
BswConst Bsw_PduR_ComGetRxIdType bsw_pdur_rom_ptComGetRxIdFunc = BSW_PDUR_COMGETRXID_FUNC;
#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

BswConst Bsw_PduR_GetIpduIdType bsw_pdur_rom_ptGetIpduIdFunc = BSW_PDUR_GETIPDUID_FUNC;

#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)
BswConst Bsw_PduR_GetLpduIdType bsw_pdur_rom_ptGetLpduIdFunc = BSW_PDUR_GETLPDUID_FUNC;
#endif

BswConst   PduIdType bsw_pdur_PduIdCompMask = BSW_PDUR_COMPMASK_ZEROCOST;
BswConst   PduIdType bsw_pdur_PduIdIfCompSet  = BSW_PDUR_IFCOMPSET_ZEROCOST;
BswConst   PduIdType bsw_pdur_PduIdTpCompSet  = BSW_PDUR_TPCOMPSET_ZEROCOST;

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#include <cs/bsw_cs_system_memmap_post.h>

#endif /* (BSW_BSWM_CS_FUNC_PDUR == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-0-1          :2018/04/04                                             */
/*  v1-1-0          :2019/01/15                                             */
/*  v1-2-0          :2019/12/12                                             */
/*  v2-0-0          :2022/02/11                                             */
/*  v2-1-0          :2023/02/03                                             */
/*  v2-2-0          :2023/05/23                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
