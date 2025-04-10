/* bsw_canif_public_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANIF/PUBLIC/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANIF_PUBLIC_H
#define     BSW_CANIF_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANIF_BUSY                  (2U)

#define BSW_CANIF_OFFLINE               (0U)
#define BSW_CANIF_TX_OFFLINE            (1U)
#define BSW_CANIF_TX_OFFLINE_ACTIVE     (2U)
#define BSW_CANIF_ONLINE                (3U)

#define BSW_CANIF_NO_NOTIFICATION       (0U)
#define BSW_CANIF_TX_RX_NOTIFICATION    (1U)

#define BSW_CANIF_FAIL_NONE             (0x0000U)
#define BSW_CANIF_FAIL_BUSOFF           (0x0001U)
#define BSW_CANIF_FAIL_SNDLOCK          (0x0002U)
#define BSW_CANIF_FAIL_RCVLOCK          (0x0004U)
#define BSW_CANIF_FAIL_REGCHECK         (0x0008U)
#define BSW_CANIF_FAIL_UNUSEDREGCHK     (0x0010U)
#define BSW_CANIF_FAIL_MPU              (0x0020U)
#define BSW_CANIF_FAIL_INITNG           (0x0040U)
#define BSW_CANIF_FAIL_USER             (0x0080U)
#define BSW_CANIF_FAIL_NMTXTIMEOUT_STABLE    (0x0100U)
#define BSW_CANIF_FAIL_NMTXTIMEOUT_UNSTABLE  (0x0200U)

#define BSW_CANIF_KIND_NMTXTIMEOUT_STABLE    (0U)
#define BSW_CANIF_KIND_NMTXTIMEOUT_UNSTABLE  (1U)

#define BSW_CANIF_STATUS_ERROR_ACTIVE   (0U)
#define BSW_CANIF_STATUS_ERROR_PASSIVE  (1U)
#define BSW_CANIF_STATUS_BUSOFF         (2U)
#define BSW_CANIF_STATUS_INVALID        (3U)

#define BSW_CANIF_EDGE_NONE             (0U)
#define BSW_CANIF_EDGE_EXIST            (1U)

#define BSW_CANIF_CONTROLLER_INVALID    (0xFFU)
#define BSW_CANIF_CANID_INVALID         (0xFFFFFFFFUL)

#define BSW_CANIF_STATE_MPUINIT         (0U)
#define BSW_CANIF_STATE_INIT            (1U)
#define BSW_CANIF_STATE_READY           (2U)
#define BSW_CANIF_STATE_RUN             (3U)

#define BSW_CANIF_COMP_PDUR             (0x00U)
#define BSW_CANIF_COMP_CANNM            (0x01U)
#define BSW_CANIF_COMP_CANTP            (0x02U)
#define BSW_CANIF_COMP_CDD1             (0x03U)
#define BSW_CANIF_COMP_CDD2             (0x04U)
#define BSW_CANIF_COMP_XCP              (0x05U)
#define BSW_CANIF_COMP_NONE             (0xFFU)

#define BSW_CANIF_COMP_BIT_PDUR         (1U << BSW_CANIF_COMP_PDUR)
#define BSW_CANIF_COMP_BIT_CANNM        (1U << BSW_CANIF_COMP_CANNM)
#define BSW_CANIF_COMP_BIT_CANTP        (1U << BSW_CANIF_COMP_CANTP)
#define BSW_CANIF_COMP_BIT_CDD1         (1U << BSW_CANIF_COMP_CDD1)
#define BSW_CANIF_COMP_BIT_CDD2         (1U << BSW_CANIF_COMP_CDD2)
#define BSW_CANIF_COMP_BIT_XCP          (1U << BSW_CANIF_COMP_XCP)
#define BSW_CANIF_COMP_BIT_NONE         (0x00U)

#define BSW_CANIF_SNDREQ_SHIFT          (8U)
#define BSW_CANIF_SNDREQ_PDUR           ((uint16)BSW_CANIF_COMP_PDUR  << BSW_CANIF_SNDREQ_SHIFT)
#define BSW_CANIF_SNDREQ_CANNM          ((uint16)BSW_CANIF_COMP_CANNM << BSW_CANIF_SNDREQ_SHIFT)
#define BSW_CANIF_SNDREQ_CANTP          ((uint16)BSW_CANIF_COMP_CANTP << BSW_CANIF_SNDREQ_SHIFT)
#define BSW_CANIF_SNDREQ_CDD1           ((uint16)BSW_CANIF_COMP_CDD1  << BSW_CANIF_SNDREQ_SHIFT)
#define BSW_CANIF_SNDREQ_CDD2           ((uint16)BSW_CANIF_COMP_CDD2  << BSW_CANIF_SNDREQ_SHIFT)
#define BSW_CANIF_SNDREQ_XCP            ((uint16)BSW_CANIF_COMP_XCP   << BSW_CANIF_SNDREQ_SHIFT)

#define BSW_CANIF_SNDREQ_QUE000         (0x00U)
#define BSW_CANIF_SNDREQ_QUE001         (0x01U)
#define BSW_CANIF_SNDREQ_QUE002         (0x02U)
#define BSW_CANIF_SNDREQ_QUE003         (0x03U)
#define BSW_CANIF_SNDREQ_QUE004         (0x04U)
#define BSW_CANIF_SNDREQ_QUE005         (0x05U)
#define BSW_CANIF_SNDREQ_QUE006         (0x06U)
#define BSW_CANIF_SNDREQ_QUE007         (0x07U)
#define BSW_CANIF_SNDREQ_QUE008         (0x08U)
#define BSW_CANIF_SNDREQ_QUE009         (0x09U)
#define BSW_CANIF_SNDREQ_QUE010         (0x0AU)
#define BSW_CANIF_SNDREQ_QUE011         (0x0BU)
#define BSW_CANIF_SNDREQ_QUE012         (0x0CU)
#define BSW_CANIF_SNDREQ_QUE013         (0x0DU)
#define BSW_CANIF_SNDREQ_QUE014         (0x0EU)
#define BSW_CANIF_SNDREQ_QUE015         (0x0FU)
#define BSW_CANIF_SNDREQ_QUE016         (0x10U)
#define BSW_CANIF_SNDREQ_QUE017         (0x11U)
#define BSW_CANIF_SNDREQ_QUE018         (0x12U)
#define BSW_CANIF_SNDREQ_QUE019         (0x13U)
#define BSW_CANIF_SNDREQ_QUE020         (0x14U)
#define BSW_CANIF_SNDREQ_QUE021         (0x15U)
#define BSW_CANIF_SNDREQ_QUE022         (0x16U)
#define BSW_CANIF_SNDREQ_QUE023         (0x17U)
#define BSW_CANIF_SNDREQ_QUE024         (0x18U)
#define BSW_CANIF_SNDREQ_QUE025         (0x19U)
#define BSW_CANIF_SNDREQ_QUE026         (0x1AU)
#define BSW_CANIF_SNDREQ_QUE027         (0x1BU)
#define BSW_CANIF_SNDREQ_QUE028         (0x1CU)
#define BSW_CANIF_SNDREQ_QUE029         (0x1DU)
#define BSW_CANIF_SNDREQ_QUE030         (0x1EU)
#define BSW_CANIF_SNDREQ_QUE031         (0x1FU)
#define BSW_CANIF_SNDREQ_QUE032         (0x20U)
#define BSW_CANIF_SNDREQ_QUE033         (0x21U)
#define BSW_CANIF_SNDREQ_QUE034         (0x22U)
#define BSW_CANIF_SNDREQ_QUE035         (0x23U)
#define BSW_CANIF_SNDREQ_QUE036         (0x24U)
#define BSW_CANIF_SNDREQ_QUE037         (0x25U)
#define BSW_CANIF_SNDREQ_QUE038         (0x26U)
#define BSW_CANIF_SNDREQ_QUE039         (0x27U)
#define BSW_CANIF_SNDREQ_QUE040         (0x28U)
#define BSW_CANIF_SNDREQ_QUE041         (0x29U)
#define BSW_CANIF_SNDREQ_QUE042         (0x2AU)
#define BSW_CANIF_SNDREQ_QUE043         (0x2BU)
#define BSW_CANIF_SNDREQ_QUE044         (0x2CU)
#define BSW_CANIF_SNDREQ_QUE045         (0x2DU)
#define BSW_CANIF_SNDREQ_QUE046         (0x2EU)
#define BSW_CANIF_SNDREQ_QUE047         (0x2FU)
#define BSW_CANIF_SNDREQ_QUE048         (0x30U)
#define BSW_CANIF_SNDREQ_QUE049         (0x31U)
#define BSW_CANIF_SNDREQ_QUE050         (0x32U)
#define BSW_CANIF_SNDREQ_QUE051         (0x33U)
#define BSW_CANIF_SNDREQ_QUE052         (0x34U)
#define BSW_CANIF_SNDREQ_QUE053         (0x35U)
#define BSW_CANIF_SNDREQ_QUE054         (0x36U)
#define BSW_CANIF_SNDREQ_QUE055         (0x37U)
#define BSW_CANIF_SNDREQ_QUE056         (0x38U)
#define BSW_CANIF_SNDREQ_QUE057         (0x39U)
#define BSW_CANIF_SNDREQ_QUE058         (0x3AU)
#define BSW_CANIF_SNDREQ_QUE059         (0x3BU)
#define BSW_CANIF_SNDREQ_QUE060         (0x3CU)
#define BSW_CANIF_SNDREQ_QUE061         (0x3DU)
#define BSW_CANIF_SNDREQ_QUE062         (0x3EU)
#define BSW_CANIF_SNDREQ_QUE063         (0x3FU)
#define BSW_CANIF_SNDREQ_QUE064         (0x40U)
#define BSW_CANIF_SNDREQ_QUE065         (0x41U)
#define BSW_CANIF_SNDREQ_QUE066         (0x42U)
#define BSW_CANIF_SNDREQ_QUE067         (0x43U)
#define BSW_CANIF_SNDREQ_QUE068         (0x44U)
#define BSW_CANIF_SNDREQ_QUE069         (0x45U)
#define BSW_CANIF_SNDREQ_QUE070         (0x46U)
#define BSW_CANIF_SNDREQ_QUE071         (0x47U)
#define BSW_CANIF_SNDREQ_QUE072         (0x48U)
#define BSW_CANIF_SNDREQ_QUE073         (0x49U)
#define BSW_CANIF_SNDREQ_QUE074         (0x4AU)
#define BSW_CANIF_SNDREQ_QUE075         (0x4BU)
#define BSW_CANIF_SNDREQ_QUE076         (0x4CU)
#define BSW_CANIF_SNDREQ_QUE077         (0x4DU)
#define BSW_CANIF_SNDREQ_QUE078         (0x4EU)
#define BSW_CANIF_SNDREQ_QUE079         (0x4FU)
#define BSW_CANIF_SNDREQ_QUE080         (0x50U)
#define BSW_CANIF_SNDREQ_QUE081         (0x51U)
#define BSW_CANIF_SNDREQ_QUE082         (0x52U)
#define BSW_CANIF_SNDREQ_QUE083         (0x53U)
#define BSW_CANIF_SNDREQ_QUE084         (0x54U)
#define BSW_CANIF_SNDREQ_QUE085         (0x55U)
#define BSW_CANIF_SNDREQ_QUE086         (0x56U)
#define BSW_CANIF_SNDREQ_QUE087         (0x57U)
#define BSW_CANIF_SNDREQ_QUE088         (0x58U)
#define BSW_CANIF_SNDREQ_QUE089         (0x59U)
#define BSW_CANIF_SNDREQ_QUE090         (0x5AU)
#define BSW_CANIF_SNDREQ_QUE091         (0x5BU)
#define BSW_CANIF_SNDREQ_QUE092         (0x5CU)
#define BSW_CANIF_SNDREQ_QUE093         (0x5DU)
#define BSW_CANIF_SNDREQ_QUE094         (0x5EU)
#define BSW_CANIF_SNDREQ_QUE095         (0x5FU)
#define BSW_CANIF_SNDREQ_QUE096         (0x60U)
#define BSW_CANIF_SNDREQ_QUE097         (0x61U)
#define BSW_CANIF_SNDREQ_QUE098         (0x62U)
#define BSW_CANIF_SNDREQ_QUE099         (0x63U)
#define BSW_CANIF_SNDREQ_QUE100         (0x64U)
#define BSW_CANIF_SNDREQ_QUE101         (0x65U)
#define BSW_CANIF_SNDREQ_QUE102         (0x66U)
#define BSW_CANIF_SNDREQ_QUE103         (0x67U)
#define BSW_CANIF_SNDREQ_QUE104         (0x68U)
#define BSW_CANIF_SNDREQ_QUE105         (0x69U)
#define BSW_CANIF_SNDREQ_QUE106         (0x6AU)
#define BSW_CANIF_SNDREQ_QUE107         (0x6BU)
#define BSW_CANIF_SNDREQ_QUE108         (0x6CU)
#define BSW_CANIF_SNDREQ_QUE109         (0x6DU)
#define BSW_CANIF_SNDREQ_QUE110         (0x6EU)
#define BSW_CANIF_SNDREQ_QUE111         (0x6FU)
#define BSW_CANIF_SNDREQ_QUE112         (0x70U)
#define BSW_CANIF_SNDREQ_QUE113         (0x71U)
#define BSW_CANIF_SNDREQ_QUE114         (0x72U)
#define BSW_CANIF_SNDREQ_QUE115         (0x73U)
#define BSW_CANIF_SNDREQ_QUE116         (0x74U)
#define BSW_CANIF_SNDREQ_QUE117         (0x75U)
#define BSW_CANIF_SNDREQ_QUE118         (0x76U)
#define BSW_CANIF_SNDREQ_QUE119         (0x77U)
#define BSW_CANIF_SNDREQ_QUE120         (0x78U)
#define BSW_CANIF_SNDREQ_QUE121         (0x79U)
#define BSW_CANIF_SNDREQ_QUE122         (0x7AU)
#define BSW_CANIF_SNDREQ_QUE123         (0x7BU)
#define BSW_CANIF_SNDREQ_QUE124         (0x7CU)
#define BSW_CANIF_SNDREQ_QUE125         (0x7DU)
#define BSW_CANIF_SNDREQ_QUE126         (0x7EU)
#define BSW_CANIF_SNDREQ_QUE127         (0x7FU)
#define BSW_CANIF_SNDREQ_QUE128         (0x80U)
#define BSW_CANIF_SNDREQ_QUE129         (0x81U)
#define BSW_CANIF_SNDREQ_QUE130         (0x82U)
#define BSW_CANIF_SNDREQ_QUE131         (0x83U)
#define BSW_CANIF_SNDREQ_QUE132         (0x84U)
#define BSW_CANIF_SNDREQ_QUE133         (0x85U)
#define BSW_CANIF_SNDREQ_QUE134         (0x86U)
#define BSW_CANIF_SNDREQ_QUE135         (0x87U)
#define BSW_CANIF_SNDREQ_QUE136         (0x88U)
#define BSW_CANIF_SNDREQ_QUE137         (0x89U)
#define BSW_CANIF_SNDREQ_QUE138         (0x8AU)
#define BSW_CANIF_SNDREQ_QUE139         (0x8BU)
#define BSW_CANIF_SNDREQ_QUE140         (0x8CU)
#define BSW_CANIF_SNDREQ_QUE141         (0x8DU)
#define BSW_CANIF_SNDREQ_QUE142         (0x8EU)
#define BSW_CANIF_SNDREQ_QUE143         (0x8FU)
#define BSW_CANIF_SNDREQ_QUE144         (0x90U)
#define BSW_CANIF_SNDREQ_QUE145         (0x91U)
#define BSW_CANIF_SNDREQ_QUE146         (0x92U)
#define BSW_CANIF_SNDREQ_QUE147         (0x93U)
#define BSW_CANIF_SNDREQ_QUE148         (0x94U)
#define BSW_CANIF_SNDREQ_QUE149         (0x95U)
#define BSW_CANIF_SNDREQ_QUE150         (0x96U)
#define BSW_CANIF_SNDREQ_QUE151         (0x97U)
#define BSW_CANIF_SNDREQ_QUE152         (0x98U)
#define BSW_CANIF_SNDREQ_QUE153         (0x99U)
#define BSW_CANIF_SNDREQ_QUE154         (0x9AU)
#define BSW_CANIF_SNDREQ_QUE155         (0x9BU)
#define BSW_CANIF_SNDREQ_QUE156         (0x9CU)
#define BSW_CANIF_SNDREQ_QUE157         (0x9DU)
#define BSW_CANIF_SNDREQ_QUE158         (0x9EU)
#define BSW_CANIF_SNDREQ_QUE159         (0x9FU)
#define BSW_CANIF_SNDREQ_QUE160         (0xA0U)
#define BSW_CANIF_SNDREQ_QUE161         (0xA1U)
#define BSW_CANIF_SNDREQ_QUE162         (0xA2U)
#define BSW_CANIF_SNDREQ_QUE163         (0xA3U)
#define BSW_CANIF_SNDREQ_QUE164         (0xA4U)
#define BSW_CANIF_SNDREQ_QUE165         (0xA5U)
#define BSW_CANIF_SNDREQ_QUE166         (0xA6U)
#define BSW_CANIF_SNDREQ_QUE167         (0xA7U)
#define BSW_CANIF_SNDREQ_QUE168         (0xA8U)
#define BSW_CANIF_SNDREQ_QUE169         (0xA9U)
#define BSW_CANIF_SNDREQ_QUE170         (0xAAU)
#define BSW_CANIF_SNDREQ_QUE171         (0xABU)
#define BSW_CANIF_SNDREQ_QUE172         (0xACU)
#define BSW_CANIF_SNDREQ_QUE173         (0xADU)
#define BSW_CANIF_SNDREQ_QUE174         (0xAEU)
#define BSW_CANIF_SNDREQ_QUE175         (0xAFU)
#define BSW_CANIF_SNDREQ_QUE176         (0xB0U)
#define BSW_CANIF_SNDREQ_QUE177         (0xB1U)
#define BSW_CANIF_SNDREQ_QUE178         (0xB2U)
#define BSW_CANIF_SNDREQ_QUE179         (0xB3U)
#define BSW_CANIF_SNDREQ_QUE180         (0xB4U)
#define BSW_CANIF_SNDREQ_QUE181         (0xB5U)
#define BSW_CANIF_SNDREQ_QUE182         (0xB6U)
#define BSW_CANIF_SNDREQ_QUE183         (0xB7U)
#define BSW_CANIF_SNDREQ_QUE184         (0xB8U)
#define BSW_CANIF_SNDREQ_QUE185         (0xB9U)
#define BSW_CANIF_SNDREQ_QUE186         (0xBAU)
#define BSW_CANIF_SNDREQ_QUE187         (0xBBU)
#define BSW_CANIF_SNDREQ_QUE188         (0xBCU)
#define BSW_CANIF_SNDREQ_QUE189         (0xBDU)
#define BSW_CANIF_SNDREQ_QUE190         (0xBEU)
#define BSW_CANIF_SNDREQ_QUE191         (0xBFU)
#define BSW_CANIF_SNDREQ_QUE192         (0xC0U)
#define BSW_CANIF_SNDREQ_QUE193         (0xC1U)
#define BSW_CANIF_SNDREQ_QUE194         (0xC2U)
#define BSW_CANIF_SNDREQ_QUE195         (0xC3U)
#define BSW_CANIF_SNDREQ_QUE196         (0xC4U)
#define BSW_CANIF_SNDREQ_QUE197         (0xC5U)
#define BSW_CANIF_SNDREQ_QUE198         (0xC6U)
#define BSW_CANIF_SNDREQ_QUE199         (0xC7U)
#define BSW_CANIF_SNDREQ_QUE200         (0xC8U)
#define BSW_CANIF_SNDREQ_QUE201         (0xC9U)
#define BSW_CANIF_SNDREQ_QUE202         (0xCAU)
#define BSW_CANIF_SNDREQ_QUE203         (0xCBU)
#define BSW_CANIF_SNDREQ_QUE204         (0xCCU)
#define BSW_CANIF_SNDREQ_QUE205         (0xCDU)
#define BSW_CANIF_SNDREQ_QUE206         (0xCEU)
#define BSW_CANIF_SNDREQ_QUE207         (0xCFU)
#define BSW_CANIF_SNDREQ_QUE208         (0xD0U)
#define BSW_CANIF_SNDREQ_QUE209         (0xD1U)
#define BSW_CANIF_SNDREQ_QUE210         (0xD2U)
#define BSW_CANIF_SNDREQ_QUE211         (0xD3U)
#define BSW_CANIF_SNDREQ_QUE212         (0xD4U)
#define BSW_CANIF_SNDREQ_QUE213         (0xD5U)
#define BSW_CANIF_SNDREQ_QUE214         (0xD6U)
#define BSW_CANIF_SNDREQ_QUE215         (0xD7U)
#define BSW_CANIF_SNDREQ_QUE216         (0xD8U)
#define BSW_CANIF_SNDREQ_QUE217         (0xD9U)
#define BSW_CANIF_SNDREQ_QUE218         (0xDAU)
#define BSW_CANIF_SNDREQ_QUE219         (0xDBU)
#define BSW_CANIF_SNDREQ_QUE220         (0xDCU)
#define BSW_CANIF_SNDREQ_QUE221         (0xDDU)
#define BSW_CANIF_SNDREQ_QUE222         (0xDEU)
#define BSW_CANIF_SNDREQ_QUE223         (0xDFU)
#define BSW_CANIF_SNDREQ_QUE224         (0xE0U)
#define BSW_CANIF_SNDREQ_QUE225         (0xE1U)
#define BSW_CANIF_SNDREQ_QUE226         (0xE2U)
#define BSW_CANIF_SNDREQ_QUE227         (0xE3U)
#define BSW_CANIF_SNDREQ_QUE228         (0xE4U)
#define BSW_CANIF_SNDREQ_QUE229         (0xE5U)
#define BSW_CANIF_SNDREQ_QUE230         (0xE6U)
#define BSW_CANIF_SNDREQ_QUE231         (0xE7U)
#define BSW_CANIF_SNDREQ_QUE232         (0xE8U)
#define BSW_CANIF_SNDREQ_QUE233         (0xE9U)
#define BSW_CANIF_SNDREQ_QUE234         (0xEAU)
#define BSW_CANIF_SNDREQ_QUE235         (0xEBU)
#define BSW_CANIF_SNDREQ_QUE236         (0xECU)
#define BSW_CANIF_SNDREQ_QUE237         (0xEDU)
#define BSW_CANIF_SNDREQ_QUE238         (0xEEU)
#define BSW_CANIF_SNDREQ_QUE239         (0xEFU)
#define BSW_CANIF_SNDREQ_QUE240         (0xF0U)
#define BSW_CANIF_SNDREQ_QUE241         (0xF1U)
#define BSW_CANIF_SNDREQ_QUE242         (0xF2U)
#define BSW_CANIF_SNDREQ_QUE243         (0xF3U)
#define BSW_CANIF_SNDREQ_QUE244         (0xF4U)
#define BSW_CANIF_SNDREQ_QUE245         (0xF5U)
#define BSW_CANIF_SNDREQ_QUE246         (0xF6U)
#define BSW_CANIF_SNDREQ_QUE247         (0xF7U)
#define BSW_CANIF_SNDREQ_QUE248         (0xF8U)
#define BSW_CANIF_SNDREQ_QUE249         (0xF9U)

/* Configuration Value */
#define BSW_CANIF_CH0                   (0U)
#define BSW_CANIF_CH1                   (1U)
#define BSW_CANIF_CH2                   (2U)
#define BSW_CANIF_CH3                   (3U)
#define BSW_CANIF_CH4                   (4U)
#define BSW_CANIF_CH5                   (5U)
#define BSW_CANIF_CH6                   (6U)
#define BSW_CANIF_CH7                   (7U)
#define BSW_CANIF_CH8                   (8U)
#define BSW_CANIF_CH9                   (9U)
#define BSW_CANIF_CH10                  (10U)
#define BSW_CANIF_CH11                  (11U)
#define BSW_CANIF_CH12                  (12U)
#define BSW_CANIF_CH13                  (13U)
#define BSW_CANIF_CH14                  (14U)
#define BSW_CANIF_CH15                  (15U)
#define BSW_CANIF_CH16                  (16U)
#define BSW_CANIF_CH17                  (17U)
#define BSW_CANIF_CH18                  (18U)
#define BSW_CANIF_CH19                  (19U)
#define BSW_CANIF_CH20                  (20U)
#define BSW_CANIF_CH21                  (21U)
#define BSW_CANIF_CH22                  (22U)
#define BSW_CANIF_CH23                  (23U)
#define BSW_CANIF_CH24                  (24U)
#define BSW_CANIF_CH25                  (25U)
#define BSW_CANIF_CH26                  (26U)
#define BSW_CANIF_CH27                  (27U)
#define BSW_CANIF_CH28                  (28U)
#define BSW_CANIF_CH29                  (29U)
#define BSW_CANIF_CH30                  (30U)
#define BSW_CANIF_CH31                  (31U)
#define BSW_CANIF_USE                   (0x00U)
#define BSW_CANIF_NOUSE                 (0xFFU)
#define BSW_CANIF_NONE                  (0U)
#define BSW_CANIF_EXIST                 (1U)
#define BSW_CANIF_DISABLE               (0U)
#define BSW_CANIF_ENABLE                (1U)
#define BSW_CANIF_INTR                  (0U)
#define BSW_CANIF_POLL                  (1U)
#define BSW_CANIF_CHKSUM_PTN0           (0x00U)
#define BSW_CANIF_CHKSUM_PTN1           (0x01U)
#define BSW_CANIF_CHKSUM_PTN2           (0x02U)
#define BSW_CANIF_CHKSUM_PTN3           (0x03U)
#define BSW_CANIF_CHKSUM_NONE           (0xFFU)
#define BSW_CANIF_DLCCHK_PTN0           (0x00U)
#define BSW_CANIF_DLCCHK_PTN1           (0x01U)
#define BSW_CANIF_DLCCHK_NONE           (0xFFU)
#define BSW_CANIF_PROTOCOL_STD_CAN      (0x00U)
#define BSW_CANIF_PROTOCOL_EXT_CAN_A    (0x01U)
#define BSW_CANIF_PROTOCOL_EXT_CAN_A1   (0x02U)
#define BSW_CANIF_PROTOCOL_EXT_CAN_A2   (0x04U)
#define BSW_CANIF_PROTOCOL_EXT_CAN_B    (0x08U)
#define BSW_CANIF_PROTOCOL_EXT_CAN_E    (0x10U)
#define BSW_CANIF_PROTOCOL_NOUSE        (0xFFU)
#define BSW_CANIF_HOH_NOUSE             (0xFFFFU)
#define BSW_CANIF_HTH_IDX_NOUSE         (0xFFU)
#define BSW_CANIF_MASK_CH_MODULE        (0x00U)
#define BSW_CANIF_MASK_RXMSG            (0x01U)

/* CAN Controller Mode */
#define BSW_CANIF_CS_UNINIT             (0U)
#define BSW_CANIF_CS_SLEEP              (1U)
#define BSW_CANIF_CS_STARTED            (2U)
#define BSW_CANIF_CS_STOPPED            (3U)

/* Vendor ID */
#define BSW_CANIF_VENDOR_ID             (83U)

/* Module ID */
#define BSW_CANIF_MODULE_ID             (60U)

/* AUTOSAR Release Version */
#define BSW_CANIF_AR_RELEASE_MAJOR_VERSION      (4U)
#define BSW_CANIF_AR_RELEASE_MINOR_VERSION      (5U)
#define BSW_CANIF_AR_RELEASE_REVISION_VERSION   (0U)

/* Vendor Specification Version */
#define BSW_CANIF_SW_MAJOR_VERSION      (4U)
#define BSW_CANIF_SW_MINOR_VERSION      (5U)
#define BSW_CANIF_SW_PATCH_VERSION      (0U)

#define BSW_CANTRCV_TRCVMODE_NORMAL     (0U)
#define BSW_CANTRCV_TRCVMODE_SLEEP      (1U)
#define BSW_CANTRCV_TRCVMODE_STANDBY    (2U)

#define BSW_CANTRCV_WUMODE_ENABLE       (0U)
#define BSW_CANTRCV_WUMODE_DISABLE      (1U)
#define BSW_CANTRCV_WUMODE_CLEAR        (2U)

#define BSW_CANTRCV_WU_ERROR            (0U)
#define BSW_CANTRCV_WU_NOT_SUPPORTED    (1U)
#define BSW_CANTRCV_WU_BY_BUS           (2U)
#define BSW_CANTRCV_WU_INTERNALLY       (3U)
#define BSW_CANTRCV_WU_RESET            (4U)
#define BSW_CANTRCV_WU_POWER_ON         (5U)
#define BSW_CANTRCV_WU_BY_PIN           (6U)
#define BSW_CANTRCV_WU_BY_SYSERR        (7U)

/* Switching Channel Attribute */
#define BSW_CANIF_SW_CHATT_PHYSICAL     (0U)
#define BSW_CANIF_SW_CHATT_VIRTUAL      (1U)

/* Controller ID identifier */
#define BSW_CANIF_CTRLID_PHYSICAL       (0x00U)
#define BSW_CANIF_CTRLID_VIRTUAL        (0x80U)

/* HOH identifier */
#define BSW_CANIF_HOH_PHYSICAL          (0x0000U)
#define BSW_CANIF_HOH_VIRTUAL           (0x8000U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8       Bsw_CanIf_ConfigType;
typedef uint8       Bsw_CanIf_PduModeType;
typedef uint8       Bsw_CanIf_NotifStatusType;
typedef uint8       Bsw_CanIf_ControllerModeType;

typedef struct
{
    uint32          CanId;
    PduIdType       PduId;
    uint8           Component;
    uint8           SduLength;
    uint8           *SduDataPtr;
} Bsw_CanIf_PduType;

typedef struct
{
    uint32          CanId;
    PduIdType       PduId;
    uint8           Component;
    uint8           SduLength;
    BswConstR uint8 *SduDataPtr;
} Bsw_CanIf_RxPduType;

typedef struct
{
    Can_IdType              CanId;
    Can_HwHandleType        Hoh;
    uint8                   ControllerId;
}Bsw_CanIf_HwType;

typedef uint8 Bsw_CanTrcv_TrcvModeType;
typedef uint8 Bsw_CanTrcv_TrcvWakeupModeType;
typedef uint8 Bsw_CanTrcv_TrcvWakeupReasonType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                      bsw_canif_st_Init( BswConst Bsw_CanIf_ConfigType* ConfigPtr );
Std_ReturnType            bsw_canif_st_SetControllerMode( uint8 ControllerId, Bsw_CanIf_ControllerModeType ControllerMode );
Std_ReturnType            bsw_canif_st_GetControllerMode( uint8 ControllerId, Bsw_CanIf_ControllerModeType * ControllerMode );
Std_ReturnType            bsw_canif_st_CheckStpCompletion ( uint8 ControllerId );
Std_ReturnType            bsw_canif_tx_TransmitFrame( uint8 ControllerId, uint16 SndReq, BswConstR Bsw_CanIf_PduType* PduPtr );
Std_ReturnType            bsw_canif_tx_CancelTxFrame( uint8 ControllerId, uint16 SndReq );
Std_ReturnType            bsw_canif_tx_Transmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType            bsw_canif_tx_CancelTransmit( PduIdType TxPduId );
Std_ReturnType            bsw_canif_rx_ReadRxPduData( PduIdType CanIfRxSduId, PduInfoType* CanIfRxInfoPtr );
Bsw_CanIf_NotifStatusType bsw_canif_tx_ReadTxNotifStatus( PduIdType CanIfTxSduId );
Bsw_CanIf_NotifStatusType bsw_canif_rx_ReadRxNotifStatus( PduIdType CanIfRxSduId );
Std_ReturnType            bsw_canif_st_SetPduMode( uint8 ControllerId, Bsw_CanIf_PduModeType PduModeRequest );
Std_ReturnType            bsw_canif_st_GetPduMode( uint8 ControllerId, Bsw_CanIf_PduModeType * PduModePtr );
void                      bsw_canif_st_GetVersionInfo( Std_VersionInfoType* VersionInfo );
void                      bsw_canif_tx_SetDynamicTxId( PduIdType CanIfTxSduId, Can_IdType CanId );
Std_ReturnType            bsw_canif_st_SetTrcvMode( uint8 TransceiverId, Bsw_CanTrcv_TrcvModeType TransceiverMode );
Std_ReturnType            bsw_canif_st_GetTrcvMode( Bsw_CanTrcv_TrcvModeType* TransceiverModePtr, uint8 TransceiverId );
Std_ReturnType            bsw_canif_st_GetTrcvWkupReason( uint8 TransceiverId, Bsw_CanTrcv_TrcvWakeupReasonType* TrcvWuReasonPtr );
Std_ReturnType            bsw_canif_edge_SetTrcvWkupMode( uint8 TransceiverId, Bsw_CanTrcv_TrcvWakeupModeType TrcvWakeupMode );
Std_ReturnType            bsw_canif_st_ClearTrcvWufFlag( uint8 TransceiverId );
Std_ReturnType            bsw_canif_edge_CheckWakeup( uint32 WakeupSource );
Bsw_CanIf_NotifStatusType bsw_canif_tx_GetTxCfmState( uint8 ControllerId );
Bsw_CanIf_NotifStatusType bsw_canif_rx_GetRxIndState( uint8 ControllerId );
Std_ReturnType            bsw_canif_st_CheckBaudrate( uint8 ControllerId, uint16 Baudrate );
Std_ReturnType            bsw_canif_st_ChangeBaudrate( uint8 ControllerId, uint16 Baudrate);
Std_ReturnType            bsw_canif_st_SetBaudrate( uint8 ControllerId, uint16 BaudRateConfigID );
Std_ReturnType            bsw_canif_st_InitDriver( uint8 ControllerId, boolean u1RegChk );
Std_ReturnType            bsw_canif_tx_TriggerTransmit( PduIdType TxPduId, PduInfoType* PduInfoPtr );
uint8                     bsw_canif_rx_GetControllerId( PduIdType CanRxPduId );
uint8                     bsw_canif_tx_GetControllerId( PduIdType CanTxPduId );
uint32                    bsw_canif_tx_GetTxCanId( PduIdType PduId );
void                      bsw_canif_tx_GetConfirmedPdu( PduIdType TxPduId, PduInfoType* PduInfoPtr );
uint32                    bsw_canif_rx_GetCurrentRxCanId( PduIdType PduId );
void                      bsw_canif_st_Reset( uint8 ControllerId );
void                      bsw_canif_st_Shutdown( void );
Std_ReturnType            bsw_canif_tx_ClearTransmitReq( PduIdType TxPduId );
void                      bsw_canif_fs_EnableRcvLock( uint8 ControllerId );
void                      bsw_canif_fs_DisableRcvLock( uint8 ControllerId );
uint8                     bsw_canif_fs_GetControllerError( uint8 ControllerId );
void                      bsw_canif_tx_MainFuncTx( void );
void                      bsw_canif_rx_MainFunctionRx( void );
void                      bsw_canif_st_MainFunction( void );
void                      bsw_canif_fs_CheckRam( void );
uint16                    bsw_canif_fs_GetStatus( uint8 ControllerId );
void                      bsw_canif_edge_EdgeInit( uint8 ControllerId );
void                      bsw_canif_edge_EdgeClearStatus( uint8 ControllerId );
void                      bsw_canif_edge_EdgeEnableDtct( uint8 ControllerId );
void                      bsw_canif_edge_EdgeDisableDtct( uint8 ControllerId );
uint8                     bsw_canif_edge_EdgeGetStatus( uint8 ControllerId );
Std_ReturnType            bsw_canif_tx_CbkPreTxMsg( PduIdType CanTxPduId, Bsw_CanIf_PduType *TxMsg );
Std_ReturnType            bsw_canif_tx_CbkPreTxFrame( PduIdType CanTxPduId, Bsw_CanIf_PduType *TxMsg );
Std_ReturnType            bsw_canif_rx_CbkPreRxMsg( PduIdType CanRxPduId, BswConstR Bsw_CanIf_PduType *RxMsg );
Std_ReturnType            bsw_canif_rx_CbkPreRxFrame( PduIdType CanRxPduId, BswConstR Bsw_CanIf_PduType *RxMsg );
void                      bsw_canif_fs_CbkLengthErr( PduIdType RxPduId );
void                      bsw_canif_fs_CbkSumErr( PduIdType RxPduId );
void                      bsw_canif_fs_CbkDtctMsgChkCrrct( PduIdType RxPduId );
void                      bsw_canif_fs_CbkTpLengthErr( PduIdType RxPduId );
Std_ReturnType            bsw_canif_rx_CbkPreStoreMsg( BswConstR Bsw_CanIf_HwType* MailBox, uint8 CanDlc, BswConstR uint8 CanSduPtr[] );
uint32                    bsw_canif_rx_GetRxCanId( PduIdType PduId );
Std_ReturnType            bsw_canif_tx_TransmitDirect( BswConstR Bsw_CanIf_HwType* MailBox, uint8 CanDlc, BswConstR uint8 CanSduPtr[] );
void                      bsw_canif_tx_CbkTxConfirmation( uint8 ControllerId, Can_HwHandleType Hth );
uint8                     bsw_canif_st_GetState( uint8 ControllerId );
void                      bsw_canif_fs_NmTxToutException( uint8 ControllerId, uint8 NmTxTimeoutKind );
void                      bsw_canif_fs_ClrNmTxToutUnSt( uint8 ControllerId );
uint8                     bsw_canif_fs_CbkChkStuckReg( uint8 CanControllerId );
void                      bsw_canif_tx_MainFuncTxFail( void );
void                      bsw_canif_st_CbkSetPduMode( uint8 ControllerId, Bsw_CanIf_PduModeType PduModeRequest );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANIF_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/12/12                                             */
/*  v3-0-0          :2024/10/03                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
