/* Rte_Dcm_Type_h(v5-6-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RTE/DCM_Type/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef RTE_Dcm_TYPE_H
#define RTE_Dcm_TYPE_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <Rte_Dcm_Typedef.h>

#ifndef RTE_MODETYPE_DcmCCrl_00
#define RTE_MODETYPE_DcmCCrl_00
typedef uint8 Rte_ModeType_DcmCCrl_00;
#endif
#ifndef RTE_TRANSITION_DcmCCrl_00
#define RTE_TRANSITION_DcmCCrl_00 ((Rte_ModeType_DcmCCrl_00)12U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_ERET_NORM
#define RTE_MODE_DcmCCrl_00_ERET_NORM ((Rte_ModeType_DcmCCrl_00)0U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_ERDT_NORM
#define RTE_MODE_DcmCCrl_00_ERDT_NORM ((Rte_ModeType_DcmCCrl_00)1U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_DRET_NORM
#define RTE_MODE_DcmCCrl_00_DRET_NORM ((Rte_ModeType_DcmCCrl_00)2U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_DRDT_NORM
#define RTE_MODE_DcmCCrl_00_DRDT_NORM ((Rte_ModeType_DcmCCrl_00)3U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_ERET_NM
#define RTE_MODE_DcmCCrl_00_ERET_NM ((Rte_ModeType_DcmCCrl_00)4U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_ERDT_NM
#define RTE_MODE_DcmCCrl_00_ERDT_NM ((Rte_ModeType_DcmCCrl_00)5U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_DRET_NM
#define RTE_MODE_DcmCCrl_00_DRET_NM ((Rte_ModeType_DcmCCrl_00)6U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_DRDT_NM
#define RTE_MODE_DcmCCrl_00_DRDT_NM ((Rte_ModeType_DcmCCrl_00)7U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_ERET_NORM_NM
#define RTE_MODE_DcmCCrl_00_ERET_NORM_NM ((Rte_ModeType_DcmCCrl_00)8U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_ERDT_NORM_NM
#define RTE_MODE_DcmCCrl_00_ERDT_NORM_NM ((Rte_ModeType_DcmCCrl_00)9U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_DRET_NORM_NM
#define RTE_MODE_DcmCCrl_00_DRET_NORM_NM ((Rte_ModeType_DcmCCrl_00)10U)
#endif

#ifndef RTE_MODE_DcmCCrl_00_DRDT_NORM_NM
#define RTE_MODE_DcmCCrl_00_DRDT_NORM_NM ((Rte_ModeType_DcmCCrl_00)11U)
#endif

#ifndef RTE_MODETYPE_DcmControlDTCSetting
#define RTE_MODETYPE_DcmControlDTCSetting
typedef uint8 Rte_ModeType_DcmControlDTCSetting;
#endif
#ifndef RTE_TRANSITION_DcmControlDTCSetting
#define RTE_TRANSITION_DcmControlDTCSetting ((Rte_ModeType_DcmControlDTCSetting)2U)
#endif

#ifndef RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING
#define RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING ((Rte_ModeType_DcmControlDTCSetting)0U)
#endif

#ifndef RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING
#define RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING ((Rte_ModeType_DcmControlDTCSetting)1U)
#endif

#ifndef RTE_MODETYPE_DcmEcuReset
#define RTE_MODETYPE_DcmEcuReset
typedef uint8 Rte_ModeType_DcmEcuReset;
#endif
#ifndef RTE_TRANSITION_DcmEcuReset
#define RTE_TRANSITION_DcmEcuReset ((Rte_ModeType_DcmEcuReset)7U)
#endif

#ifndef RTE_MODE_DcmEcuReset_NONE
#define RTE_MODE_DcmEcuReset_NONE ((Rte_ModeType_DcmEcuReset)0U)
#endif

#ifndef RTE_MODE_DcmEcuReset_HARD
#define RTE_MODE_DcmEcuReset_HARD ((Rte_ModeType_DcmEcuReset)1U)
#endif

#ifndef RTE_MODE_DcmEcuReset_KEYONOFF
#define RTE_MODE_DcmEcuReset_KEYONOFF ((Rte_ModeType_DcmEcuReset)2U)
#endif

#ifndef RTE_MODE_DcmEcuReset_SOFT
#define RTE_MODE_DcmEcuReset_SOFT ((Rte_ModeType_DcmEcuReset)3U)
#endif

#ifndef RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER
#define RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER ((Rte_ModeType_DcmEcuReset)4U)
#endif

#ifndef RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER
#define RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER ((Rte_ModeType_DcmEcuReset)5U)
#endif

#ifndef RTE_MODE_DcmEcuReset_EXECUTE
#define RTE_MODE_DcmEcuReset_EXECUTE ((Rte_ModeType_DcmEcuReset)6U)
#endif

#ifndef RTE_MODETYPE_DcmSesCtrl
#define RTE_MODETYPE_DcmSesCtrl
typedef uint8 Rte_ModeType_DcmSesCtrl;
#endif
#ifndef RTE_TRANSITION_DcmSesCtrl
#define RTE_TRANSITION_DcmSesCtrl ((Rte_ModeType_DcmSesCtrl)4U)
#endif

#ifndef RTE_MODE_DcmSesCtrl_DEFAULT_SESSION
#define RTE_MODE_DcmSesCtrl_DEFAULT_SESSION ((Rte_ModeType_DcmSesCtrl)1U)
#endif

#ifndef RTE_MODE_DcmSesCtrl_RkDcmDspSessionRow_Reprog
#define RTE_MODE_DcmSesCtrl_RkDcmDspSessionRow_Reprog ((Rte_ModeType_DcmSesCtrl)2U)
#endif

#ifndef RTE_MODE_DcmSesCtrl_RkDcmDspSessionRow_Extend
#define RTE_MODE_DcmSesCtrl_RkDcmDspSessionRow_Extend ((Rte_ModeType_DcmSesCtrl)3U)
#endif

#ifndef RTE_MODE_DcmSesCtrl_EXTENDED_DIAGNOSTIC_SESSION
#define RTE_MODE_DcmSesCtrl_EXTENDED_DIAGNOSTIC_SESSION ((Rte_ModeType_DcmSesCtrl)3U)
#endif


#ifndef RTE_MODETYPE_ResponseOnEvent_00
#define RTE_MODETYPE_ResponseOnEvent_00
typedef uint8 Rte_ModeType_ResponseOnEvent_00;
#endif
#ifndef RTE_TRANSITION_ResponseOnEvent_00
#define RTE_TRANSITION_ResponseOnEvent_00 ((Rte_ModeType_ResponseOnEvent_00)3U)
#endif

#ifndef RTE_MODE_ResponseOnEvent_00_DCM_EVENT_STARTED
#define RTE_MODE_ResponseOnEvent_00_DCM_EVENT_STARTED ((Rte_ModeType_ResponseOnEvent_00)0U)
#endif

#ifndef RTE_MODE_ResponseOnEvent_00_DCM_EVENT_STOPPED
#define RTE_MODE_ResponseOnEvent_00_DCM_EVENT_STOPPED ((Rte_ModeType_ResponseOnEvent_00)1U)
#endif

#ifndef RTE_MODE_ResponseOnEvent_00_DCM_EVENT_CLEARED
#define RTE_MODE_ResponseOnEvent_00_DCM_EVENT_CLEARED ((Rte_ModeType_ResponseOnEvent_00)2U)
#endif


#ifndef RTE_MODETYPE_DcmSecurityAccess
#define RTE_MODETYPE_DcmSecurityAccess
typedef uint8 Rte_ModeType_DcmSecurityAccess;
#endif
#ifndef RTE_TRANSITION_DcmSecurityAccess
#define RTE_TRANSITION_DcmSecurityAccess ((Rte_ModeType_DcmSecurityAccess)1U)
#endif

#ifndef RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_LOCKED
#define RTE_MODE_DcmSecurityAccess_DCM_SEC_LEV_LOCKED ((Rte_ModeType_DcmSecurityAccess)0U)
#endif


#ifndef RTE_MODETYPE_DcmAuthenticationState_00
#define RTE_MODETYPE_DcmAuthenticationState_00
typedef uint8 Rte_ModeType_DcmAuthenticationState_00;
#endif
#ifndef RTE_TRANSITION_DcmAuthenticationState_00
#define RTE_TRANSITION_DcmAuthenticationState_00 ((Rte_ModeType_DcmAuthenticationState_00)2U)
#endif

#ifndef RTE_MODE_DcmAuthenticationState_00_DCM_DEAUTHENTICATED
#define RTE_MODE_DcmAuthenticationState_00_DCM_DEAUTHENTICATED ((Rte_ModeType_DcmAuthenticationState_00)0U)
#endif

#ifndef RTE_MODE_DcmAuthenticationState_00_DCM_AUTHENTICATED
#define RTE_MODE_DcmAuthenticationState_00_DCM_AUTHENTICATED ((Rte_ModeType_DcmAuthenticationState_00)1U)
#endif


#ifndef DCM_RES_POS_OK
#define DCM_RES_POS_OK ((Dcm_ConfirmationStatusType)0x00U)
#endif /* DCM_RES_POS_OK */

#ifndef DCM_RES_POS_NOT_OK
#define DCM_RES_POS_NOT_OK ((Dcm_ConfirmationStatusType)0x01U)
#endif /* DCM_RES_POS_NOT_OK */

#ifndef DCM_RES_NEG_OK
#define DCM_RES_NEG_OK ((Dcm_ConfirmationStatusType)0x02U)
#endif /* DCM_RES_NEG_OK */

#ifndef DCM_RES_NEG_NOT_OK
#define DCM_RES_NEG_NOT_OK ((Dcm_ConfirmationStatusType)0x03U)
#endif /* DCM_RES_NEG_NOT_OK */


#ifndef DCM_DID_SUPPORTED
#define DCM_DID_SUPPORTED ((Dcm_DidSupportedType)0x00U)
#endif /* DCM_DID_SUPPORTED */

#ifndef DCM_DID_NOT_SUPPORTED
#define DCM_DID_NOT_SUPPORTED ((Dcm_DidSupportedType)0x01U)
#endif /* DCM_DID_NOT_SUPPORTED */

#ifndef DCM_DTC_KIND_ALL_DTCS
#define DCM_DTC_KIND_ALL_DTCS ((Dcm_DTCKindType)0x01)
#endif /* DCM_DTC_KIND_ALL_DTCS */

#ifndef DCM_DTC_KIND_EMISSION_REL_DTCS
#define DCM_DTC_KIND_EMISSION_REL_DTCS ((Dcm_DTCKindType)0x02)
#endif /* DCM_DTC_KIND_EMISSION_REL_DTCS */


#ifndef DCM_E_BRAKESWITCH_NOTCLOSED
#define DCM_E_BRAKESWITCH_NOTCLOSED ((Dcm_NegativeResponseCodeType)0x8fU)
#endif /* DCM_E_BRAKESWITCH_NOTCLOSED */

#ifndef DCM_E_BUSYREPEATREQUEST
#define DCM_E_BUSYREPEATREQUEST ((Dcm_NegativeResponseCodeType)0x21U)
#endif /* DCM_E_BUSYREPEATREQUEST */

#ifndef DCM_E_CONDITIONSNOTCORRECT
#define DCM_E_CONDITIONSNOTCORRECT ((Dcm_NegativeResponseCodeType)0x22U)
#endif /* DCM_E_CONDITIONSNOTCORRECT */

#ifndef DCM_E_ENGINEISNOTRUNNING
#define DCM_E_ENGINEISNOTRUNNING ((Dcm_NegativeResponseCodeType)0x84U)
#endif /* DCM_E_ENGINEISNOTRUNNING */

#ifndef DCM_E_ENGINEISRUNNING
#define DCM_E_ENGINEISRUNNING ((Dcm_NegativeResponseCodeType)0x83U)
#endif /* DCM_E_ENGINEISRUNNING */

#ifndef DCM_E_ENGINERUNTIMETOOLOW
#define DCM_E_ENGINERUNTIMETOOLOW ((Dcm_NegativeResponseCodeType)0x85U)
#endif /* DCM_E_ENGINERUNTIMETOOLOW */

#ifndef DCM_E_EXCEEDNUMBEROFATTEMPTS
#define DCM_E_EXCEEDNUMBEROFATTEMPTS ((Dcm_NegativeResponseCodeType)0x36U)
#endif /* DCM_E_EXCEEDNUMBEROFATTEMPTS */

#ifndef DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION
#define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION ((Dcm_NegativeResponseCodeType)0x26U)
#endif /* DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION */

#ifndef DCM_E_GENERALPROGRAMMINGFAILURE
#define DCM_E_GENERALPROGRAMMINGFAILURE ((Dcm_NegativeResponseCodeType)0x72U)
#endif /* DCM_E_GENERALPROGRAMMINGFAILURE */

#ifndef DCM_POS_RESP
#define DCM_POS_RESP ((Dcm_NegativeResponseCodeType)0x00U)
#endif /* DCM_POS_RESP */

#ifndef DCM_E_GENERALREJECT
#define DCM_E_GENERALREJECT ((Dcm_NegativeResponseCodeType)0x10U)
#endif /* DCM_E_GENERALREJECT */

#ifndef DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT ((Dcm_NegativeResponseCodeType)0x13U)
#endif /* DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT */

#ifndef DCM_E_INVALIDKEY
#define DCM_E_INVALIDKEY ((Dcm_NegativeResponseCodeType)0x35U)
#endif /* DCM_E_INVALIDKEY */

#ifndef DCM_E_NORESPONSEFROMSUBNETCOMPONENT
#define DCM_E_NORESPONSEFROMSUBNETCOMPONENT ((Dcm_NegativeResponseCodeType)0x25U)
#endif /* DCM_E_NORESPONSEFROMSUBNETCOMPONENT */

#ifndef DCM_E_REQUESTOUTOFRANGE
#define DCM_E_REQUESTOUTOFRANGE ((Dcm_NegativeResponseCodeType)0x31U)
#endif /* DCM_E_REQUESTOUTOFRANGE */

#ifndef DCM_E_REQUESTSEQUENCEERROR
#define DCM_E_REQUESTSEQUENCEERROR ((Dcm_NegativeResponseCodeType)0x24U)
#endif /* DCM_E_REQUESTSEQUENCEERROR */

#ifndef DCM_E_REQUIREDTIMEDELAYNOTEXPIRED
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED ((Dcm_NegativeResponseCodeType)0x37U)
#endif /* DCM_E_REQUIREDTIMEDELAYNOTEXPIRED */

#ifndef DCM_E_RESPONSETOOLONG
#define DCM_E_RESPONSETOOLONG ((Dcm_NegativeResponseCodeType)0x14U)
#endif /* DCM_E_RESPONSETOOLONG */

#ifndef DCM_E_RPMTOOHIGH
#define DCM_E_RPMTOOHIGH ((Dcm_NegativeResponseCodeType)0x81U)
#endif /* DCM_E_RPMTOOHIGH */

#ifndef DCM_E_RPMTOOLOW
#define DCM_E_RPMTOOLOW ((Dcm_NegativeResponseCodeType)0x82U)
#endif /* DCM_E_RPMTOOLOW */

#ifndef DCM_E_SECURITYACCESSDENIED
#define DCM_E_SECURITYACCESSDENIED ((Dcm_NegativeResponseCodeType)0x33U)
#endif /* DCM_E_SECURITYACCESSDENIED */

#ifndef DCM_E_AUTHENTICATIONREQUIRED
#define DCM_E_AUTHENTICATIONREQUIRED ((Dcm_NegativeResponseCodeType)0x34U)
#endif /* DCM_E_AUTHENTICATIONREQUIRED */

#ifndef DCM_E_SERVICENOTSUPPORTED
#define DCM_E_SERVICENOTSUPPORTED ((Dcm_NegativeResponseCodeType)0x11U)
#endif /* DCM_E_SERVICENOTSUPPORTED */

#ifndef DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION ((Dcm_NegativeResponseCodeType)0x7fU)
#endif /* DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION */

#ifndef DCM_E_SHIFTERLEVERNOTINPARK
#define DCM_E_SHIFTERLEVERNOTINPARK ((Dcm_NegativeResponseCodeType)0x90U)
#endif /* DCM_E_SHIFTERLEVERNOTINPARK */

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTED
#define DCM_E_SUBFUNCTIONNOTSUPPORTED ((Dcm_NegativeResponseCodeType)0x12U)
#endif /* DCM_E_SUBFUNCTIONNOTSUPPORTED */

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION ((Dcm_NegativeResponseCodeType)0x7eU)
#endif /* DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION */

#ifndef DCM_E_TEMPERATURETOOHIGH
#define DCM_E_TEMPERATURETOOHIGH ((Dcm_NegativeResponseCodeType)0x86U)
#endif /* DCM_E_TEMPERATURETOOHIGH */

#ifndef DCM_E_TEMPERATURETOOLOW
#define DCM_E_TEMPERATURETOOLOW ((Dcm_NegativeResponseCodeType)0x87U)
#endif /* DCM_E_TEMPERATURETOOLOW */

#ifndef DCM_E_THROTTLE_PEDALTOOHIGH
#define DCM_E_THROTTLE_PEDALTOOHIGH ((Dcm_NegativeResponseCodeType)0x8aU)
#endif /* DCM_E_THROTTLE_PEDALTOOHIGH */

#ifndef DCM_E_THROTTLE_PEDALTOOLOW
#define DCM_E_THROTTLE_PEDALTOOLOW ((Dcm_NegativeResponseCodeType)0x8bU)
#endif /* DCM_E_THROTTLE_PEDALTOOLOW */

#ifndef DCM_E_TORQUECONVERTERCLUTCHLOCKED
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED ((Dcm_NegativeResponseCodeType)0x91U)
#endif /* DCM_E_TORQUECONVERTERCLUTCHLOCKED */

#ifndef DCM_E_TRANSFERDATASUSPENDED
#define DCM_E_TRANSFERDATASUSPENDED ((Dcm_NegativeResponseCodeType)0x71U)
#endif /* DCM_E_TRANSFERDATASUSPENDED */

#ifndef DCM_E_TRANSMISSIONRANGENOTINGEAR
#define DCM_E_TRANSMISSIONRANGENOTINGEAR ((Dcm_NegativeResponseCodeType)0x8dU)
#endif /* DCM_E_TRANSMISSIONRANGENOTINGEAR */

#ifndef DCM_E_TRANSMISSIONRANGENOTINNEUTRAL
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL ((Dcm_NegativeResponseCodeType)0x8cU)
#endif /* DCM_E_TRANSMISSIONRANGENOTINNEUTRAL */

#ifndef DCM_E_UPLOADDOWNLOADNOTACCEPTED
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED ((Dcm_NegativeResponseCodeType)0x70U)
#endif /* DCM_E_UPLOADDOWNLOADNOTACCEPTED */

#ifndef DCM_E_VEHICLESPEEDTOOHIGH
#define DCM_E_VEHICLESPEEDTOOHIGH ((Dcm_NegativeResponseCodeType)0x88U)
#endif /* DCM_E_VEHICLESPEEDTOOHIGH */

#ifndef DCM_E_VEHICLESPEEDTOOLOW
#define DCM_E_VEHICLESPEEDTOOLOW ((Dcm_NegativeResponseCodeType)0x89U)
#endif /* DCM_E_VEHICLESPEEDTOOLOW */

#ifndef DCM_E_VOLTAGETOOHIGH
#define DCM_E_VOLTAGETOOHIGH ((Dcm_NegativeResponseCodeType)0x92U)
#endif /* DCM_E_VOLTAGETOOHIGH */

#ifndef DCM_E_VOLTAGETOOLOW
#define DCM_E_VOLTAGETOOLOW ((Dcm_NegativeResponseCodeType)0x93U)
#endif /* DCM_E_VOLTAGETOOLOW */

#ifndef DCM_E_WRONGBLOCKSEQUENCECOUNTER
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER ((Dcm_NegativeResponseCodeType)0x73U)
#endif /* DCM_E_WRONGBLOCKSEQUENCECOUNTER */

#ifndef DCM_E_VMSCNC_0
#define DCM_E_VMSCNC_0 ((Dcm_NegativeResponseCodeType)0xf0U)
#endif /* DCM_E_VMSCNC_0 */

#ifndef DCM_E_VMSCNC_1
#define DCM_E_VMSCNC_1 ((Dcm_NegativeResponseCodeType)0xf1U)
#endif /* DCM_E_VMSCNC_1 */

#ifndef DCM_E_VMSCNC_2
#define DCM_E_VMSCNC_2 ((Dcm_NegativeResponseCodeType)0xf2U)
#endif /* DCM_E_VMSCNC_2 */

#ifndef DCM_E_VMSCNC_3
#define DCM_E_VMSCNC_3 ((Dcm_NegativeResponseCodeType)0xf3U)
#endif /* DCM_E_VMSCNC_3 */

#ifndef DCM_E_VMSCNC_4
#define DCM_E_VMSCNC_4 ((Dcm_NegativeResponseCodeType)0xf4U)
#endif /* DCM_E_VMSCNC_4 */

#ifndef DCM_E_VMSCNC_5
#define DCM_E_VMSCNC_5 ((Dcm_NegativeResponseCodeType)0xf5U)
#endif /* DCM_E_VMSCNC_5 */

#ifndef DCM_E_VMSCNC_6
#define DCM_E_VMSCNC_6 ((Dcm_NegativeResponseCodeType)0xf6U)
#endif /* DCM_E_VMSCNC_6 */

#ifndef DCM_E_VMSCNC_7
#define DCM_E_VMSCNC_7 ((Dcm_NegativeResponseCodeType)0xf7U)
#endif /* DCM_E_VMSCNC_7 */

#ifndef DCM_E_VMSCNC_8
#define DCM_E_VMSCNC_8 ((Dcm_NegativeResponseCodeType)0xf8U)
#endif /* DCM_E_VMSCNC_8 */

#ifndef DCM_E_VMSCNC_9
#define DCM_E_VMSCNC_9 ((Dcm_NegativeResponseCodeType)0xf9U)
#endif /* DCM_E_VMSCNC_9 */

#ifndef DCM_E_VMSCNC_A
#define DCM_E_VMSCNC_A ((Dcm_NegativeResponseCodeType)0xfaU)
#endif /* DCM_E_VMSCNC_A */

#ifndef DCM_E_VMSCNC_B
#define DCM_E_VMSCNC_B ((Dcm_NegativeResponseCodeType)0xfbU)
#endif /* DCM_E_VMSCNC_B */

#ifndef DCM_E_VMSCNC_C
#define DCM_E_VMSCNC_C ((Dcm_NegativeResponseCodeType)0xfcU)
#endif /* DCM_E_VMSCNC_C */

#ifndef DCM_E_VMSCNC_D
#define DCM_E_VMSCNC_D ((Dcm_NegativeResponseCodeType)0xfdU)
#endif /* DCM_E_VMSCNC_D */

#ifndef DCM_E_VMSCNC_E
#define DCM_E_VMSCNC_E ((Dcm_NegativeResponseCodeType)0xfeU)
#endif /* DCM_E_VMSCNC_E */


#ifndef DCM_INITIAL
#define DCM_INITIAL ((Dcm_OpStatusType)0x00U)
#endif /* DCM_INITIAL */

#ifndef DCM_PENDING
#define DCM_PENDING ((Dcm_OpStatusType)0x01U)
#endif /* DCM_PENDING */

#ifndef DCM_CANCEL
#define DCM_CANCEL ((Dcm_OpStatusType)0x02U)
#endif /* DCM_CANCEL */

#ifndef DCM_FORCE_RCRRP_OK
#define DCM_FORCE_RCRRP_OK ((Dcm_OpStatusType)0x03U)
#endif /* DCM_FORCE_RCRRP_OK */

#ifndef DCM_UPDATE_PAGE_OK
#define DCM_UPDATE_PAGE_OK ((Dcm_OpStatusType)0x10U)
#endif /* DCM_UPDATE_PAGE_OK */

#ifndef DCM_PERIODIC_INITIAL
#define DCM_PERIODIC_INITIAL ((Dcm_OpStatusType)0x11U)
#endif /* DCM_PERIODIC_INITIAL */

#ifndef DCM_PERIODIC_PENDING
#define DCM_PERIODIC_PENDING ((Dcm_OpStatusType)0x12U)
#endif /* DCM_PERIODIC_PENDING */

#ifndef DCM_PERIODIC_CANCEL
#define DCM_PERIODIC_CANCEL ((Dcm_OpStatusType)0x13U)
#endif /* DCM_PERIODIC_CANCEL */

#ifndef DCM_OBD_ON_CAN
#define DCM_OBD_ON_CAN ((Dcm_ProtocolType)0x00U)
#endif /* DCM_OBD_ON_CAN */

#ifndef DCM_OBD_ON_FLEXRAY
#define DCM_OBD_ON_FLEXRAY ((Dcm_ProtocolType)0x01U)
#endif /* DCM_OBD_ON_FLEXRAY */

#ifndef DCM_OBD_ON_IP
#define DCM_OBD_ON_IP ((Dcm_ProtocolType)0x02U)
#endif /* DCM_OBD_ON_IP */

#ifndef DCM_UDS_ON_CAN
#define DCM_UDS_ON_CAN ((Dcm_ProtocolType)0x03U)
#endif /* DCM_UDS_ON_CAN */

#ifndef DCM_UDS_ON_FLEXRAY
#define DCM_UDS_ON_FLEXRAY ((Dcm_ProtocolType)0x04U)
#endif /* DCM_UDS_ON_FLEXRAY */

#ifndef DCM_UDS_ON_IP
#define DCM_UDS_ON_IP ((Dcm_ProtocolType)0x05U)
#endif /* DCM_UDS_ON_IP */

#ifndef DCM_ROE_ON_CAN
#define DCM_ROE_ON_CAN ((Dcm_ProtocolType)0x06U)
#endif /* DCM_ROE_ON_CAN */

#ifndef DCM_ROE_ON_FLEXRAY
#define DCM_ROE_ON_FLEXRAY ((Dcm_ProtocolType)0x07U)
#endif /* DCM_ROE_ON_FLEXRAY */

#ifndef DCM_ROE_ON_IP
#define DCM_ROE_ON_IP ((Dcm_ProtocolType)0x08U)
#endif /* DCM_ROE_ON_IP */

#ifndef DCM_PERIODICTRANS_ON_CAN
#define DCM_PERIODICTRANS_ON_CAN ((Dcm_ProtocolType)0x09U)
#endif /* DCM_PERIODICTRANS_ON_CAN */

#ifndef DCM_PERIODICTRANS_ON_FLEXRAY
#define DCM_PERIODICTRANS_ON_FLEXRAY ((Dcm_ProtocolType)0x0aU)
#endif /* DCM_PERIODICTRANS_ON_FLEXRAY */

#ifndef DCM_PERIODICTRANS_ON_IP
#define DCM_PERIODICTRANS_ON_IP ((Dcm_ProtocolType)0x0bU)
#endif /* DCM_PERIODICTRANS_ON_IP */

#ifndef DCM_NO_ACTIVE_PROTOCOL
#define DCM_NO_ACTIVE_PROTOCOL ((Dcm_ProtocolType)0x0cU)
#endif /* DCM_NO_ACTIVE_PROTOCOL */

#ifndef DCM_UDS_ON_LIN
#define DCM_UDS_ON_LIN ((Dcm_ProtocolType)0x0dU)
#endif /* DCM_UDS_ON_LIN */

#ifndef DCM_SUPPLIER_1
#define DCM_SUPPLIER_1 ((Dcm_ProtocolType)0xf0U)
#endif /* DCM_SUPPLIER_1 */

#ifndef DCM_SUPPLIER_2
#define DCM_SUPPLIER_2 ((Dcm_ProtocolType)0xf1U)
#endif /* DCM_SUPPLIER_2 */

#ifndef DCM_SUPPLIER_3
#define DCM_SUPPLIER_3 ((Dcm_ProtocolType)0xf2U)
#endif /* DCM_SUPPLIER_3 */

#ifndef DCM_SUPPLIER_4
#define DCM_SUPPLIER_4 ((Dcm_ProtocolType)0xf3U)
#endif /* DCM_SUPPLIER_4 */

#ifndef DCM_SUPPLIER_5
#define DCM_SUPPLIER_5 ((Dcm_ProtocolType)0xf4U)
#endif /* DCM_SUPPLIER_5 */

#ifndef DCM_SUPPLIER_6
#define DCM_SUPPLIER_6 ((Dcm_ProtocolType)0xf5U)
#endif /* DCM_SUPPLIER_6 */

#ifndef DCM_SUPPLIER_7
#define DCM_SUPPLIER_7 ((Dcm_ProtocolType)0xf6U)
#endif /* DCM_SUPPLIER_7 */

#ifndef DCM_SUPPLIER_8
#define DCM_SUPPLIER_8 ((Dcm_ProtocolType)0xf7U)
#endif /* DCM_SUPPLIER_8 */

#ifndef DCM_SUPPLIER_9
#define DCM_SUPPLIER_9 ((Dcm_ProtocolType)0xf8U)
#endif /* DCM_SUPPLIER_9 */

#ifndef DCM_SUPPLIER_10
#define DCM_SUPPLIER_10 ((Dcm_ProtocolType)0xf9U)
#endif /* DCM_SUPPLIER_10 */

#ifndef DCM_SUPPLIER_11
#define DCM_SUPPLIER_11 ((Dcm_ProtocolType)0xfaU)
#endif /* DCM_SUPPLIER_11 */

#ifndef DCM_SUPPLIER_12
#define DCM_SUPPLIER_12 ((Dcm_ProtocolType)0xfbU)
#endif /* DCM_SUPPLIER_12 */

#ifndef DCM_SUPPLIER_13
#define DCM_SUPPLIER_13 ((Dcm_ProtocolType)0xfcU)
#endif /* DCM_SUPPLIER_13 */

#ifndef DCM_SUPPLIER_14
#define DCM_SUPPLIER_14 ((Dcm_ProtocolType)0xfdU)
#endif /* DCM_SUPPLIER_14 */

#ifndef DCM_SUPPLIER_15
#define DCM_SUPPLIER_15 ((Dcm_ProtocolType)0xfeU)
#endif /* DCM_SUPPLIER_15 */


#ifndef DCM_SEC_LEV_LOCKED
#define DCM_SEC_LEV_LOCKED ((Dcm_SecLevelType)0x00U)
#endif /* DCM_SEC_LEV_LOCKED */


#ifndef DCM_DEFAULT_SESSION
#define DCM_DEFAULT_SESSION ((Dcm_SesCtrlType)0x01U)
#endif /* DCM_DEFAULT_SESSION */

#ifndef DCM_RkDcmDspSessionRow_Reprog
#define DCM_RkDcmDspSessionRow_Reprog ((Dcm_SesCtrlType)0x02U)
#endif /* DCM_RkDcmDspSessionRow_Reprog */

#ifndef DCM_RkDcmDspSessionRow_Extend
#define DCM_RkDcmDspSessionRow_Extend ((Dcm_SesCtrlType)0x03U)
#endif /* DCM_RkDcmDspSessionRow_Extend */

#ifndef DCM_EXTENDED_DIAGNOSTIC_SESSION
#define DCM_EXTENDED_DIAGNOSTIC_SESSION ((Dcm_SesCtrlType)0x03U)
#endif /* DCM_EXTENDED_DIAGNOSTIC_SESSION */


/* Bitfield mask [SWS_Rte_07410] */
#ifndef DCM_EXE_NONE_BflMask
#define DCM_EXE_NONE_BflMask ((Dcm_ActiveStateType)255U) /* 0b11111111 */
#endif /* DCM_EXE_NONE_BflMask */
/* Bitfield bit start position [SWS_Rte_07411] */
#ifndef DCM_EXE_NONE_BflPn
#define DCM_EXE_NONE_BflPn ((uint8)0U)
#endif /* DCM_EXE_NONE_BflPn */
/* Bitfield bit field length [SWS_Rte_07412] */
#ifndef DCM_EXE_NONE_BflLn
#define DCM_EXE_NONE_BflLn ((uint8)8U)
#endif /* DCM_EXE_NONE_BflLn */
/* Bitfield mask [SWS_Rte_07410] */
#ifndef DCM_EXE_PERIODIC_BflMask
#define DCM_EXE_PERIODIC_BflMask ((Dcm_ActiveStateType)255U) /* 0b11111111 */
#endif /* DCM_EXE_PERIODIC_BflMask */
/* Bitfield bit start position [SWS_Rte_07411] */
#ifndef DCM_EXE_PERIODIC_BflPn
#define DCM_EXE_PERIODIC_BflPn ((uint8)0U)
#endif /* DCM_EXE_PERIODIC_BflPn */
/* Bitfield bit field length [SWS_Rte_07412] */
#ifndef DCM_EXE_PERIODIC_BflLn
#define DCM_EXE_PERIODIC_BflLn ((uint8)8U)
#endif /* DCM_EXE_PERIODIC_BflLn */
/* Bitfield mask [SWS_Rte_07410] */
#ifndef DCM_EXE_ROE_BflMask
#define DCM_EXE_ROE_BflMask ((Dcm_ActiveStateType)255U) /* 0b11111111 */
#endif /* DCM_EXE_ROE_BflMask */
/* Bitfield bit start position [SWS_Rte_07411] */
#ifndef DCM_EXE_ROE_BflPn
#define DCM_EXE_ROE_BflPn ((uint8)0U)
#endif /* DCM_EXE_ROE_BflPn */
/* Bitfield bit field length [SWS_Rte_07412] */
#ifndef DCM_EXE_ROE_BflLn
#define DCM_EXE_ROE_BflLn ((uint8)8U)
#endif /* DCM_EXE_ROE_BflLn */

#ifndef DCM_EXE_NONE
#define DCM_EXE_NONE                 ((Dcm_ActiveStateType)0x00U)
#endif /* DCM_EXE_NONE */

#ifndef DCM_EXE_PERIODIC
#define DCM_EXE_PERIODIC             ((Dcm_ActiveStateType)0x01U)
#endif /* DCM_EXE_PERIODIC */

#ifndef DCM_EXE_ROE
#define DCM_EXE_ROE                  ((Dcm_ActiveStateType)0x02U)
#endif /* DCM_EXE_ROE */

#ifndef DCM_DID_REQTYPE_READ
#define DCM_DID_REQTYPE_READ ((Dcm_DidRequestType)0x00U)
#endif /* DCM_DID_REQTYPE_READ */

#ifndef DCM_DID_REQTYPE_WRITE
#define DCM_DID_REQTYPE_WRITE ((Dcm_DidRequestType)0x01U)
#endif /* DCM_DID_REQTYPE_WRITE */

#ifndef DCM_DID_REQTYPE_CONTROL
#define DCM_DID_REQTYPE_CONTROL ((Dcm_DidRequestType)0x02U)
#endif /* DCM_DID_REQTYPE_CONTROL */

#ifndef DCM_DID_REQTYPE_DYNAMIC_DDDID
#define DCM_DID_REQTYPE_DYNAMIC_DDDID ((Dcm_DidRequestType)0x03U)
#endif /* DCM_DID_REQTYPE_DYNAMIC_DDDID */

#ifndef DCM_DID_REQTYPE_DYNAMIC_SOURCE
#define DCM_DID_REQTYPE_DYNAMIC_SOURCE ((Dcm_DidRequestType)0x04U)
#endif /* DCM_DID_REQTYPE_DYNAMIC_SOURCE */

#ifndef DCM_RETURN_CONTROL_TO_ECU
#define DCM_RETURN_CONTROL_TO_ECU  ((Dcm_InputOutputControlParameterType)0x00U)
#endif /* DCM_RETURN_CONTROL_TO_ECU */

#ifndef DCM_RESET_TO_DEFAULT
#define DCM_RESET_TO_DEFAULT       ((Dcm_InputOutputControlParameterType)0x01U)
#endif /* DCM_RESET_TO_DEFAULT */

#ifndef DCM_FREEZE_CURRENT_STATE
#define DCM_FREEZE_CURRENT_STATE   ((Dcm_InputOutputControlParameterType)0x02U)
#endif /* DCM_FREEZE_CURRENT_STATE */

#ifndef DCM_SHORT_TERM_ADJUSTMENT
#define DCM_SHORT_TERM_ADJUSTMENT  ((Dcm_InputOutputControlParameterType)0x03U)
#endif /* DCM_SHORT_TERM_ADJUSTMENT */

#ifndef DCM_IDLE
#define DCM_IDLE                   ((Dcm_InputOutputControlParameterType)0xFFU)
#endif /* DCM_IDLE */

#ifndef DCM_POSITIVE_RESPONSE
#define DCM_POSITIVE_RESPONSE           (0x00U)
#endif /* DCM_POSITIVE_RESPONSE */

#ifndef DCM_GENERAL_REJECT
#define DCM_GENERAL_REJECT              (0x10U)
#endif /* DCM_GENERAL_REJECT */

#ifndef DCM_BUSY_REPEAT_REQUEST
#define DCM_BUSY_REPEAT_REQUEST         (0x21U)
#endif /* DCM_BUSY_REPEAT_REQUEST */

#ifndef DCM_CONDITIONS_NOT_CORRECT
#define DCM_CONDITIONS_NOT_CORRECT      (0x22U)
#endif /* DCM_CONDITIONS_NOT_CORRECT */

#ifndef DCM_FAILURE_PREVENTS_EXECUTION
#define DCM_FAILURE_PREVENTS_EXECUTION  (0x26U)
#endif /* DCM_FAILURE_PREVENTS_EXECUTION */

#ifndef DCM_REQUEST_OUT_OF_RANGE
#define DCM_REQUEST_OUT_OF_RANGE        (0x31U)
#endif /* DCM_REQUEST_OUT_OF_RANGE */

#ifndef DCM_RESPONSE_PENDING
#define DCM_RESPONSE_PENDING            (0x78U)
#endif /* DCM_RESPONSE_PENDING */



#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* RTE_Dcm_TYPE_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
