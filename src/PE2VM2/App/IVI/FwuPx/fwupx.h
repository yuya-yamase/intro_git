/* 1.0.0 */
/*===================================================================================================================================*/
/*  XSPI Firmware Update Request Bridge (VM2 -> VM1)                                                                                */
/*===================================================================================================================================*/

#ifndef FWUPX_H
#define FWUPX_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUPX_H_MAJOR                  (1)
#define FWUPX_H_MINOR                  (0)
#define FWUPX_H_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    <Std_Types.h>

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUPX_SUBTYPE_REQ_PREP                (0x01U)
#define FWUPX_SUBTYPE_REQ_RUN                 (0x02U)
#define FWUPX_SUBTYPE_REQ_VERI                (0x18U)
#define FWUPX_SUBTYPE_REQ_CANCEL              (0x27U)
#define FWUPX_SUBTYPE_REQ_PHASE               (0x37U)
#define FWUPX_SUBTYPE_REQ_PRNUM               (0x63U)

#define FWUPX_SUBTYPE_RES_PREP            (0x07U)
#define FWUPX_SUBTYPE_RES_RUN             (0x17U)
#define FWUPX_SUBTYPE_RES_VERI            (0x19U)
#define FWUPX_SUBTYPE_RES_CANCEL          (0x28U)
#define FWUPX_SUBTYPE_RES_PHASE           (0x38U)
#define FWUPX_SUBTYPE_RES_PRNUM           (0x64U)

#define FWUPX_WRI_HEAD_WORDS              (2U)
#define FWUPX_WRI_DATA_ADR_WORDS          (1U)
#define FWUPX_WRI_DATA_SIZE_MAX           (1024U)

#define FWUPX_WRI_PREP_DATA_SIZE          (512U)
#define FWUPX_WRI_PREP_DATA_START         (4U)

#define FWUPX_WRI_RUN_DATA_SIZE           (1024U)
#if (FWUPX_WRI_RUN_DATA_SIZE != 1024U)
#error \
    "FWUPX_WRI_RUN_DATA_SIZE must be same with FWUMEMACC_WRITE_LENGTH in PE1VM1 fwumemacc.h. " \
    "Change with FWUMEMACC_WRITE_LENGTH & this error check value"
#endif
#define FWUPX_WRI_RUN_DATA_START          (6U)

#define FWUPX_READ_WORDS                  (2U)
#define FWUPX_SHIFT_BIT                   (8U)
#define FWUPX_WORD_SIZE                   (4U)


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_FwupxInit(void);
void            vd_g_FwupxMainTask(void);
U1              u1_g_FwupxResData(U1 * u1_ap_resdata, U1 u1_a_len);
void            vd_g_FwupxPutReqData(const U1 * u1_ap_SUB4_ADD, const U2 u2_a_DTLEN);

#endif /* FWUPX_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History :  fwupx.c                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
