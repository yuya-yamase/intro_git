/* 0.0.0-010B-6 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Variation Definition : HUD                                                                                                       */
/*===================================================================================================================================*/

#ifndef HUDCSTMSUP_CFG_PRM
#define HUDCSTMSUP_CFG_PRM

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HUDCSTMSUP_CFG_PRM_MAJOR                    (0)
#define HUDCSTMSUP_CFG_PRM_MINOR                    (0)
#define HUDCSTMSUP_CFG_PRM_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "hudcom.h"
#include "vardef.h"
#include "hudcstmsup.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Definitions                                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HUDCSTMSUP_CFG_STAT_UNDEF                   (0x00)                                         /* UNDEF                          */
#define HUDCSTMSUP_CFG_STAT_ON                      (0x01)                                         /* ON                             */
#define HUDCSTMSUP_CFG_STAT_ON_GOUT                 (0x02)                                         /* ON(Grey  )                     */
#define HUDCSTMSUP_CFG_STAT_NOUSE                   (0x03)                                         /* not use                        */

#define HUDCSTMSUP_CFG_TACHDSP_OFF                  (0x00)                                         /* OFF : Hudcom HCOM_CTTACEXT_OFF  */
#define HUDCSTMSUP_CFG_TACHDSP_ECO_ON               (0x01)                                         /* ECO : Hudcom HCOM_CTTACEXT_ECO  */
#define HUDCSTMSUP_CFG_TACHDSP_HV_ON                (0x02)                                         /* HV  : Hudcom HCOM_CTTACEXT_HYBSYS */
#define HUDCSTMSUP_ST_TIMEOUT					(COM_TIMEOUT)
#define HUDCSTMSUP_ST_NO_RX					(COM_NO_RX)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_HUDCSTMSUP_CFG_HUD_IS_SUPD()             (TRUE)

#define u1_HUDCSTMSUP_CFG_CANMSGSTS_HUD1S01()       (u1_g_HcomGetCanMsgSts())

#define u1_HUDCSTMSUP_CFG_HUDSW_PW()                (u1_g_HcomGetSwPow())
#define u1_HUDCSTMSUP_CFG_HUDSW_PS()                (u1_g_HcomGetSwPos())
#define u1_HUDCSTMSUP_CFG_HUDSW_RT()                (u1_g_HcomGetSwRot())
#define u1_HUDCSTMSUP_CFG_HUDSW_DC()                (u1_g_HcomGetSwDsp())
#define u1_HUDCSTMSUP_CFG_CTAUDEXT()                (u1_g_HcomGetAudExt())
#define u1_HUDCSTMSUP_CFG_CTLANEXT()                (u1_g_HcomGetLanExt())
#define u1_HUDCSTMSUP_CFG_CTNAVEXT()                (u1_g_HcomGetNavExt())
#define u1_HUDCSTMSUP_CFG_CTADSEXT()                (u1_g_HcomGetAdsExt())
#define u1_HUDCSTMSUP_CFG_CTCMPEXT()                (u1_g_HcomGetCmpExt())
#define u1_HUDCSTMSUP_CFG_TACH_DSP()                (u1_g_HcomGetTacExt())

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #ifndef HUDCSTMSUP_CFG_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  vdfhud .c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
