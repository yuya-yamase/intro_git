/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 4 in XSPI communication.                                                       */
/*  Handled data: CAN Data/Repro/LCAN Data                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB1_VERSION_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_VERSION_C_MINOR                   (0)
#define XSPI_IVI_SUB1_VERSION_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_version.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_VERSION_C_MAJOR != XSPI_IVI_SUB1_VERSION_H_MAJOR) || \
     (XSPI_IVI_SUB1_VERSION_C_MINOR != XSPI_IVI_SUB1_VERSION_H_MINOR) || \
     (XSPI_IVI_SUB1_VERSION_C_PATCH != XSPI_IVI_SUB1_VERSION_H_PATCH))
#error "x_spi_ivi_sub1_version.c and x_spi_ivi_sub1.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB1_VERSION_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB1_VERSION_C_MINOR != XSPI_IVI_SUB1_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB1_VERSION_C_PATCH != XSPI_IVI_SUB1_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub1_version.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_VERSION_ID    (0x24U)
#define    XSPI_IVI_VERSION_RQST  (0x01U)
#define    XSPI_IVI_VERSION_RES   (0x02U)

#define    XSPI_IVI_VERSION_SIZE  (34U)
#define    XSPI_IVI_VERSION_MAJOR (0x00U)
#define    XSPI_IVI_VERSION_MINOR (0x01U)
#define    XSPI_IVI_VERSION_GSEN  (0x10U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
volatile U4 * const    u4p_s_VERSION_MAJ = (volatile U4 *)0x007FFB00U;
volatile U4 * const    u4p_s_VERSION_MIN = (volatile U4 *)0x007FFB00U;
/*Gセンサバージョンはシス検では対応しない*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1_VersionReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
static void            vd_s_XspiIviSub1_VersionDataToQueue(const U1* u1_ap_XSPI_ADD, const U1 u1_a_SIZE);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1VersionInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1VersionInit(void)
{
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1VersionMainTask(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1VersionMainTask(void)
{
    /*定期送信などのデータ作成をここで行う*/
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1VersionAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1VersionAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    U1 u1_t_subtype;

    u1_t_subtype = u1_ap_XSPI_ADD[0];

    switch (u1_t_subtype)
    {
    case XSPI_IVI_VERSION_RQST:
        vd_s_XspiIviSub1_VersionReq(u1_ap_XSPI_ADD,u2_a_DATA_SIZE);
        break;
    
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_VersionReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_VersionReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    U1     u1_s_MAJORVERSIZE = (U1)4U;
    U1     u1_s_MINORVERSIZE = (U1)4U;
    U1     u1_t_verison_type;
    U1     u1_tp_data[XSPI_IVI_VERSION_SIZE];
    U4     u4_t_version;

    /*[1]のデータをSend側に送る*/
    u1_t_verison_type = u1_ap_XSPI_ADD[1];
    u1_tp_data[0] = (U1)XSPI_IVI_VERSION_RES;
    u1_tp_data[1] = u1_t_verison_type;
    switch (u1_t_verison_type)
    {
    case XSPI_IVI_VERSION_MAJOR:
        u4_t_version = *u4p_s_VERSION_MAJ;
        u1_tp_data[2] = (U1)(u4_t_version & 0x000000FFU);
        u1_tp_data[3] = (U1)((u4_t_version & 0x0000FF00U) >> XSPI_IVI_SFT_08);
        vd_s_XspiIviSub1_VersionDataToQueue(&u1_tp_data[0],u1_s_MAJORVERSIZE);
        break;
    case XSPI_IVI_VERSION_MINOR:
        u4_t_version = *u4p_s_VERSION_MIN;
        u1_tp_data[2] = (U1)(u4_t_version & 0x000000FFU);
        u1_tp_data[3] = (U1)((u4_t_version & 0x0000FF00U) >> XSPI_IVI_SFT_08);
        vd_s_XspiIviSub1_VersionDataToQueue(&u1_tp_data[0],u1_s_MINORVERSIZE);
        break;
    case XSPI_IVI_VERSION_GSEN:
        /*シス検 skip*/
        break;
    
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub1_VersionDataToQueue(const U1* u1_ap_XSPI_ADD, const U1 u1_a_SIZE)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_VersionDataToQueue(const U1* u1_ap_XSPI_ADD, const U1 u1_a_SIZE)
{
    U2     u2_s_MISC_VERSION_SIZE = (U2)XSPI_IVI_VERSION_SIZE;

    U1     u1_tp_data[XSPI_IVI_VERSION_SIZE];
    U1     u1_t_id;

    u1_t_id = (U1)XSPI_IVI_VERSION_ID;
    vd_g_MemfillU1(&u1_tp_data[0], (U1)0U, (U4)XSPI_IVI_VERSION_SIZE);
    vd_g_MemcpyU1(&u1_tp_data[0], &u1_ap_XSPI_ADD[0], (U4)u1_a_SIZE);

    /*キューの関数呼び出し*/
    vd_g_XspiIviSub1MISCStuckBuff(u1_t_id,u2_s_MISC_VERSION_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    01/31/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
