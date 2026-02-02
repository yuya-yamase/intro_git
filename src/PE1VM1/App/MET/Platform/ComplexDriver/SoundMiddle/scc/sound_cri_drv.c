/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Sound Middleware (CRI) Driver                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_CRI_DRV_C_MAJOR                        (2)
#define SOUND_CRI_DRV_C_MINOR                        (0)
#define SOUND_CRI_DRV_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#include "aip_common.h"
#include "sound_cri_drv.h"

/* CRI header file */
#include "cri_xpt.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "def_hw.h"             /* ハードウェア設定 */
#include "Port.h"
#include "Dma.h"
#include "Dma_Desc.h"
#include "pwm_drv.h"
#include "gpt_drv_d16.h"
#include "gpt_drv_frt.h"
#include "reg_dma.h"
#include "int_handler.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SOUND_CRI_DRV_C_MAJOR != SOUND_CRI_DRV_H_MAJOR) || \
     (SOUND_CRI_DRV_C_MINOR != SOUND_CRI_DRV_H_MINOR) || \
     (SOUND_CRI_DRV_C_PATCH != SOUND_CRI_DRV_H_PATCH))
#error "sound_cri_drv.c and sound_cri_drv.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 一斉書き換え許可状態トリガ用変数
 * [SPEC] RsrcDrv_DmacStart関数で初期化された後、
 *        この変数はDMA転送対象として保持し続ける必要があります。
 *        静的記憶領域に配置する必要がありますのでご注意ください。
 */
static U4 s_rsrc_taud0_rdt_value;

/*
 * ディスクリプタIDからポインタを取得
 */
static U2 get_descriptor_ptr_from_id(CriSfrDrvDescriptorId descriptor_id)
{
    switch (descriptor_id)
    {
        case CRISFRDRVDESCRIPTORID_P_0:
            return u2_DMAC_DESC_PTR_BUZ_S1_0;
        case CRISFRDRVDESCRIPTORID_N_0: 
            return u2_DMAC_DESC_PTR_BUZ_S2_0;
        case CRISFRDRVDESCRIPTORID_P_1:
            return u2_DMAC_DESC_PTR_BUZ_S1_1;
        case CRISFRDRVDESCRIPTORID_N_1:
            return u2_DMAC_DESC_PTR_BUZ_S2_1;
        default:
            return u2_DMAC_DESC_PTR_BUZ_S1_0;
    }
}


/*===================================================================================================================================*/
/*  Initial process                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvInitialize(void)
{
}

/*===================================================================================================================================*/
/*  Timer start process                                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_TimerStart(void)                                                                                                     */
void vd_g_SoundCriDrvTimerInitialize(void)
{
    return;
}


/*===================================================================================================================================*/
/*  timer stop process                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_TimerStop(void)                                                                                                      */
void vd_g_SoundCriDrvTimerFinalize(void)
{
    return;
}

/*===================================================================================================================================*/
/*  Get timer count process                                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* CriUint32 RsrcDrv_TimerGetCount(void)                                                                                             */
CriUint32 u4_g_SoundCriDrvTimerGetCount(void)
{
	U4 timer_count = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
	timer_count = 0xFFFFFFFFU - timer_count;
	return timer_count;
}

/*===================================================================================================================================*/
/*  DMAC start process(SoftwareTrigger)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Note:dma_drv.c                                                                                                                   */
/*       Caution:Don't call u4_g_DmaEnaCh and vd_g_DmaDisCh of the same channel at the same time, to prevent resource collision.     */
/*===================================================================================================================================*/
/* void RsrcDrv_DmacStart(const CriUint32 src_addr_tbl[CRISFRDRVDMACH_NUM], const CriSfrDrvDescriptorId descriptor_id_tbl[CRISFRDRVDMACH_NUM], CriUint32 transfer_count) */
void vd_g_SoundCriDrvDmacStart(const CriUint32 src_addr_tbl[CRISFRDRVDMACH_NUM], const CriSfrDrvDescriptorId descriptor_id_tbl[CRISFRDRVDMACH_NUM], CriUint32 transfer_count)
{
    U4* src_addr_P;
    U4* src_addr_N;
    U4* src_addr_Master;
    U2 descriptor_ptr_P;
    U2 descriptor_ptr_N;

    /* 一斉書き換え許可状態トリガ用変数 
     * HW_TAUD_CH_MASTERのRDTレジスタに転送する定数を定義
     */
    s_rsrc_taud0_rdt_value = (0x1U << HW_TAUD_CH_MASTER)
                            | (0x1U << HW_TAUD_CH_SLAVE_P)
                            | (0x1U << HW_TAUD_CH_SLAVE_N); 

    src_addr_P = (U4*) src_addr_tbl[CRISFRDRVDMACH_P];
    src_addr_N = (U4*) src_addr_tbl[CRISFRDRVDMACH_N];
    src_addr_Master = &s_rsrc_taud0_rdt_value;

    descriptor_ptr_P = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_P]);
    descriptor_ptr_N = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_N]);

    Dma_SetTransModeDoubleBufferReload( DMA_CH_DATA_ID_7, u1DMA_TRANSSIZE_2, DMA_DESCMODE0, src_addr_P, (volatile const void*)HW_TAUD_CH_SLAVE_P_CDR_ADDR , (U2)transfer_count, descriptor_ptr_P );
    Dma_SetTransModeDoubleBufferReload( DMA_CH_DATA_ID_8, u1DMA_TRANSSIZE_2, DMA_DESCMODE1, src_addr_N, (volatile const void*)HW_TAUD_CH_SLAVE_N_CDR_ADDR, (U2)transfer_count, descriptor_ptr_N );
    Dma_SetTransModeDoubleBufferReload( DMA_CH_DATA_ID_9, u1DMA_TRANSSIZE_2, DMA_DESCMODE2, src_addr_Master, (volatile const void*)HW_TAUD_RDT_ADDR, (U2)HW_DMAC_CH_MASTER_TRNSFR_BYTE_SIZE, u2_DMAC_DESC_PTR_BUZ_M_0 );

    Dma_EnableTrans(DMA_CH_DATA_ID_7);
    Dma_EnableTrans(DMA_CH_DATA_ID_8);
    Dma_EnableTrans(DMA_CH_DATA_ID_9);

}

/*===================================================================================================================================*/
/*  DMAC interrupt process(CRI Library)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_DmacIntr(const CriUint32 reload_src_addr_tbl[CRISFRDRVDMACH_NUM], const CriSfrDrvDescriptorId descriptor_id_tbl[CRISFRDRVDMACH_NUM], CriUint32 transfer_count) */
void vd_g_SoundCriDrvDmacIntr(const CriUint32 reload_src_addr_tbl[CRISFRDRVDMACH_NUM], const CriSfrDrvDescriptorId descriptor_id_tbl[CRISFRDRVDMACH_NUM], CriUint32 transfer_count)
{
    U4* reload_src_addr_P;
    U4* reload_src_addr_N;
    U2 descriptor_ptr_P;
    U2 descriptor_ptr_N;

    reload_src_addr_P = (U4*) reload_src_addr_tbl[CRISFRDRVDMACH_P];
    reload_src_addr_N = (U4*) reload_src_addr_tbl[CRISFRDRVDMACH_N];
    descriptor_ptr_P = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_P]);
    descriptor_ptr_N = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_N]);

    Dma_ReloadDataUpdate(DMA_CH_DATA_ID_7, u1DMA_TRANSSIZE_2, reload_src_addr_P, (volatile const void*)HW_TAUD_CH_SLAVE_P_CDR_ADDR , (U2)transfer_count, descriptor_ptr_P);
    Dma_ReloadDataUpdate(DMA_CH_DATA_ID_8, u1DMA_TRANSSIZE_2, reload_src_addr_N, (volatile const void*)HW_TAUD_CH_SLAVE_N_CDR_ADDR, (U2)transfer_count, descriptor_ptr_N);
}

/*===================================================================================================================================*/
/*  DMAC stop process                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_DmacStop(void)                                                                                                       */
void vd_g_SoundCriDrvDmacStop(void)
{
    Dma_DisableTrans(DMA_CH_DATA_ID_7);
    Dma_DisableTrans(DMA_CH_DATA_ID_8);
    Dma_DisableTrans(DMA_CH_DATA_ID_9);
}

/*===================================================================================================================================*/
/*  DMA Interrupt disable process                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_IntrDisable(void)                                                                                                    */
void vd_g_SoundCriDrvDmaDisableIntr(void)
{
    vd_g_IntHndlrIRQCtrlCh(DMA_INTC2_INTSDMAC0CH7, (U1)0);
}

/*===================================================================================================================================*/
/*  DMA Interrupt enable process                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_IntrEnable(void)                                                                                                     */
void vd_g_SoundCriDrvDmaEnableIntr(void)
{
    vd_g_IntHndlrIRQCtrlCh(DMA_INTC2_INTSDMAC0CH7, INT_HNDLR_IRQ_CTRL_CH_ENA);
}

/*===================================================================================================================================*/
/*  TAUD start process                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_TaudStart(CriUint16 master_CDR, CriUint16 slave_CDR)                                                                 */
void vd_g_SoundCriDrvTaudStart(CriUint16 master_CDR, CriUint16 slave_CDR)
{
    U2 u2_a_D16_CHBIT = 1U << HW_TAUD_CH_MASTER  |
                        1U << HW_TAUD_CH_SLAVE_P |
                        1U << HW_TAUD_CH_SLAVE_N ;

    const U2     u2_sp_CARSPDPLS_OPEN_TAUD_MASTER[GPT_D16_START_NUM_CFG] = {
        (U2)GPT_D16_START_CTRL_BIT_ELVL,
        (U2)(master_CDR + 1)
    };
    const U2     u2_sp_CARSPDPLS_OPEN_TAUD_SLAVE[GPT_D16_START_NUM_CFG] = {
        (U2)GPT_D16_START_CTRL_BIT_ELVL,
        (U2)(slave_CDR + 1)
    };

    vd_g_Gpt_D16Start((U1)GPT_D16_UN_1_CH_00_BUZZER_M, &u2_sp_CARSPDPLS_OPEN_TAUD_MASTER[0]);
    vd_g_Gpt_D16Start((U1)GPT_D16_UN_1_CH_01_BUZZER_S1, &u2_sp_CARSPDPLS_OPEN_TAUD_SLAVE[0]);
    vd_g_Gpt_D16Start((U1)GPT_D16_UN_1_CH_02_BUZZER_S2, &u2_sp_CARSPDPLS_OPEN_TAUD_SLAVE[0]);

    /* ADXATで利用する3ch同時スタート */
    vd_g_Gpt_D16SyncStart( (U1)GPT_D16_UNIT_1, u2_a_D16_CHBIT );
}

/*===================================================================================================================================*/
/*  TAUD stop process                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* void RsrcDrv_TaudStop(void)                                                                                                       */
void vd_g_SoundCriDrvTaudStop(void)
{
    U2 u2_a_D16_CHBIT = 1U << HW_TAUD_CH_MASTER  |
                        1U << HW_TAUD_CH_SLAVE_P |
                        1U << HW_TAUD_CH_SLAVE_N ;

    vd_g_Gpt_D16SyncStop((U1)GPT_D16_UNIT_1, u2_a_D16_CHBIT );
}

/*===================================================================================================================================*/
/*  DMAC interrupt process(IntHandler)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvDmacInterrupt(void)
{
    criAtomEx_ExecServerIntr_Rh850u2a();
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     6/13/2019  YK       Create SoundMiddle based on TY3S soft.                                                             */
/*  1.0.1     8/ 1/2019  YK       Apply to CRI WARE's middle-ware type D1L1.                                                         */
/*  1.1.0     3/31/2020  TN       Implement DI/EI and apply coding rule.                                                             */
/*  1.1.1     9/ 8/2020  SK       Correct the way calculate DMAC registers address.(Fix the bug inherited from TY3S soft)            */
/*  1.2.0     6/10/2021  NK       Add CRI reset processing when DMA transfer error occurred.                                         */
/*  1.3.0    25/10/2024  KI       modify for BSW update.                                                                             */
/*  2.0.0     3/19/2025  SU       BEV                                                                                                */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * YK   = Yuuki Kato, Denso Techno                                                                                                */
/*  * TN   = Toshiharu Nagata, Denso Techno                                                                                          */
/*  * SK   = Sakae Kitamura, Denso Techno                                                                                            */
/*  * NK   = Naoki Kondo, Denso Techno                                                                                               */
/*  * KI   = Kanji Ito, DensoTechno                                                                                                  */
/*  * SU   = Shin Uchida, DensoTechno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
