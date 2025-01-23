/* bsw_vdat_h_v3-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VDAT/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_VDAT_H
#define BSW_VDAT_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_VDAT_USE                    (0U)
#define BSW_VDAT_NOUSE                  (1U)

#define BSW_VDAT_KIND_IPC               (0x00U)
#define BSW_VDAT_KIND_VCC               (0x01U)
#define BSW_VDAT_KIND_NONE              (0xFFU)

#define BSW_VDAT_BUSID_INVAILD          (0xFFU)

#define BSW_VDAT_OK                     (0x00U)
#define BSW_VDAT_NOT_OK                 (0x01U)
#define BSW_VDAT_OVERWRITE_OCCURS       (0x02U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef BswU1                           Bsw_VDat_ReturnType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
Bsw_VDat_ReturnType     bsw_vdat_InitNode( BswU1 ConnectionId, BswU1 NodeId );
void                    bsw_vdat_StartNode( BswU1 ConnectionId, BswU1 NodeId );
Bsw_VDat_ReturnType     bsw_vdat_Receive( BswU1 ConnectionId, BswU1 NodeId, BswU4* Data, BswU4 BufSize, BswU4* Size );
Bsw_VDat_ReturnType     bsw_vdat_Transmit( BswU1 ConnectionId, BswU1 NodeId, BswU4* Data, BswU4 Size );
void                    bsw_vdat_CbkPostTx( BswU1 ConnectionId, BswU1 NodeId );
void                    bsw_vdat_DeInitNode( BswU1 ConnectionId, BswU1 NodeId );
void                    bsw_vdat_CbkDetectFail( BswU1 ConnectionId, BswU1 NodeId );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_VDAT_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/04                                             */
/*  v2-1-0          :2022/09/22                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
