/* bsw_vcan_config_h_v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/CONFIG/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_VCAN_CONFIG_H
#define     BSW_VCAN_CONFIG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_VCAN_VHRHNUM                (BSW_VCAN_TBL_VHRHNUM)
#define BSW_VCAN_VHTHNUM                (BSW_VCAN_TBL_VHTHNUM)
#define BSW_VCAN_VHOHNUM                (BSW_VCAN_VHRHNUM + BSW_VCAN_VHTHNUM)
#define BSW_VCAN_USERTX_VMBOXNUM        (BSW_VCAN_TBL_USERTX_VMBOXNUM)


/* IPC use/unuse */
#define BSW_VCAN_IPC_FUNC    (BSW_VCAN_IPC_FUNC0)
#define BSW_VCAN_IPC_FUNC0  ((BSW_VCAN_CFG_IPC_VCONTROLLER0  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC1)
#define BSW_VCAN_IPC_FUNC1  ((BSW_VCAN_CFG_IPC_VCONTROLLER1  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC2)
#define BSW_VCAN_IPC_FUNC2  ((BSW_VCAN_CFG_IPC_VCONTROLLER2  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC3)
#define BSW_VCAN_IPC_FUNC3  ((BSW_VCAN_CFG_IPC_VCONTROLLER3  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC4)
#define BSW_VCAN_IPC_FUNC4  ((BSW_VCAN_CFG_IPC_VCONTROLLER4  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC5)
#define BSW_VCAN_IPC_FUNC5  ((BSW_VCAN_CFG_IPC_VCONTROLLER5  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC6)
#define BSW_VCAN_IPC_FUNC6  ((BSW_VCAN_CFG_IPC_VCONTROLLER6  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC7)
#define BSW_VCAN_IPC_FUNC7  ((BSW_VCAN_CFG_IPC_VCONTROLLER7  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC8)
#define BSW_VCAN_IPC_FUNC8  ((BSW_VCAN_CFG_IPC_VCONTROLLER8  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC9)
#define BSW_VCAN_IPC_FUNC9  ((BSW_VCAN_CFG_IPC_VCONTROLLER9  == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC10)
#define BSW_VCAN_IPC_FUNC10 ((BSW_VCAN_CFG_IPC_VCONTROLLER10 == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC11)
#define BSW_VCAN_IPC_FUNC11 ((BSW_VCAN_CFG_IPC_VCONTROLLER11 == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC12)
#define BSW_VCAN_IPC_FUNC12 ((BSW_VCAN_CFG_IPC_VCONTROLLER12 == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC13)
#define BSW_VCAN_IPC_FUNC13 ((BSW_VCAN_CFG_IPC_VCONTROLLER13 == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC14)
#define BSW_VCAN_IPC_FUNC14 ((BSW_VCAN_CFG_IPC_VCONTROLLER14 == BSW_VCAN_IPC) ? BSW_USE : BSW_VCAN_IPC_FUNC15)
#define BSW_VCAN_IPC_FUNC15 ((BSW_VCAN_CFG_IPC_VCONTROLLER15 == BSW_VCAN_IPC) ? BSW_USE : BSW_NOUSE)

/* VCC used/unused */
#define BSW_VCAN_VCC_FUNC    (BSW_VCAN_VCC_FUNC0)
#define BSW_VCAN_VCC_FUNC0  ((BSW_VCAN_CFG_IPC_VCONTROLLER0  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC1)
#define BSW_VCAN_VCC_FUNC1  ((BSW_VCAN_CFG_IPC_VCONTROLLER1  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC2)
#define BSW_VCAN_VCC_FUNC2  ((BSW_VCAN_CFG_IPC_VCONTROLLER2  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC3)
#define BSW_VCAN_VCC_FUNC3  ((BSW_VCAN_CFG_IPC_VCONTROLLER3  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC4)
#define BSW_VCAN_VCC_FUNC4  ((BSW_VCAN_CFG_IPC_VCONTROLLER4  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC5)
#define BSW_VCAN_VCC_FUNC5  ((BSW_VCAN_CFG_IPC_VCONTROLLER5  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC6)
#define BSW_VCAN_VCC_FUNC6  ((BSW_VCAN_CFG_IPC_VCONTROLLER6  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC7)
#define BSW_VCAN_VCC_FUNC7  ((BSW_VCAN_CFG_IPC_VCONTROLLER7  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC8)
#define BSW_VCAN_VCC_FUNC8  ((BSW_VCAN_CFG_IPC_VCONTROLLER8  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC9)
#define BSW_VCAN_VCC_FUNC9  ((BSW_VCAN_CFG_IPC_VCONTROLLER9  == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC10)
#define BSW_VCAN_VCC_FUNC10 ((BSW_VCAN_CFG_IPC_VCONTROLLER10 == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC11)
#define BSW_VCAN_VCC_FUNC11 ((BSW_VCAN_CFG_IPC_VCONTROLLER11 == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC12)
#define BSW_VCAN_VCC_FUNC12 ((BSW_VCAN_CFG_IPC_VCONTROLLER12 == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC13)
#define BSW_VCAN_VCC_FUNC13 ((BSW_VCAN_CFG_IPC_VCONTROLLER13 == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC14)
#define BSW_VCAN_VCC_FUNC14 ((BSW_VCAN_CFG_IPC_VCONTROLLER14 == BSW_VCAN_VCC) ? BSW_USE : BSW_VCAN_VCC_FUNC15)
#define BSW_VCAN_VCC_FUNC15 ((BSW_VCAN_CFG_IPC_VCONTROLLER15 == BSW_VCAN_VCC) ? BSW_USE : BSW_NOUSE)

/* Virtual communication module switching index */
#define BSW_VCAN_VIRTUALTBL_INDEX(id)   ((BSW_VCAN_CFG_IPC_VCONTROLLER##id == BSW_VCAN_IPC) ? BSW_VCAN_IPC : BSW_VCAN_VCC )

/* Number of virtual MBOX (Tx+UserTx) for transmission by virtual controller */
#define BSW_VCAN_TX_VMBOXNUM_0               ( BSW_VCAN_CFG_VHTHNUM_0 + BSW_VCAN_CFG_USERTX_VMBOXNUM_0 )
#define BSW_VCAN_TX_VMBOXNUM_1               ( BSW_VCAN_CFG_VHTHNUM_1 + BSW_VCAN_CFG_USERTX_VMBOXNUM_1 )
#define BSW_VCAN_TX_VMBOXNUM_2               ( BSW_VCAN_CFG_VHTHNUM_2 + BSW_VCAN_CFG_USERTX_VMBOXNUM_2 )
#define BSW_VCAN_TX_VMBOXNUM_3               ( BSW_VCAN_CFG_VHTHNUM_3 + BSW_VCAN_CFG_USERTX_VMBOXNUM_3 )
#define BSW_VCAN_TX_VMBOXNUM_4               ( BSW_VCAN_CFG_VHTHNUM_4 + BSW_VCAN_CFG_USERTX_VMBOXNUM_4 )
#define BSW_VCAN_TX_VMBOXNUM_5               ( BSW_VCAN_CFG_VHTHNUM_5 + BSW_VCAN_CFG_USERTX_VMBOXNUM_5 )
#define BSW_VCAN_TX_VMBOXNUM_6               ( BSW_VCAN_CFG_VHTHNUM_6 + BSW_VCAN_CFG_USERTX_VMBOXNUM_6 )
#define BSW_VCAN_TX_VMBOXNUM_7               ( BSW_VCAN_CFG_VHTHNUM_7 + BSW_VCAN_CFG_USERTX_VMBOXNUM_7 )
#define BSW_VCAN_TX_VMBOXNUM_8               ( BSW_VCAN_CFG_VHTHNUM_8 + BSW_VCAN_CFG_USERTX_VMBOXNUM_8 )
#define BSW_VCAN_TX_VMBOXNUM_9               ( BSW_VCAN_CFG_VHTHNUM_9 + BSW_VCAN_CFG_USERTX_VMBOXNUM_9 )
#define BSW_VCAN_TX_VMBOXNUM_10              ( BSW_VCAN_CFG_VHTHNUM_10 + BSW_VCAN_CFG_USERTX_VMBOXNUM_10 )
#define BSW_VCAN_TX_VMBOXNUM_11              ( BSW_VCAN_CFG_VHTHNUM_11 + BSW_VCAN_CFG_USERTX_VMBOXNUM_11 )
#define BSW_VCAN_TX_VMBOXNUM_12              ( BSW_VCAN_CFG_VHTHNUM_12 + BSW_VCAN_CFG_USERTX_VMBOXNUM_12 )
#define BSW_VCAN_TX_VMBOXNUM_13              ( BSW_VCAN_CFG_VHTHNUM_13 + BSW_VCAN_CFG_USERTX_VMBOXNUM_13 )
#define BSW_VCAN_TX_VMBOXNUM_14              ( BSW_VCAN_CFG_VHTHNUM_14 + BSW_VCAN_CFG_USERTX_VMBOXNUM_14 )
#define BSW_VCAN_TX_VMBOXNUM_15              ( BSW_VCAN_CFG_VHTHNUM_15 + BSW_VCAN_CFG_USERTX_VMBOXNUM_15 )

/* Virtual HRH total number */
#define BSW_VCAN_TBL_VHRHNUM                 ( BSW_VCAN_TBL_VHRHNUM_0_7 + BSW_VCAN_TBL_VHRHNUM_8_15 )
#define BSW_VCAN_TBL_VHRHNUM_0_7             ( BSW_VCAN_CFG_VHRHNUM_0 \
 + BSW_VCAN_CFG_VHRHNUM_1 \
 + BSW_VCAN_CFG_VHRHNUM_2 \
 + BSW_VCAN_CFG_VHRHNUM_3 \
 + BSW_VCAN_CFG_VHRHNUM_4 \
 + BSW_VCAN_CFG_VHRHNUM_5 \
 + BSW_VCAN_CFG_VHRHNUM_6 \
 + BSW_VCAN_CFG_VHRHNUM_7 )
#define BSW_VCAN_TBL_VHRHNUM_8_15            ( BSW_VCAN_CFG_VHRHNUM_8 \
 + BSW_VCAN_CFG_VHRHNUM_9 \
 + BSW_VCAN_CFG_VHRHNUM_10 \
 + BSW_VCAN_CFG_VHRHNUM_11 \
 + BSW_VCAN_CFG_VHRHNUM_12 \
 + BSW_VCAN_CFG_VHRHNUM_13 \
 + BSW_VCAN_CFG_VHRHNUM_14 \
 + BSW_VCAN_CFG_VHRHNUM_15 )

/* Virtual HTH total number */
#define BSW_VCAN_TBL_VHTHNUM                 ( BSW_VCAN_TBL_VHTHNUM_0_7 + BSW_VCAN_TBL_VHTHNUM_8_15 )
#define BSW_VCAN_TBL_VHTHNUM_0_7             ( BSW_VCAN_CFG_VHTHNUM_0 \
 + BSW_VCAN_CFG_VHTHNUM_1 \
 + BSW_VCAN_CFG_VHTHNUM_2 \
 + BSW_VCAN_CFG_VHTHNUM_3 \
 + BSW_VCAN_CFG_VHTHNUM_4 \
 + BSW_VCAN_CFG_VHTHNUM_5 \
 + BSW_VCAN_CFG_VHTHNUM_6 \
 + BSW_VCAN_CFG_VHTHNUM_7 )
#define BSW_VCAN_TBL_VHTHNUM_8_15            ( BSW_VCAN_CFG_VHTHNUM_8 \
 + BSW_VCAN_CFG_VHTHNUM_9 \
 + BSW_VCAN_CFG_VHTHNUM_10 \
 + BSW_VCAN_CFG_VHTHNUM_11 \
 + BSW_VCAN_CFG_VHTHNUM_12 \
 + BSW_VCAN_CFG_VHTHNUM_13 \
 + BSW_VCAN_CFG_VHTHNUM_14 \
 + BSW_VCAN_CFG_VHTHNUM_15 )

/* Number of virtual MBOX for user transmission */
#define BSW_VCAN_TBL_USERTX_VMBOXNUM         ( BSW_VCAN_TBL_USERTX_VMBOX_0_7 + BSW_VCAN_TBL_USERTX_VMBOX_8_15 )
#define BSW_VCAN_TBL_USERTX_VMBOX_0_7        ( BSW_VCAN_CFG_USERTX_VMBOXNUM_0 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_1 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_2 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_3 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_4 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_5 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_6 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_7 )
#define BSW_VCAN_TBL_USERTX_VMBOX_8_15            ( BSW_VCAN_CFG_USERTX_VMBOXNUM_8 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_9 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_10 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_11 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_12 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_13 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_14 \
 + BSW_VCAN_CFG_USERTX_VMBOXNUM_15 )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1 bsw_vcan_u1IpcVirtualCtrlBus[];
extern BswConst BswU4 bsw_vcan_tx_u4VirtualCtrlToNode[];

#endif  /* BSW_VCAN_CONFIG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
