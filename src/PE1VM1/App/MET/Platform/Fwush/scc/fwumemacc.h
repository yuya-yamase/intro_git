/* 1.0.0 */
/*===================================================================================================================================*/
/*  FW Update Memory Access                                                                                                          */
/*===================================================================================================================================*/

#ifndef FWUMEMACC_H
#define FWUMEMACC_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUMEMACC_H_MAJOR                   (1U)
#define FWUMEMACC_H_MINOR                   (0U)
#define FWUMEMACC_H_PATCH                   (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MemAcc Erase */
#define FWUMEMACC_ERASE_STS_NON             (0U)
#define FWUMEMACC_ERASE_STS_ACT             (1U)
#define FWUMEMACC_ERASE_STS_COMP            (2U)
#define FWUMEMACC_ERASE_STS_ERR             (3U)

/* MemAcc Update */
#define FWUMEMACC_UPDT_STS_NON              (0U)
#define FWUMEMACC_UPDT_STS_WRITE            (1U)
#define FWUMEMACC_UPDT_STS_1B_COMP          (2U)
#define FWUMEMACC_UPDT_STS_CRC              (3U)
#define FWUMEMACC_UPDT_STS_ALL_COMP         (4U)
#define FWUMEMACC_UPDT_STS_ERR              (5U)

/* MemAcc Switch */
#define FWUMEMACC_SWITCH_STS_NON            (0U)
#define FWUMEMACC_SWITCH_STS_ACT            (1U)
#define FWUMEMACC_SWITCH_STS_COMP           (2U)
#define FWUMEMACC_SWITCH_STS_ERR            (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_FwuMemAccInit(void);
void            vd_g_FwuMemAccMainTask(void);

void            vd_g_FwuMemAccEraseReqTrg(const U4 u4_a_START_ADRS, const U4 u4_a_RPRGDAT_LEN, const U4 u4_a_CRC_DATA);
void            vd_g_FwuMemAccUpdateReqTrg(const U2 u2_a_BLK_OFFSET, const U4* u4_ap_WRT_DATA);
void            vd_g_FwuMemAccSwitchReqTrg(void);

U1              u1_g_FwuMemAccEraseSts(void);
U1              u1_g_FwuMemAccUpdateSts(void);
U1              u1_g_FwuMemAccSwitchSts(void);

#endif /* FWUMEMACC_H */
/*===================================================================================================================================*/
