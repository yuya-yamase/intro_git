/* Dcm_Dsl_Main_Connector_Cfg_c(v5-0-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_Main_Connector_Cfg/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/cfg/Dcm_Dsl_Main_Connector_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_CONNECTION_EXTENDED_NUM         ((uint16)0x0000U)  /* Number of Dcm_Dsl_ExtTransmitType */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

static CONST(AB_83_ConstV Dcm_Dsl_ExtTransmitType, DCM_CONFIG_DATA) Dcm_Dsl_ConnectionExtMapTable[1] = 
{
        /* TxPdu            ptExtTransmitFnc     */
    {
        (PduIdType)0xFFU,  NULL_PTR
    }
};

static CONST(AB_83_ConstV uint16, DCM_CONFIG_DATA) Dcm_Dsl_u2ConnectionExtMapTableNum = DCM_DSL_CONNECTION_EXTENDED_NUM;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsl_Transmit32                                       */
/* Description   | This function is a connector for -                       */
/*               | XxxTpTransmit function.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] id : Identification of the I-PDU.                   */
/*               |                                                          */
/*               | [in] info : Length and pointer to the buffer of the      */
/*               |             I-PDU.                                       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : request is accepted by the destination module */
/*               |                   transmission is continued.             */
/*               | E_NOT_OK : request is not accepted by the destination    */
/*               |            module transmission is aborted.               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_Transmit32
(
    PduIdType id,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) info
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_ConnectionExt_Cnt;
    uint16         u2_ConnectionExt_Max;

    u1_RetVal = E_NOT_OK;
    u2_ConnectionExt_Max = Dcm_Dsl_u2ConnectionExtMapTableNum;

    for ( u2_ConnectionExt_Cnt = 0U; u2_ConnectionExt_Cnt < u2_ConnectionExt_Max; u2_ConnectionExt_Cnt++ )
    {
        if( Dcm_Dsl_ConnectionExtMapTable[u2_ConnectionExt_Cnt].TxPdu == id )
        {
            break;
        }
    }

    if ( u2_ConnectionExt_Cnt != u2_ConnectionExt_Max )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsl_ConnectionExtMapTable[u2_ConnectionExt_Cnt].ptExtTransmitFnc(id, info);
#else /* JGXSTACK */
        /* user-defined */
#endif /* JGXSTACK */
    }

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-09-26                                              */
/*  v5-0-0         :2021-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
