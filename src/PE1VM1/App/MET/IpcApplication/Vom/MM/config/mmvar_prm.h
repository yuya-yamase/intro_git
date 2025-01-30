/* 19PFV3_1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  MMテキストデータ制御でカスタマイズするデータを定義する                                                                           */
/*===================================================================================================================================*/

#ifndef MMVAR_PRM
#define MMVAR_PRM

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMVAR_PRM_MAJOR                    (1)
#define MMVAR_PRM_MINOR                    (0)
#define MMVAR_PRM_PATCH                    (0)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "mmlib.h"
#include "MM_Appl.h"
#include "mmvar.h"
#include "veh_opemd.h"
#include "mmtim.h"
#include "mmtext.h"
#include "oxcan.h"
#include "memcpy_u2.h"
#include "memfill_u2.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type definition                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMVAR_AVNMS72_MSG                 (MSG_AVNMS72_RXCH1)

/* MMTIMID */
#define MMVAR_TIMERID_UNAME_ACCON           (MMTIM_TIMERID_UNAME_ACCON)
#define MMVAR_TIMERID_UNAME_INTERVAL        (MMTIM_TIMERID_UNAME_INTERVAL)

#define MMVAR_UNAME_INT                     (0x0FU)                              /* MMVAR_UNAME_INT                                  */
#define MMVAR_UNAME1                        (0x01U)                              /* MMVAR_UNAME1                                     */
#define MMVAR_UNAME2                        (0x02U)                              /* MMVAR_UNAME2                                     */
#define MMVAR_UNAME3                        (0x03U)                              /* MMVAR_UNAME3                                     */
#define MMVAR_UNAME_MAX                     (0x03U)                              /* MMVAR_UNAME_MAX                                  */
#define MMVAR_CHG_UNAME_VALID_MAX           (0x0EU)                              /* MMVAR_CHG_UNAME_VALID_MAX                        */
#define MMVAR_CHG_UNAME_VALID_MIN           (0x01U)                              /* MMVAR_CHG_UNAME_VALID_MIN                        */
#define MMVAR_CHG_UNAME_INT                 (0x0FU)                              /* MMVAR_CHG_UNAME_INT                              */
#define MMVAR_REQ_UNAME_FLG_NO              (0x00U)                              /* MMVAR_REQ_UNAME_FLG_NO                           */

/* MMText */
#define MMVAR_RET_OK                        (MMTEXT_RET_OK)
#define MMVAR_TEXT_LENGTH_AVNMS72           (MMTEXT_TEXT_LENGTH_AVNMS72)

#define MMVAR_USRDAT_MAX                    (31U)
#define MMVAR_VALNUM_INT                    (0U)
#define MMVAR_VALNUM_MAX                    (30U)
#define MMVAR_FLG_ON                        (1U)
#define MMVAR_FLG_OFF                       (0U)

#define MMVAR_CHAR_NULL                     (0x0000)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_MMVAR_ACCISON()                  (u1_g_VehopemdAccOn())              /* ACC状態通知                                       */

/* MMText */
#define u1_s_MMVAR_TEXTGETDATA_AVNMS72(st_textdata)  (u1_g_MMText_GetTextData_AVNMS72(st_textdata))
#define vd_s_MMVAR_SENDREQUSERNAME(u1_req_uname)             (vd_g_MMText_SendReqUserName(u1_req_uname))

/* MMTim */
#define vd_s_MMVAR_STARTTIMERRESERVE(u1_timerid)      (vd_g_MMTim_StartTimerReserve((U1)(u1_timerid)))
#define vd_s_MMVAR_STOPTIMER(u1_timerid)              (vd_g_MMTim_StopTimer((U1)(u1_timerid)))

/* Copy */
#define vd_s_MMVAR_COPYU2(u2_ap_pdst,u2_ap_PSRC,u2_a_nword) (vd_g_MemcpyU2((u2_ap_pdst), (u2_ap_PSRC), (U4)(u2_a_nword)))

/* Clear */
#define vd_g_MMVAR_CLEAR_TEXT_UNAME(u2_buff)     (vd_g_MemfillU2((u2_buff), (U2)MMVAR_CHAR_NULL, (U4)((U1)MMVAR_TEXT_LENGTH_AVNMS72 * MMVAR_UNAME_MAX)))
#define vd_g_MMVAR_CLEAR_CHG_UNAME(u2_buff)      (vd_g_MemfillU2((u2_buff), (U2)MMVAR_CHG_UNAME_INT, (U4)MMVAR_UNAME_MAX))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* MMVAR_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  mmvar.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
