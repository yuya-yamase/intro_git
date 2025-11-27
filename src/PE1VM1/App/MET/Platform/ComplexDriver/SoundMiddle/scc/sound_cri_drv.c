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
#warning "BEVCDCFD-2209"
#if 0 /* BEVCDCFD-2209 */
#include <v800_ghs.h>           /* GHS: Intrinsic Functions */
#else /* BEVCDCFD-2209 */
#endif /* BEVCDCFD-2209 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#include "aip_common.h"
#include "sound_cri_drv.h"

/* CRI header file */
#include "cri_xpt.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "def_reg.h"            /* レジスタ定義 */
#include "def_hw.h"             /* ハードウェア設定 */
#include "Port.h"
#include "Dma.h"
#include "pwm_drv.h"
#include "gpt_drv_d16.h"
#include "gpt_drv_j32.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/* MCAL */
#include "Dma.h"
#if 0   /* BEV BSW provisionally */
#include "gpt_drv_j32.h"
#else
#include "gpt_drv_j32_channel_STUB.h"
#include "dma_drv_STUB.h"
#endif
#include "int_drv.h"

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
/* タイマ値の取得 */
#define RSRC_GET_TIMER_COUNT()              ( REG_TAUJ0.TAUJnCNTm[0].U32)
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
static const U2     u2_sp_CARSPDPLS_OPEN_TAUD_START[GPT_D16_START_NUM_CFG] = {
    (U2)GPT_D16_START_CTRL_BIT_TRG_ST,
    (U2)GPT_D16_PERI_MAX
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 一斉書き換え許可状態トリガ用変数
 * [SPEC] RsrcDrv_DmacStart関数で初期化された後、
 *        この変数はDMA転送対象として保持し続ける必要があります。
 *        静的記憶領域に配置する必要がありますのでご注意ください。
 */
static CriUint16 s_rsrc_taud0_rdt_value;

/*  * 16bitレジスタダミーリード（同期用）* */
static CriUint16 rsrc_dummy_read16(volatile CriUint16 *p)
{
    register CriUint16 d;
    d = *p;
    return d;
}
/* * 8bitレジスタダミーリード（同期用）* */
static CriUint8 rsrc_dummy_read8(volatile CriUint8 *p)
{
    register CriUint8 d;
    d = *p;
    return d;
}

/*
 * ディスクリプタIDからポインタを取得
 */
static CriUint32 get_descriptor_ptr_from_id(CriSfrDrvDescriptorId descriptor_id)
{
    switch (descriptor_id)
    {
        case CRISFRDRVDESCRIPTORID_P_0:
            return HW_DESCRIPTOR_PTR_CH_P_0;
        case CRISFRDRVDESCRIPTORID_N_0: 
            return HW_DESCRIPTOR_PTR_CH_N_0;
        case CRISFRDRVDESCRIPTORID_P_1:
            return HW_DESCRIPTOR_PTR_CH_P_1;
        case CRISFRDRVDESCRIPTORID_N_1:
            return HW_DESCRIPTOR_PTR_CH_N_1;
        default:
            return HW_DESCRIPTOR_PTR_CH_P_0;
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
    REG_TAUJ0.TAUJnTT.U8 = 0x1U;

    REG_TAUJ0.TAUJnCDRm[0].U32 = 0xFFFFFFFFU;

    REG_TAUJ0.TAUJnTS.U8 = 0x1U;

    /* Synchronization */
    rsrc_dummy_read8(&REG_TAUJ0.TAUJnTS.U8);
    __SYNCP();
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
    vd_g_Gpt_J32Stop(GPT_J32_UN_0_CH_00);
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
    return RSRC_GET_TIMER_COUNT();
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
    CriUint32 descriptor_ptr_P;
    CriUint32 descriptor_ptr_N;

    descriptor_ptr_P = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_P]);
    descriptor_ptr_N = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_N]);

    /* 一斉書き換え許可状態トリガ用変数 
     * HW_TAUD_CH_MASTERのRDTレジスタに転送する定数を定義
     */
    s_rsrc_taud0_rdt_value = (0x1U << HW_TAUD_CH_MASTER)
                            | (0x1U << HW_TAUD_CH_SLAVE_P)
                            | (0x1U << HW_TAUD_CH_SLAVE_N); 


    /* DMA Operation Register */
    REG_DMAC.global.DMAjOR.U16 = 0x0001U;   /* DME[0]: DMA Master Enable */

    /************************************************************************
     * 7.7.4 Setting up the DMA channel setting
     ************************************************************************/
    /* (1) Disabling the DMAC channel operation */
    /* DMA Channel Control Register */
    REG_DMAC.channel[HW_DMAC_CH_P].DMAjCHCR.U16 = 0x0000U;
    REG_DMAC.channel[HW_DMAC_CH_N].DMAjCHCR.U16 = 0x0000U;
    REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjCHCR.U16 = 0x0000U;

    /* (3) Setting up the DMA transfer request */
    /* DMA Transfer Mode Register (DMAjTMR) */
    REG_DMAC.channel[HW_DMAC_CH_P].DMAjTMR.U32 = 
        0U << 20U |         /* SLM[3:0]: DMA Transfer Slow Speed mode (Normal Mode) */
        0U << 16U |         /* PRI[3:0]: Channel Request Priority Setting (disabled) */
        1U << 12U |         /* TRS[0]:   Transfer Request Soure (Hardware request) */
        0U << 10U |         /* DM[1:0]:  Destination Address Mode (Fixed) */
        1U << 8U  |         /* SM[1:0]:  Source Address Mode (Incremented) */
        1U << 4U  |         /* DTS[3:0]: DMA Destination Transaction Size (2-byte unit transfer) */
        1U << 0U  ;         /* STS[3:0]: DMA Source Transaction Size (2-byte unit transfer) */
    REG_DMAC.channel[HW_DMAC_CH_N].DMAjTMR.U32 = 
        0U << 20U |         /* SLM[3:0]: DMA Transfer Slow Speed mode (Normal Mode) */
        0U << 16U |         /* PRI[3:0]: Channel Request Priority Setting (disabled) */
        1U << 12U |         /* TRS[0]:   Transfer Request Soure (Hardware request) */
        0U << 10U |         /* DM[1:0]:  Destination Address Mode (Fixed) */
        1U << 8U  |         /* SM[1:0]:  Source Address Mode (Incremented) */
        1U << 4U  |         /* DTS[3:0]: DMA Destination Transaction Size (2-byte unit transfer) */
        1U << 0U  ;         /* STS[3:0]: DMA Source Transaction Size (2-byte unit transfer) */
    REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjTMR.U32 = 
        0U << 20U |         /* SLM[3:0]: DMA Transfer Slow Speed mode (Normal Mode) */
        0U << 16U |         /* PRI[3:0]: Channel Request Priority Setting (disabled) */
        1U << 12U |         /* TRS[0]:   Transfer Request Soure (Hardware request) */
        0U << 10U |         /* DM[1:0]:  Destination Address Mode (Fixed) */
        0U << 8U  |         /* SM[1:0]:  Source Address Mode (Fixed) */
        1U << 4U  |         /* DTS[3:0]: DMA Destination Transaction Size (2-byte unit transfer) */
        1U << 0U  ;         /* STS[3:0]: DMA Source Transaction Size (2-byte unit transfer) */

    /* DMA Resource Select Register (DMAjRS) */
    REG_DMAC.channel[HW_DMAC_CH_P].DMAjRS.U32 = 
        1U << 16U |                 /* TC[15:0]: Transfer Count per hardware request (Buffer array num) */
        0U << 12U |                 /* TL[2:0]: Transfer limit per hardware request (DMAjTMR.DTS*DMAjRS.TC) */
        0U << 11U |                 /* FPT[0]: First pre-load trigger (When DE is set to 1) */
        0U << 10U |                 /* PLE[0]: Pre-load enable (Disable) */
        0U << 9U  |                 /* DRQI[0]: DMA request initialization when descriptor settings are loaded (DRQ initialize disabled) */
        HW_DMAC_TRANSFER_TRIGGER << 0U; /* RS[7:0]: DMA request source */
    REG_DMAC.channel[HW_DMAC_CH_N].DMAjRS.U32 = 
        1U << 16U |                 /* TC[15:0]: Transfer Count per hardware request (Buffer array num) */
        0U << 12U |                 /* TL[2:0]: Transfer limit per hardware request (DMAjTMR.DTS*DMAjRS.TC) */
        0U << 11U |                 /* FPT[0]: First pre-load trigger (When DE is set to 1) */
        0U << 10U |                 /* PLE[0]: Pre-load enable (Disable) */
        0U << 9U  |                 /* DRQI[0]: DMA request initialization when descriptor settings are loaded (DRQ initialize disabled) */
        HW_DMAC_TRANSFER_TRIGGER << 0U; /* RS[7:0]: DMA request source */
    REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjRS.U32 = 
        1U << 16U |                 /* TC[15:0]: Transfer Count per hardware request (Buffer array num) */
        0U << 12U |                 /* TL[2:0]: Transfer limit per hardware request (DMAjTMR.DTS*DMAjRS.TC) */
        0U << 11U |                 /* FPT[0]: First pre-load trigger (When DE is set to 1) */
        0U << 10U |                 /* PLE[0]: Pre-load enable (Disable) */
        0U << 9U  |                 /* DRQI[0]: DMA request initialization when descriptor settings are loaded (DRQ initialize disabled) */
        HW_DMAC_TRANSFER_TRIGGER << 0U; /* RS[7:0]: DMA request source */

    /************************************************************************
     * 7.4.6 Descriptors
     ************************************************************************/
    /* Ref > (4) Example of descriptor (d) Example4 */
    /* DMA Descriptor Control Register n (DMAjDPCR_n) */
    REG_DMAC.channel[HW_DMAC_CH_P].DMAjDPCR.U32 = 
        7U << 0U ;      /* UPF[10:0]: Update flag of Descriptor (Enable Updating DMAjSAR_n, DMAjDAR and DMAjTSR_n)*/
    REG_DMAC.channel[HW_DMAC_CH_N].DMAjDPCR.U32 = 
        7U << 0U ;      /* UPF[10:0]: Update flag of Descriptor (Enable Updating DMAjSAR_n, DMAjDAR and DMAjTSR_n)*/
    REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjDPCR.U32 = 
        7U << 0U ;      /* UPF[10:0]: Update flag of Descriptor (Enable Updating DMAjSAR_n, DMAjDAR and DMAjTSR_n)*/

    /* DMA Descriptor Pointer Register n (DMAjDPPTR_n) */
    REG_DMAC.channel[HW_DMAC_CH_P].DMAjDPPTR.U32 = 
        descriptor_ptr_P << 2U |                    /* PTR[11:2]:Address pointer of Descriptor */
        0U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (disable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */
    REG_DMAC.channel[HW_DMAC_CH_N].DMAjDPPTR.U32 = 
        descriptor_ptr_N << 2U |                    /* PTR[11:2]:Address pointer of Descriptor */
        1U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (enable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */
    REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjDPPTR.U32 = 
        HW_DESCRIPTOR_PTR_CH_MASTER_0 << 2U |       /* PTR[11:2]:Address pointer of Descriptor */
        0U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (disable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */
    
    /* HW_DESCRIPTOR_CH_P_0 SAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_0].U32 = src_addr_tbl[CRISFRDRVDMACH_P];
    /* HW_DESCRIPTOR_CH_P_0 DAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_0 + 1U].U32 = HW_TAUD_CH_SLAVE_P_CDR_ADDR;
    /* HW_DESCRIPTOR_CH_P_0 TSR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_0 + 2U].U32 = transfer_count * HW_DMAC_BYTE_SIZE_PER_TRANSFER;
    /* HW_DESCRIPTOR_CH_P_0 DPPTR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_0 + 3U].U32 = 
        HW_DESCRIPTOR_PTR_CH_P_1 << 2U |            /* PTR[11:2]:Address pointer of Descriptor */
        0U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (disable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */

    /* HW_DESCRIPTOR_CH_P_1 SAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_1].U32 = src_addr_tbl[CRISFRDRVDMACH_P];
    /* HW_DESCRIPTOR_CH_P_1 DAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_1 + 1U].U32 = HW_TAUD_CH_SLAVE_P_CDR_ADDR;
    /* HW_DESCRIPTOR_CH_P_1 TSR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_1 + 2U].U32 = transfer_count * HW_DMAC_BYTE_SIZE_PER_TRANSFER;
    /* HW_DESCRIPTOR_CH_P_1 DPPTR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_P_1 + 3U].U32 = 
        HW_DESCRIPTOR_PTR_CH_P_0 << 2U |            /* PTR[11:2]:Address pointer of Descriptor */
        0U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (disable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */

    /* HW_DESCRIPTOR_CH_N_0 SAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_0].U32 = src_addr_tbl[CRISFRDRVDMACH_N];
    /* HW_DESCRIPTOR_CH_N_0 DAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_0 + 1U].U32 = HW_TAUD_CH_SLAVE_N_CDR_ADDR;
    /* HW_DESCRIPTOR_CH_N_0 TSR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_0 + 2U].U32 = transfer_count * HW_DMAC_BYTE_SIZE_PER_TRANSFER;
    /* HW_DESCRIPTOR_CH_N_0 DPPTR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_0 + 3U].U32 = 
        HW_DESCRIPTOR_PTR_CH_N_1 << 2U |            /* PTR[11:2]:Address pointer of Descriptor */
        1U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (enable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */

    /* HW_DESCRIPTOR_CH_N_1 SAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_1].U32 = src_addr_tbl[CRISFRDRVDMACH_N];
    /* HW_DESCRIPTOR_CH_N_1 DAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_1 + 1U].U32 = HW_TAUD_CH_SLAVE_N_CDR_ADDR;
    /* HW_DESCRIPTOR_CH_N_1 TSR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_1 + 2U].U32 = transfer_count * HW_DMAC_BYTE_SIZE_PER_TRANSFER;
    /* HW_DESCRIPTOR_CH_N_1 DPPTR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_N_1 + 3U].U32 = 
        HW_DESCRIPTOR_PTR_CH_N_0 << 2U |            /* PTR[11:2]:Address pointer of Descriptor */
        1U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (enable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */

    /* HW_DESCRIPTOR_CH_MASTER_0 SAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_MASTER_0].U32 = (CriUint32)(&s_rsrc_taud0_rdt_value);
    /* HW_DESCRIPTOR_CH_MASTER_0 DAR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_MASTER_0 + 1U].U32 = HW_TAUD_RDT_ADDR;
    /* HW_DESCRIPTOR_CH_MASTER_0 TSR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_MASTER_0 + 2U].U32 = HW_DMAC_CH_MASTER_TRNSFR_BYTE_SIZE;
    /* HW_DESCRIPTOR_CH_MASTER_0 DPPTR */
    REG_DESCRIPTOR.DESCRIPTOR[HW_DESCRIPTOR_PTR_CH_MASTER_0 + 3U].U32 = 
        HW_DESCRIPTOR_PTR_CH_MASTER_0 << 2U |       /* PTR[11:2]:Address pointer of Descriptor */
        0U << 1U |                                  /* DIE[1]   :Descriptor interrupt enable (disable) */
        1U << 0U ;                                  /* CF[1]    :Continuation flag of descriptor */

    /* (4) Clearing the transfer status */
    /* DMA Channel Flag Clear Register (DMAjCHFCR) */
    REG_DMAC.channel[HW_DMAC_CH_P].DMAjCHFCR.U32 = 
        1U << 13U |     /* OVFC[0]: Hardware transfer request overflow flag clear */
        1U << 12U |     /* DRQC[0]: Hardware transfer request clear */
        1U << 9U  |     /* DPEC[0]: Descriptor enable clear */
        1U << 3U  |     /* CAEC[0]: Address error flag clear */
        1U << 2U  |     /* DSEC[0]: Desctiptor step end flag clear */
        1U << 1U  |     /* TEC[0] : Transfer end flag clear */
        1U << 0U  ;     /* DEC[0] : DMA enable clear */
    REG_DMAC.channel[HW_DMAC_CH_N].DMAjCHFCR.U32 = 
        1U << 13U |     /* OVFC[0]: Hardware transfer request overflow flag clear */
        1U << 12U |     /* DRQC[0]: Hardware transfer request clear */
        1U << 9U  |     /* DPEC[0]: Descriptor enable clear */
        1U << 3U  |     /* CAEC[0]: Address error flag clear */
        1U << 2U  |     /* DSEC[0]: Desctiptor step end flag clear */
        1U << 1U  |     /* TEC[0] : Transfer end flag clear */
        1U << 0U  ;     /* DEC[0] : DMA enable clear */
    REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjCHFCR.U32 = 
        1U << 13U |     /* OVFC[0]: Hardware transfer request overflow flag clear */
        1U << 12U |     /* DRQC[0]: Hardware transfer request clear */
        1U << 9U  |     /* DPEC[0]: Descriptor enable clear */
        1U << 3U  |     /* CAEC[0]: Address error flag clear */
        1U << 2U  |     /* DSEC[0]: Desctiptor step end flag clear */
        1U << 1U  |     /* TEC[0] : Transfer end flag clear */
        1U << 0U  ;     /* DEC[0] : DMA enable clear */

        
    /* (5) Enabling the DMAC channel operation */
    /* DMA Channel Control Register (DMAjCHCR) */
    REG_DMAC.channel[HW_DMAC_CH_P].DMAjCHCR.U16 = 
        1U << 9U |      /* DPE[1]: Descriptor Enable bit: 1(Enable) */
        1U << 8U |      /* DPB[1]: Descriptor start bit: 1 (Enable) */
        0U << 4U |      /* CAEE[1]: (not use) */
        0U << 3U |      /* CAIE[1]: (not use) */
        0U << 2U |      /* DSIE[1]: Descriptor step end interrupt master enable: 0 (disable) */
        0U << 1U |      /* IE[1]: (not use) */
        1U << 0U ;      /* DE[1]: DMA Enable */
    REG_DMAC.channel[HW_DMAC_CH_N].DMAjCHCR.U16 = 
        1U << 9U |      /* DPE[1]: Descriptor Enable bit: 1(Enable) */
        1U << 8U |      /* DPB[1]: Descriptor start bit: 1 ("Enable") */
        0U << 4U |      /* CAEE[1]: (not use) */
        0U << 3U |      /* CAIE[1]: (not use) */
        1U << 2U |      /* DSIE[1]: Descriptor step end interrupt master enable: 1 (Enable) */
        0U << 1U |      /* IE[1]: (not use) */
        1U << 0U ;      /* DE[1]: DMA Enable */
    REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjCHCR.U16 = 
        1U << 9U |      /* DPE[1]: Descriptor Enable bit: 0(Disable) */
        1U << 8U |      /* DPB[1]: Descriptor start bit: 1 (Enable) */
        0U << 4U |      /* CAEE[1]: (not use) */
        0U << 3U |      /* CAIE[1]: (not use) */
        0U << 2U |      /* DSIE[1]: Descriptor step end interrupt master enable: 0 (disable) */
        0U << 1U |      /* IE[1]: (not use) */
        1U << 0U ;      /* DE[1]: DMA Enable */

    /* Synchronization */
    rsrc_dummy_read16(&REG_DMAC.channel[HW_DMAC_CH_MASTER].DMAjCHCR.U16);
    __SYNCP();
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
    CriUint32 descriptor_ptr_P;
    CriUint32 descriptor_ptr_N;

    descriptor_ptr_P = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_P]);
    descriptor_ptr_N = get_descriptor_ptr_from_id(descriptor_id_tbl[CRISFRDRVDMACH_N]);

    /************************************************************************
     * 7.4.6 Descriptors
     ************************************************************************/
    /* SAR */
    REG_DESCRIPTOR.DESCRIPTOR[descriptor_ptr_P].U32 = reload_src_addr_tbl[CRISFRDRVDMACH_P];
    /* TSR */
    REG_DESCRIPTOR.DESCRIPTOR[descriptor_ptr_P + 2U].U32 = transfer_count * HW_DMAC_BYTE_SIZE_PER_TRANSFER;

    /* SAR */
    REG_DESCRIPTOR.DESCRIPTOR[descriptor_ptr_N].U32 = reload_src_addr_tbl[CRISFRDRVDMACH_N];
    /* TSR */
    REG_DESCRIPTOR.DESCRIPTOR[descriptor_ptr_N + 2U].U32 = transfer_count * HW_DMAC_BYTE_SIZE_PER_TRANSFER;
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
    Dma_DisableTrans(DMA_CH_DATA_ID_6);
    Dma_DisableTrans(DMA_CH_DATA_ID_7);
    Dma_DisableTrans(DMA_CH_DATA_ID_8);
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
    __SYNCP();
    __DI();
    __SYNCP();
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
    __SYNCP();
    __EI();
    __SYNCP();
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
    /* TAUD1ペリフェラルガードの解除 */
    REG_PBGERRSLV50.PBGKCPROT.U32 = 0xA5A5A501U;
    REG_PBG51.PBGPROT0_2.U32 = 0x00000043U;

    vd_g_Gpt_D16Start((U1)GPT_D16_UN_1_CH_0_DD_PWM_M, &u2_sp_CARSPDPLS_OPEN_TAUD_START[0]);
    vd_g_Gpt_D16Start((U1)GPT_D16_UN_1_CH_1_DD_PWM_S, &u2_sp_CARSPDPLS_OPEN_TAUD_START[0]);
    vd_g_Gpt_D16Start((U1)GPT_D16_UN_1_CH_2_DD_PWM_S, &u2_sp_CARSPDPLS_OPEN_TAUD_START[0]);


    REG_TAUD1.TAUDnCDRm[HW_TAUD_CH_MASTER].U16 = master_CDR;
    REG_TAUD1.TAUDnCDRm[HW_TAUD_CH_SLAVE_P].U16 = slave_CDR;
    REG_TAUD1.TAUDnCDRm[HW_TAUD_CH_SLAVE_N].U16 = slave_CDR;

    /************************************************************************
     * 33.4 Operating Procedure
     ************************************************************************/
    /* TAUDn Channel Start Trigger Register */
    REG_TAUD1.TAUDnTS.U16 = 
        1U << HW_TAUD_CH_MASTER  |
        1U << HW_TAUD_CH_SLAVE_P |
        1U << HW_TAUD_CH_SLAVE_N ;

    /* Synchronization */
    rsrc_dummy_read16(&REG_TAUD1.TAUDnCDRm[HW_TAUD_CH_SLAVE_N].U16);
    __SYNCP();
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
    /************************************************************************
     * 33.4 Operating Procedure
     ************************************************************************/
    /* TAUDn Channel Stop Trigger Register */
    REG_TAUD1.TAUDnTT.U16 = 
        1U << HW_TAUD_CH_MASTER  |
        1U << HW_TAUD_CH_SLAVE_P |
        1U << HW_TAUD_CH_SLAVE_N ;

    /* Synchronization */
    rsrc_dummy_read16(&REG_TAUD1.TAUDnTT.U16);
    __SYNCP();

    vd_g_Gpt_D16Stop((U1)GPT_D16_UN_1_CH_0_DD_PWM_M);
    vd_g_Gpt_D16Stop((U1)GPT_D16_UN_1_CH_1_DD_PWM_S);
    vd_g_Gpt_D16Stop((U1)GPT_D16_UN_1_CH_2_DD_PWM_S);
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
