/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  vCrypto Proxy                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VCRYPX_CFG_H
#define VCRYPX_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VCRYPX_CFG_H_MAJOR                        (1)
#define VCRYPX_CFG_H_MINOR                        (0)
#define VCRYPX_CFG_H_PATCH                        (0)

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "aip_common.h"
#include "Std_Types.h"
#include <ehvm.h>
#include <ehvm_cfg_pe0_vm0.h>
#include "Csm.h"
#include "vCryPx.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Channel ID for transmission from client to proxy */
#define VCRYPX_VCC_ID_C2P       (EHVM_RX_VCCID_VCC_VCRYCL_TX_VM1)
/* Channel ID for transmission from proxy to client */
#define VCRYPX_VCC_ID_P2C       (EHVM_TX_VCCID_VCC_VCRYPX_TX_VM0)


/* vCryPx_JobContextType . id_service */
#define VCRYPX_ID_SERVICE_NONE              (0xFFFFFFFFU)
#define VCRYPX_ID_SERVICE_KEYUPDATE         (0x00000000U)
#define VCRYPX_ID_SERVICE_ENCRYPT           (0x00000001U)
#define VCRYPX_ID_SERVICE_DECRYPT           (0x00000002U)
#define VCRYPX_ID_SERVICE_MACGENERATE       (0x00000003U)
#define VCRYPX_ID_SERVICE_MACVERIFY         (0x00000004U)
#define VCRYPX_ID_SERVICE_SIGNATUREVERIFY   (0x00000005U)
#define VCRYPX_ID_SERVICE_JOBRANDOMSEED     (0x00000006U)
#define VCRYPX_ID_SERVICE_RANDOMGENERATE    (0x00000007U)

/* vCryPx Service Config */
#define	VCRYPX_ID_SERVICE_NUM               (8U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct{
    U4                      u4_ServiceId;
    U4                      u4_JobId;
}ST_CRYPX_CSM_CFG;

typedef struct{
    U4                      u4_Csm_KeyId;
    U4                      u4_KeySetElemId;
    U4                      u4_KeyGetElemId;
    U4                      u4_JobId;
}ST_CRYPX_KEY_CFG;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern const U4 u4_g_VCRYPX_KEY_SET_ELEM_ID;
extern const U4 u4_g_VCRYPX_KEY_GET_ELEM_ID;

#endif  /* VCRYPX_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vCryPx.c                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/