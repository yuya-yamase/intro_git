/* canif_h_v2-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANIF/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANIF_AR_H
#define     BSW_CANIF_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

#include <PduR_CanIf.h>
#include <Can.h>
#include <ComStack_Types.h>
#include <Can_GeneralTypes.h>
#include <canif/bsw_canif_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CANIF_BUSY                      (BSW_CANIF_BUSY)

#define CANIF_OFFLINE                   (BSW_CANIF_OFFLINE)
#define CANIF_TX_OFFLINE                (BSW_CANIF_TX_OFFLINE)
#define CANIF_TX_OFFLINE_ACTIVE         (BSW_CANIF_TX_OFFLINE_ACTIVE)
#define CANIF_ONLINE                    (BSW_CANIF_ONLINE)

#define CANIF_NO_NOTIFICATION           (BSW_CANIF_NO_NOTIFICATION)
#define CANIF_TX_RX_NOTIFICATION        (BSW_CANIF_TX_RX_NOTIFICATION)

#define CANIF_STATUS_ERROR_ACTIVE       (BSW_CANIF_STATUS_ERROR_ACTIVE)
#define CANIF_STATUS_ERROR_PASSIVE      (BSW_CANIF_STATUS_ERROR_PASSIVE)
#define CANIF_STATUS_BUSOFF             (BSW_CANIF_STATUS_BUSOFF)
#define CANIF_STATUS_INVALID            (BSW_CANIF_STATUS_INVALID)

#define CANIF_CONTROLLER_INVALID        (BSW_CANIF_CONTROLLER_INVALID)
#define CANIF_CANID_INVALID             (BSW_CANIF_CANID_INVALID)

#define CANIF_COMP_BIT_PDUR             (BSW_CANIF_COMP_BIT_PDUR)
#define CANIF_COMP_BIT_CANNM            (BSW_CANIF_COMP_BIT_CANNM)
#define CANIF_COMP_BIT_CANTP            (BSW_CANIF_COMP_BIT_CANTP)
#define CANIF_COMP_BIT_CDD1             (BSW_CANIF_COMP_BIT_CDD1)
#define CANIF_COMP_BIT_CDD2             (BSW_CANIF_COMP_BIT_CDD2)
#define CANIF_COMP_BIT_XCP              (BSW_CANIF_COMP_BIT_XCP)
#define CANIF_COMP_BIT_NONE             (BSW_CANIF_COMP_BIT_NONE)

#define CANIF_SNDREQ_PDUR               (BSW_CANIF_SNDREQ_PDUR)
#define CANIF_SNDREQ_CANNM              (BSW_CANIF_SNDREQ_CANNM)
#define CANIF_SNDREQ_CANTP              (BSW_CANIF_SNDREQ_CANTP)
#define CANIF_SNDREQ_CDD1               (BSW_CANIF_SNDREQ_CDD1)
#define CANIF_SNDREQ_CDD2               (BSW_CANIF_SNDREQ_CDD2)
#define CANIF_SNDREQ_XCP                (BSW_CANIF_SNDREQ_XCP)

#define CANIF_SNDREQ_QUE000             (BSW_CANIF_SNDREQ_QUE000)
#define CANIF_SNDREQ_QUE001             (BSW_CANIF_SNDREQ_QUE001)
#define CANIF_SNDREQ_QUE002             (BSW_CANIF_SNDREQ_QUE002)
#define CANIF_SNDREQ_QUE003             (BSW_CANIF_SNDREQ_QUE003)
#define CANIF_SNDREQ_QUE004             (BSW_CANIF_SNDREQ_QUE004)
#define CANIF_SNDREQ_QUE005             (BSW_CANIF_SNDREQ_QUE005)
#define CANIF_SNDREQ_QUE006             (BSW_CANIF_SNDREQ_QUE006)
#define CANIF_SNDREQ_QUE007             (BSW_CANIF_SNDREQ_QUE007)
#define CANIF_SNDREQ_QUE008             (BSW_CANIF_SNDREQ_QUE008)
#define CANIF_SNDREQ_QUE009             (BSW_CANIF_SNDREQ_QUE009)
#define CANIF_SNDREQ_QUE010             (BSW_CANIF_SNDREQ_QUE010)
#define CANIF_SNDREQ_QUE011             (BSW_CANIF_SNDREQ_QUE011)
#define CANIF_SNDREQ_QUE012             (BSW_CANIF_SNDREQ_QUE012)
#define CANIF_SNDREQ_QUE013             (BSW_CANIF_SNDREQ_QUE013)
#define CANIF_SNDREQ_QUE014             (BSW_CANIF_SNDREQ_QUE014)
#define CANIF_SNDREQ_QUE015             (BSW_CANIF_SNDREQ_QUE015)
#define CANIF_SNDREQ_QUE016             (BSW_CANIF_SNDREQ_QUE016)
#define CANIF_SNDREQ_QUE017             (BSW_CANIF_SNDREQ_QUE017)
#define CANIF_SNDREQ_QUE018             (BSW_CANIF_SNDREQ_QUE018)
#define CANIF_SNDREQ_QUE019             (BSW_CANIF_SNDREQ_QUE019)
#define CANIF_SNDREQ_QUE020             (BSW_CANIF_SNDREQ_QUE020)
#define CANIF_SNDREQ_QUE021             (BSW_CANIF_SNDREQ_QUE021)
#define CANIF_SNDREQ_QUE022             (BSW_CANIF_SNDREQ_QUE022)
#define CANIF_SNDREQ_QUE023             (BSW_CANIF_SNDREQ_QUE023)
#define CANIF_SNDREQ_QUE024             (BSW_CANIF_SNDREQ_QUE024)
#define CANIF_SNDREQ_QUE025             (BSW_CANIF_SNDREQ_QUE025)
#define CANIF_SNDREQ_QUE026             (BSW_CANIF_SNDREQ_QUE026)
#define CANIF_SNDREQ_QUE027             (BSW_CANIF_SNDREQ_QUE027)
#define CANIF_SNDREQ_QUE028             (BSW_CANIF_SNDREQ_QUE028)
#define CANIF_SNDREQ_QUE029             (BSW_CANIF_SNDREQ_QUE029)
#define CANIF_SNDREQ_QUE030             (BSW_CANIF_SNDREQ_QUE030)
#define CANIF_SNDREQ_QUE031             (BSW_CANIF_SNDREQ_QUE031)
#define CANIF_SNDREQ_QUE032             (BSW_CANIF_SNDREQ_QUE032)
#define CANIF_SNDREQ_QUE033             (BSW_CANIF_SNDREQ_QUE033)
#define CANIF_SNDREQ_QUE034             (BSW_CANIF_SNDREQ_QUE034)
#define CANIF_SNDREQ_QUE035             (BSW_CANIF_SNDREQ_QUE035)
#define CANIF_SNDREQ_QUE036             (BSW_CANIF_SNDREQ_QUE036)
#define CANIF_SNDREQ_QUE037             (BSW_CANIF_SNDREQ_QUE037)
#define CANIF_SNDREQ_QUE038             (BSW_CANIF_SNDREQ_QUE038)
#define CANIF_SNDREQ_QUE039             (BSW_CANIF_SNDREQ_QUE039)
#define CANIF_SNDREQ_QUE040             (BSW_CANIF_SNDREQ_QUE040)
#define CANIF_SNDREQ_QUE041             (BSW_CANIF_SNDREQ_QUE041)
#define CANIF_SNDREQ_QUE042             (BSW_CANIF_SNDREQ_QUE042)
#define CANIF_SNDREQ_QUE043             (BSW_CANIF_SNDREQ_QUE043)
#define CANIF_SNDREQ_QUE044             (BSW_CANIF_SNDREQ_QUE044)
#define CANIF_SNDREQ_QUE045             (BSW_CANIF_SNDREQ_QUE045)
#define CANIF_SNDREQ_QUE046             (BSW_CANIF_SNDREQ_QUE046)
#define CANIF_SNDREQ_QUE047             (BSW_CANIF_SNDREQ_QUE047)
#define CANIF_SNDREQ_QUE048             (BSW_CANIF_SNDREQ_QUE048)
#define CANIF_SNDREQ_QUE049             (BSW_CANIF_SNDREQ_QUE049)
#define CANIF_SNDREQ_QUE050             (BSW_CANIF_SNDREQ_QUE050)
#define CANIF_SNDREQ_QUE051             (BSW_CANIF_SNDREQ_QUE051)
#define CANIF_SNDREQ_QUE052             (BSW_CANIF_SNDREQ_QUE052)
#define CANIF_SNDREQ_QUE053             (BSW_CANIF_SNDREQ_QUE053)
#define CANIF_SNDREQ_QUE054             (BSW_CANIF_SNDREQ_QUE054)
#define CANIF_SNDREQ_QUE055             (BSW_CANIF_SNDREQ_QUE055)
#define CANIF_SNDREQ_QUE056             (BSW_CANIF_SNDREQ_QUE056)
#define CANIF_SNDREQ_QUE057             (BSW_CANIF_SNDREQ_QUE057)
#define CANIF_SNDREQ_QUE058             (BSW_CANIF_SNDREQ_QUE058)
#define CANIF_SNDREQ_QUE059             (BSW_CANIF_SNDREQ_QUE059)
#define CANIF_SNDREQ_QUE060             (BSW_CANIF_SNDREQ_QUE060)
#define CANIF_SNDREQ_QUE061             (BSW_CANIF_SNDREQ_QUE061)
#define CANIF_SNDREQ_QUE062             (BSW_CANIF_SNDREQ_QUE062)
#define CANIF_SNDREQ_QUE063             (BSW_CANIF_SNDREQ_QUE063)
#define CANIF_SNDREQ_QUE064             (BSW_CANIF_SNDREQ_QUE064)
#define CANIF_SNDREQ_QUE065             (BSW_CANIF_SNDREQ_QUE065)
#define CANIF_SNDREQ_QUE066             (BSW_CANIF_SNDREQ_QUE066)
#define CANIF_SNDREQ_QUE067             (BSW_CANIF_SNDREQ_QUE067)
#define CANIF_SNDREQ_QUE068             (BSW_CANIF_SNDREQ_QUE068)
#define CANIF_SNDREQ_QUE069             (BSW_CANIF_SNDREQ_QUE069)
#define CANIF_SNDREQ_QUE070             (BSW_CANIF_SNDREQ_QUE070)
#define CANIF_SNDREQ_QUE071             (BSW_CANIF_SNDREQ_QUE071)
#define CANIF_SNDREQ_QUE072             (BSW_CANIF_SNDREQ_QUE072)
#define CANIF_SNDREQ_QUE073             (BSW_CANIF_SNDREQ_QUE073)
#define CANIF_SNDREQ_QUE074             (BSW_CANIF_SNDREQ_QUE074)
#define CANIF_SNDREQ_QUE075             (BSW_CANIF_SNDREQ_QUE075)
#define CANIF_SNDREQ_QUE076             (BSW_CANIF_SNDREQ_QUE076)
#define CANIF_SNDREQ_QUE077             (BSW_CANIF_SNDREQ_QUE077)
#define CANIF_SNDREQ_QUE078             (BSW_CANIF_SNDREQ_QUE078)
#define CANIF_SNDREQ_QUE079             (BSW_CANIF_SNDREQ_QUE079)
#define CANIF_SNDREQ_QUE080             (BSW_CANIF_SNDREQ_QUE080)
#define CANIF_SNDREQ_QUE081             (BSW_CANIF_SNDREQ_QUE081)
#define CANIF_SNDREQ_QUE082             (BSW_CANIF_SNDREQ_QUE082)
#define CANIF_SNDREQ_QUE083             (BSW_CANIF_SNDREQ_QUE083)
#define CANIF_SNDREQ_QUE084             (BSW_CANIF_SNDREQ_QUE084)
#define CANIF_SNDREQ_QUE085             (BSW_CANIF_SNDREQ_QUE085)
#define CANIF_SNDREQ_QUE086             (BSW_CANIF_SNDREQ_QUE086)
#define CANIF_SNDREQ_QUE087             (BSW_CANIF_SNDREQ_QUE087)
#define CANIF_SNDREQ_QUE088             (BSW_CANIF_SNDREQ_QUE088)
#define CANIF_SNDREQ_QUE089             (BSW_CANIF_SNDREQ_QUE089)
#define CANIF_SNDREQ_QUE090             (BSW_CANIF_SNDREQ_QUE090)
#define CANIF_SNDREQ_QUE091             (BSW_CANIF_SNDREQ_QUE091)
#define CANIF_SNDREQ_QUE092             (BSW_CANIF_SNDREQ_QUE092)
#define CANIF_SNDREQ_QUE093             (BSW_CANIF_SNDREQ_QUE093)
#define CANIF_SNDREQ_QUE094             (BSW_CANIF_SNDREQ_QUE094)
#define CANIF_SNDREQ_QUE095             (BSW_CANIF_SNDREQ_QUE095)
#define CANIF_SNDREQ_QUE096             (BSW_CANIF_SNDREQ_QUE096)
#define CANIF_SNDREQ_QUE097             (BSW_CANIF_SNDREQ_QUE097)
#define CANIF_SNDREQ_QUE098             (BSW_CANIF_SNDREQ_QUE098)
#define CANIF_SNDREQ_QUE099             (BSW_CANIF_SNDREQ_QUE099)
#define CANIF_SNDREQ_QUE100             (BSW_CANIF_SNDREQ_QUE100)
#define CANIF_SNDREQ_QUE101             (BSW_CANIF_SNDREQ_QUE101)
#define CANIF_SNDREQ_QUE102             (BSW_CANIF_SNDREQ_QUE102)
#define CANIF_SNDREQ_QUE103             (BSW_CANIF_SNDREQ_QUE103)
#define CANIF_SNDREQ_QUE104             (BSW_CANIF_SNDREQ_QUE104)
#define CANIF_SNDREQ_QUE105             (BSW_CANIF_SNDREQ_QUE105)
#define CANIF_SNDREQ_QUE106             (BSW_CANIF_SNDREQ_QUE106)
#define CANIF_SNDREQ_QUE107             (BSW_CANIF_SNDREQ_QUE107)
#define CANIF_SNDREQ_QUE108             (BSW_CANIF_SNDREQ_QUE108)
#define CANIF_SNDREQ_QUE109             (BSW_CANIF_SNDREQ_QUE109)
#define CANIF_SNDREQ_QUE110             (BSW_CANIF_SNDREQ_QUE110)
#define CANIF_SNDREQ_QUE111             (BSW_CANIF_SNDREQ_QUE111)
#define CANIF_SNDREQ_QUE112             (BSW_CANIF_SNDREQ_QUE112)
#define CANIF_SNDREQ_QUE113             (BSW_CANIF_SNDREQ_QUE113)
#define CANIF_SNDREQ_QUE114             (BSW_CANIF_SNDREQ_QUE114)
#define CANIF_SNDREQ_QUE115             (BSW_CANIF_SNDREQ_QUE115)
#define CANIF_SNDREQ_QUE116             (BSW_CANIF_SNDREQ_QUE116)
#define CANIF_SNDREQ_QUE117             (BSW_CANIF_SNDREQ_QUE117)
#define CANIF_SNDREQ_QUE118             (BSW_CANIF_SNDREQ_QUE118)
#define CANIF_SNDREQ_QUE119             (BSW_CANIF_SNDREQ_QUE119)
#define CANIF_SNDREQ_QUE120             (BSW_CANIF_SNDREQ_QUE120)
#define CANIF_SNDREQ_QUE121             (BSW_CANIF_SNDREQ_QUE121)
#define CANIF_SNDREQ_QUE122             (BSW_CANIF_SNDREQ_QUE122)
#define CANIF_SNDREQ_QUE123             (BSW_CANIF_SNDREQ_QUE123)
#define CANIF_SNDREQ_QUE124             (BSW_CANIF_SNDREQ_QUE124)
#define CANIF_SNDREQ_QUE125             (BSW_CANIF_SNDREQ_QUE125)
#define CANIF_SNDREQ_QUE126             (BSW_CANIF_SNDREQ_QUE126)
#define CANIF_SNDREQ_QUE127             (BSW_CANIF_SNDREQ_QUE127)
#define CANIF_SNDREQ_QUE128             (BSW_CANIF_SNDREQ_QUE128)
#define CANIF_SNDREQ_QUE129             (BSW_CANIF_SNDREQ_QUE129)
#define CANIF_SNDREQ_QUE130             (BSW_CANIF_SNDREQ_QUE130)
#define CANIF_SNDREQ_QUE131             (BSW_CANIF_SNDREQ_QUE131)
#define CANIF_SNDREQ_QUE132             (BSW_CANIF_SNDREQ_QUE132)
#define CANIF_SNDREQ_QUE133             (BSW_CANIF_SNDREQ_QUE133)
#define CANIF_SNDREQ_QUE134             (BSW_CANIF_SNDREQ_QUE134)
#define CANIF_SNDREQ_QUE135             (BSW_CANIF_SNDREQ_QUE135)
#define CANIF_SNDREQ_QUE136             (BSW_CANIF_SNDREQ_QUE136)
#define CANIF_SNDREQ_QUE137             (BSW_CANIF_SNDREQ_QUE137)
#define CANIF_SNDREQ_QUE138             (BSW_CANIF_SNDREQ_QUE138)
#define CANIF_SNDREQ_QUE139             (BSW_CANIF_SNDREQ_QUE139)
#define CANIF_SNDREQ_QUE140             (BSW_CANIF_SNDREQ_QUE140)
#define CANIF_SNDREQ_QUE141             (BSW_CANIF_SNDREQ_QUE141)
#define CANIF_SNDREQ_QUE142             (BSW_CANIF_SNDREQ_QUE142)
#define CANIF_SNDREQ_QUE143             (BSW_CANIF_SNDREQ_QUE143)
#define CANIF_SNDREQ_QUE144             (BSW_CANIF_SNDREQ_QUE144)
#define CANIF_SNDREQ_QUE145             (BSW_CANIF_SNDREQ_QUE145)
#define CANIF_SNDREQ_QUE146             (BSW_CANIF_SNDREQ_QUE146)
#define CANIF_SNDREQ_QUE147             (BSW_CANIF_SNDREQ_QUE147)
#define CANIF_SNDREQ_QUE148             (BSW_CANIF_SNDREQ_QUE148)
#define CANIF_SNDREQ_QUE149             (BSW_CANIF_SNDREQ_QUE149)
#define CANIF_SNDREQ_QUE150             (BSW_CANIF_SNDREQ_QUE150)
#define CANIF_SNDREQ_QUE151             (BSW_CANIF_SNDREQ_QUE151)
#define CANIF_SNDREQ_QUE152             (BSW_CANIF_SNDREQ_QUE152)
#define CANIF_SNDREQ_QUE153             (BSW_CANIF_SNDREQ_QUE153)
#define CANIF_SNDREQ_QUE154             (BSW_CANIF_SNDREQ_QUE154)
#define CANIF_SNDREQ_QUE155             (BSW_CANIF_SNDREQ_QUE155)
#define CANIF_SNDREQ_QUE156             (BSW_CANIF_SNDREQ_QUE156)
#define CANIF_SNDREQ_QUE157             (BSW_CANIF_SNDREQ_QUE157)
#define CANIF_SNDREQ_QUE158             (BSW_CANIF_SNDREQ_QUE158)
#define CANIF_SNDREQ_QUE159             (BSW_CANIF_SNDREQ_QUE159)
#define CANIF_SNDREQ_QUE160             (BSW_CANIF_SNDREQ_QUE160)
#define CANIF_SNDREQ_QUE161             (BSW_CANIF_SNDREQ_QUE161)
#define CANIF_SNDREQ_QUE162             (BSW_CANIF_SNDREQ_QUE162)
#define CANIF_SNDREQ_QUE163             (BSW_CANIF_SNDREQ_QUE163)
#define CANIF_SNDREQ_QUE164             (BSW_CANIF_SNDREQ_QUE164)
#define CANIF_SNDREQ_QUE165             (BSW_CANIF_SNDREQ_QUE165)
#define CANIF_SNDREQ_QUE166             (BSW_CANIF_SNDREQ_QUE166)
#define CANIF_SNDREQ_QUE167             (BSW_CANIF_SNDREQ_QUE167)
#define CANIF_SNDREQ_QUE168             (BSW_CANIF_SNDREQ_QUE168)
#define CANIF_SNDREQ_QUE169             (BSW_CANIF_SNDREQ_QUE169)
#define CANIF_SNDREQ_QUE170             (BSW_CANIF_SNDREQ_QUE170)
#define CANIF_SNDREQ_QUE171             (BSW_CANIF_SNDREQ_QUE171)
#define CANIF_SNDREQ_QUE172             (BSW_CANIF_SNDREQ_QUE172)
#define CANIF_SNDREQ_QUE173             (BSW_CANIF_SNDREQ_QUE173)
#define CANIF_SNDREQ_QUE174             (BSW_CANIF_SNDREQ_QUE174)
#define CANIF_SNDREQ_QUE175             (BSW_CANIF_SNDREQ_QUE175)
#define CANIF_SNDREQ_QUE176             (BSW_CANIF_SNDREQ_QUE176)
#define CANIF_SNDREQ_QUE177             (BSW_CANIF_SNDREQ_QUE177)
#define CANIF_SNDREQ_QUE178             (BSW_CANIF_SNDREQ_QUE178)
#define CANIF_SNDREQ_QUE179             (BSW_CANIF_SNDREQ_QUE179)
#define CANIF_SNDREQ_QUE180             (BSW_CANIF_SNDREQ_QUE180)
#define CANIF_SNDREQ_QUE181             (BSW_CANIF_SNDREQ_QUE181)
#define CANIF_SNDREQ_QUE182             (BSW_CANIF_SNDREQ_QUE182)
#define CANIF_SNDREQ_QUE183             (BSW_CANIF_SNDREQ_QUE183)
#define CANIF_SNDREQ_QUE184             (BSW_CANIF_SNDREQ_QUE184)
#define CANIF_SNDREQ_QUE185             (BSW_CANIF_SNDREQ_QUE185)
#define CANIF_SNDREQ_QUE186             (BSW_CANIF_SNDREQ_QUE186)
#define CANIF_SNDREQ_QUE187             (BSW_CANIF_SNDREQ_QUE187)
#define CANIF_SNDREQ_QUE188             (BSW_CANIF_SNDREQ_QUE188)
#define CANIF_SNDREQ_QUE189             (BSW_CANIF_SNDREQ_QUE189)
#define CANIF_SNDREQ_QUE190             (BSW_CANIF_SNDREQ_QUE190)
#define CANIF_SNDREQ_QUE191             (BSW_CANIF_SNDREQ_QUE191)
#define CANIF_SNDREQ_QUE192             (BSW_CANIF_SNDREQ_QUE192)
#define CANIF_SNDREQ_QUE193             (BSW_CANIF_SNDREQ_QUE193)
#define CANIF_SNDREQ_QUE194             (BSW_CANIF_SNDREQ_QUE194)
#define CANIF_SNDREQ_QUE195             (BSW_CANIF_SNDREQ_QUE195)
#define CANIF_SNDREQ_QUE196             (BSW_CANIF_SNDREQ_QUE196)
#define CANIF_SNDREQ_QUE197             (BSW_CANIF_SNDREQ_QUE197)
#define CANIF_SNDREQ_QUE198             (BSW_CANIF_SNDREQ_QUE198)
#define CANIF_SNDREQ_QUE199             (BSW_CANIF_SNDREQ_QUE199)
#define CANIF_SNDREQ_QUE200             (BSW_CANIF_SNDREQ_QUE200)
#define CANIF_SNDREQ_QUE201             (BSW_CANIF_SNDREQ_QUE201)
#define CANIF_SNDREQ_QUE202             (BSW_CANIF_SNDREQ_QUE202)
#define CANIF_SNDREQ_QUE203             (BSW_CANIF_SNDREQ_QUE203)
#define CANIF_SNDREQ_QUE204             (BSW_CANIF_SNDREQ_QUE204)
#define CANIF_SNDREQ_QUE205             (BSW_CANIF_SNDREQ_QUE205)
#define CANIF_SNDREQ_QUE206             (BSW_CANIF_SNDREQ_QUE206)
#define CANIF_SNDREQ_QUE207             (BSW_CANIF_SNDREQ_QUE207)
#define CANIF_SNDREQ_QUE208             (BSW_CANIF_SNDREQ_QUE208)
#define CANIF_SNDREQ_QUE209             (BSW_CANIF_SNDREQ_QUE209)
#define CANIF_SNDREQ_QUE210             (BSW_CANIF_SNDREQ_QUE210)
#define CANIF_SNDREQ_QUE211             (BSW_CANIF_SNDREQ_QUE211)
#define CANIF_SNDREQ_QUE212             (BSW_CANIF_SNDREQ_QUE212)
#define CANIF_SNDREQ_QUE213             (BSW_CANIF_SNDREQ_QUE213)
#define CANIF_SNDREQ_QUE214             (BSW_CANIF_SNDREQ_QUE214)
#define CANIF_SNDREQ_QUE215             (BSW_CANIF_SNDREQ_QUE215)
#define CANIF_SNDREQ_QUE216             (BSW_CANIF_SNDREQ_QUE216)
#define CANIF_SNDREQ_QUE217             (BSW_CANIF_SNDREQ_QUE217)
#define CANIF_SNDREQ_QUE218             (BSW_CANIF_SNDREQ_QUE218)
#define CANIF_SNDREQ_QUE219             (BSW_CANIF_SNDREQ_QUE219)
#define CANIF_SNDREQ_QUE220             (BSW_CANIF_SNDREQ_QUE220)
#define CANIF_SNDREQ_QUE221             (BSW_CANIF_SNDREQ_QUE221)
#define CANIF_SNDREQ_QUE222             (BSW_CANIF_SNDREQ_QUE222)
#define CANIF_SNDREQ_QUE223             (BSW_CANIF_SNDREQ_QUE223)
#define CANIF_SNDREQ_QUE224             (BSW_CANIF_SNDREQ_QUE224)
#define CANIF_SNDREQ_QUE225             (BSW_CANIF_SNDREQ_QUE225)
#define CANIF_SNDREQ_QUE226             (BSW_CANIF_SNDREQ_QUE226)
#define CANIF_SNDREQ_QUE227             (BSW_CANIF_SNDREQ_QUE227)
#define CANIF_SNDREQ_QUE228             (BSW_CANIF_SNDREQ_QUE228)
#define CANIF_SNDREQ_QUE229             (BSW_CANIF_SNDREQ_QUE229)
#define CANIF_SNDREQ_QUE230             (BSW_CANIF_SNDREQ_QUE230)
#define CANIF_SNDREQ_QUE231             (BSW_CANIF_SNDREQ_QUE231)
#define CANIF_SNDREQ_QUE232             (BSW_CANIF_SNDREQ_QUE232)
#define CANIF_SNDREQ_QUE233             (BSW_CANIF_SNDREQ_QUE233)
#define CANIF_SNDREQ_QUE234             (BSW_CANIF_SNDREQ_QUE234)
#define CANIF_SNDREQ_QUE235             (BSW_CANIF_SNDREQ_QUE235)
#define CANIF_SNDREQ_QUE236             (BSW_CANIF_SNDREQ_QUE236)
#define CANIF_SNDREQ_QUE237             (BSW_CANIF_SNDREQ_QUE237)
#define CANIF_SNDREQ_QUE238             (BSW_CANIF_SNDREQ_QUE238)
#define CANIF_SNDREQ_QUE239             (BSW_CANIF_SNDREQ_QUE239)
#define CANIF_SNDREQ_QUE240             (BSW_CANIF_SNDREQ_QUE240)
#define CANIF_SNDREQ_QUE241             (BSW_CANIF_SNDREQ_QUE241)
#define CANIF_SNDREQ_QUE242             (BSW_CANIF_SNDREQ_QUE242)
#define CANIF_SNDREQ_QUE243             (BSW_CANIF_SNDREQ_QUE243)
#define CANIF_SNDREQ_QUE244             (BSW_CANIF_SNDREQ_QUE244)
#define CANIF_SNDREQ_QUE245             (BSW_CANIF_SNDREQ_QUE245)
#define CANIF_SNDREQ_QUE246             (BSW_CANIF_SNDREQ_QUE246)
#define CANIF_SNDREQ_QUE247             (BSW_CANIF_SNDREQ_QUE247)
#define CANIF_SNDREQ_QUE248             (BSW_CANIF_SNDREQ_QUE248)
#define CANIF_SNDREQ_QUE249             (BSW_CANIF_SNDREQ_QUE249)

/* CAN Controller Mode */
#define CANIF_CS_UNINIT                 (BSW_CANIF_CS_UNINIT)
#define CANIF_CS_SLEEP                  (BSW_CANIF_CS_SLEEP)
#define CANIF_CS_STARTED                (BSW_CANIF_CS_STARTED)
#define CANIF_CS_STOPPED                (BSW_CANIF_CS_STOPPED)

/* Controller ID identifier */
#define CANIF_CTRLID_PHYSICAL           (BSW_CANIF_CTRLID_PHYSICAL)
#define CANIF_CTRLID_VIRTUAL            (BSW_CANIF_CTRLID_VIRTUAL)

/* HOH identifier */
#define CANIF_HOH_PHYSICAL              (BSW_CANIF_HOH_PHYSICAL)
#define CANIF_HOH_VIRTUAL               (BSW_CANIF_HOH_VIRTUAL)

/* Vendor ID */
#define CANIF_VENDOR_ID                    (BSW_CANIF_VENDOR_ID)

/* Module ID */
#define CANIF_MODULE_ID                    (BSW_CANIF_MODULE_ID)

/* AUTOSAR Release Version */
#define CANIF_AR_RELEASE_MAJOR_VERSION     (BSW_CANIF_AR_RELEASE_MAJOR_VERSION)
#define CANIF_AR_RELEASE_MINOR_VERSION     (BSW_CANIF_AR_RELEASE_MINOR_VERSION)
#define CANIF_AR_RELEASE_REVISION_VERSION  (BSW_CANIF_AR_RELEASE_REVISION_VERSION)

/* Vendor Specification Version */
#define CANIF_SW_MAJOR_VERSION             (BSW_CANIF_SW_MAJOR_VERSION)
#define CANIF_SW_MINOR_VERSION             (BSW_CANIF_SW_MINOR_VERSION)
#define CANIF_SW_PATCH_VERSION             (BSW_CANIF_SW_PATCH_VERSION)

/* Function */
#define CanIf_Init                         (bsw_canif_st_Init)
#define CanIf_SetControllerMode            (bsw_canif_st_SetControllerMode)
#define CanIf_GetControllerMode            (bsw_canif_st_GetControllerMode)
#define CanIf_TransmitFrame                (bsw_canif_tx_TransmitFrame)
#define CanIf_CancelTransmitFrame          (bsw_canif_tx_CancelTxFrame)
#define CanIf_Transmit                     (bsw_canif_tx_Transmit)
#define CanIf_CancelTransmit               (bsw_canif_tx_CancelTransmit)
#define CanIf_ReadRxPduData                (bsw_canif_rx_ReadRxPduData)
#define CanIf_ReadTxNotifStatus            (bsw_canif_tx_ReadTxNotifStatus)
#define CanIf_ReadRxNotifStatus            (bsw_canif_rx_ReadRxNotifStatus)
#define CanIf_SetPduMode                   (bsw_canif_st_SetPduMode)
#define CanIf_GetPduMode                   (bsw_canif_st_GetPduMode)
#define CanIf_GetVersionInfo               (bsw_canif_st_GetVersionInfo)
#define CanIf_SetDynamicTxId               (bsw_canif_tx_SetDynamicTxId)
#define CanIf_SetTrcvMode                  (bsw_canif_st_SetTrcvMode)
#define CanIf_GetTrcvMode                  (bsw_canif_st_GetTrcvMode)
#define CanIf_GetTrcvWakeupReason          (bsw_canif_st_GetTrcvWkupReason)
#define CanIf_SetTrcvWakeupMode            (bsw_canif_edge_SetTrcvWkupMode)
#define CanIf_ClearTrcvWufFlag             (bsw_canif_st_ClearTrcvWufFlag)
#define CanIf_CheckWakeup                  (bsw_canif_edge_CheckWakeup)
#define CanIf_GetTxConfirmationState       (bsw_canif_tx_GetTxCfmState)
#define CanIf_CheckBaudrate                (bsw_canif_st_CheckBaudrate)
#define CanIf_ChangeBaudrate               (bsw_canif_st_ChangeBaudrate)
#define CanIf_SetBaudrate                  (bsw_canif_st_SetBaudrate)
#define CanIf_TriggerTransmit              (bsw_canif_tx_TriggerTransmit)
#define CanIf_GetRxControllerId            (bsw_canif_rx_GetControllerId)
#define CanIf_GetTxControllerId            (bsw_canif_tx_GetControllerId)
#define CanIf_GetTxCanId                   (bsw_canif_tx_GetTxCanId)
#define CanIf_GetCurrentRxCanId            (bsw_canif_rx_GetCurrentRxCanId)
#define CanIf_DeInit                       (bsw_canif_st_Shutdown)
#define CanIf_CbkPreTxMsg                  (bsw_canif_tx_CbkPreTxMsg)
#define CanIf_CbkPreRxMsg                  (bsw_canif_rx_CbkPreRxMsg)
#define CanIf_CbkLengthErr                 (bsw_canif_fs_CbkLengthErr)
#define CanIf_CbkSumErr                    (bsw_canif_fs_CbkSumErr)
#define CanIf_CbkDetectMsgCheckCorrect     (bsw_canif_fs_CbkDtctMsgChkCrrct)
#define CanIf_CbkTpLengthErr               (bsw_canif_fs_CbkTpLengthErr)
#define CanIf_CbkPreStoreMsg               (bsw_canif_rx_CbkPreStoreMsg)
#define CanIf_GetRxCanId                   (bsw_canif_rx_GetRxCanId)
#define CanIf_TransmitDirect               (bsw_canif_tx_TransmitDirect)
#define CanIf_CbkTxConfirmation            (bsw_canif_tx_CbkTxConfirmation)
#define CanIf_CbkCheckStuckRegister        (bsw_canif_fs_CbkChkStuckReg)
#define CanIf_CbkSetPduMode                (bsw_canif_st_CbkSetPduMode)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define CanIf_ConfigType                Bsw_CanIf_ConfigType
#define CanIf_PduModeType               Bsw_CanIf_PduModeType
#define CanIf_NotifStatusType           Bsw_CanIf_NotifStatusType
#define CanIf_ControllerModeType        Bsw_CanIf_ControllerModeType

#define CanIf_PduType                   Bsw_CanIf_PduType
#define CanIf_HwType                    Bsw_CanIf_HwType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANIF_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/07/10                                             */
/*  v1-1-0          :2018/10/02                                             */
/*  v2-0-0          :2021/12/12                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
