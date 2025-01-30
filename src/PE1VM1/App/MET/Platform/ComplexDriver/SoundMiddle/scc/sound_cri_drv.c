/* 1.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Sound Middleware (CRI) Driver                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_CRI_DRV_C_MAJOR                        (1)
#define SOUND_CRI_DRV_C_MINOR                        (2)
#define SOUND_CRI_DRV_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "sound_cri_drv.h"

/* CRI header file */
#include "cri_xpt.h"
#include "cri_atom_rh850d1.h"

/* MCAL */
#include "dma_drv.h"
#include "gpt_drv_j32.h"
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
#define SOUND_CRI_DRV_TAUJ_CH           (GPT_J32_UN_CH_SOUND_CRI)               /* TAUJ channel used by CRI middleware               */

#define SOUND_CRI_DRV_PCMP0             ((volatile ST_SOUND_CRI_DRV_REGPCMP *)0xFFF10000U)        /* Head address of the PCMP0 registers */
#define SOUND_CRI_DRV_DMA_CHANNEL_HEAD  ((volatile ST_SOUND_CRI_DRV_REGDMACCHANNEL *)0xFFFF8400U) /* Head address of the DMAC registers  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* PCMP registers */
typedef struct CriRegPcmpTag
{
    CriUint32 u4_ctl;                                                           /* [+0x00] PCM-PWM control register                  */
    CriUint32 u4_tpwm;                                                          /* [+0x04] PCM-PWM counter period register           */
    CriUint32 u4_inv;                                                           /* [+0x08] PCM-PWM inverter control register         */
    CriUint32 u4_stlv;                                                          /* [+0x0C] PCM-PWM static level selection register   */

    CriUint32 u4_sten;                                                          /* [+0x10] PCM-PWM static level enable register      */
    CriUint32 u4_offs;                                                          /* [+0x14] PCM-PWM conversion offset register        */
    CriUint32 u4_ausa;                                                          /* [+0x18] PCM-PWM audio sample input register       */
    CriUint32 u4_str;                                                           /* [+0x1C] PCM-PWM status register                   */

    CriUint32 u4_stc;                                                           /* [+0x20] PCM-PWM status clear register             */
    CriUint32 u4_cksel;                                                         /* [+0x24] PCM-PWM clock selection register          */
    CriUint32 u4_emu;                                                           /* [+0x28] PCM-PWM emulation register                */
    CriUint32 u4_dummy_2c;                                                      /* [+0x2C] (dummy padding)                           */
} ST_SOUND_CRI_DRV_REGPCMP;

/* DMAC channel registers */
typedef struct RegDmacChannelTag
{
    CriUint32 u4_dsan;                                                          /* [+0x00] DMAC source address                       */
    CriUint32 u4_ddan;                                                          /* [+0x04] DMAC destination address                  */
    CriUint32 u4_dtcn;                                                          /* [+0x08] DMAC transfer count                       */
    CriUint32 u4_dtctn;                                                         /* [+0x0C] DMAC transfer control                     */

    CriUint32 u4_drsan;                                                         /* [+0x10] DMAC reload source address                */
    CriUint32 u4_drdan;                                                         /* [+0x14] DMAC reload destination address           */
    CriUint32 u4_drtcn;                                                         /* [+0x18] DMAC reload transfer count                */
    CriUint32 u4_dtccn;                                                         /* [+0x1C] DMAC transfer count compare               */

    CriUint32 u4_dcenn;                                                         /* [+0x20] DMAC channel operation enable setting     */
    CriUint32 u4_dcstn;                                                         /* [+0x24] DMAC transfer status                      */
    CriUint32 u4_dcstsn;                                                        /* [+0x28] DMAC transfer status set                  */
    CriUint32 u4_dcstcn;                                                        /* [+0x2C] DMAC transfer status clear                */

    CriUint32 u4_dtfrn;                                                         /* [+0x30] DTFR setting                              */
    CriUint32 u4_dtfrrqn;                                                       /* [+0x34] DTFR transfer request status              */
    CriUint32 u4_dtfrrqcn;                                                      /* [+0x38] DTFR transfer request clear               */
    CriUint32 u4_dummy_3c;                                                      /* [+0x3C] (dummy padding)                           */
} ST_SOUND_CRI_DRV_REGDMACCHANNEL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4 u4_sp_soundmiddle_dmadata[DMA_CFG_CH_NUM_WORD];                       /* DMAC data for enabling                            */

static U1 u1_s_soundmiddle_under_di;                                            /* Under interrupt                                   */
static U4 u4_s_soundmiddle_gli;                                                 /* Return value of u4_g_IRQ_DI function              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  Initial process                                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvInitialize(void)
{
    u1_s_soundmiddle_under_di = (U1)FALSE;
    u4_s_soundmiddle_gli      = (U4)0U;
}

/*===================================================================================================================================*/
/*  Timer start process                                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvTimerInitialize(void)
{
    U4  u4_tp_j32[GPT_J32_START_NUM_CFG];

    u4_tp_j32[GPT_J32_START_CTRL] = (U4)GPT_J32_START_CTRL_BIT_TRG_ST;
    u4_tp_j32[GPT_J32_START_PERI] = (U4)0U;

    /* Stop -> Start the channel */
    vd_g_Gpt_J32Stop((U1)SOUND_CRI_DRV_TAUJ_CH);
    vd_g_Gpt_J32Start((U1)SOUND_CRI_DRV_TAUJ_CH, &u4_tp_j32[0U]);
}


/*===================================================================================================================================*/
/*  timer stop process                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvTimerFinalize(void)
{
    vd_g_Gpt_J32Stop((U1)SOUND_CRI_DRV_TAUJ_CH);
}

/*===================================================================================================================================*/
/*  Get timer count process                                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
CriUint32 u4_g_SoundCriDrvTimerGetCount(void)
{
    return ((CriUint32)u4_g_Gpt_J32GetTimeElapsed((U1)SOUND_CRI_DRV_TAUJ_CH, vdp_PTR_NA));
}

/*===================================================================================================================================*/
/*  DMAC initialize process                                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvDmacInitialize(const CriUint32 u4_a_READ_HEAD, const CriUint32 u4_a_READ_SIZE)
{
    /* Set DMAC master and/or PEG if necessary. */
}


/*===================================================================================================================================*/
/*  DMAC finalize process                                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvDmacFinalize(void)
{
    /* Reset DMAC master and/or PEG if necessary. */
}

/*===================================================================================================================================*/
/*  DMAC start process(SoftwareTrigger)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Note:dma_drv.c                                                                                                                   */
/*       Caution:Don't call u4_g_DmaEnaCh and vd_g_DmaDisCh of the same channel at the same time, to prevent resource collision.     */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvDmacStart(const CriUint32 u4_a_DSA, const CriUint32 u4_a_DDA, const CriUint32 u4_a_DTC, const CriUint32 u4_a_DTCT,
                               const CriUint32 u4_a_DRSA, const CriUint32 u4_a_DRDA, const CriUint32 u4_a_DRTC, const CriUint32 u4_a_DTCC, const CriUint32 u4_a_DTFR)
{
    U4  u4_t_stsbit;

    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_SRC]  = u4_a_DSA;                 /* DMAC Source Address Register (DSAn)               */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_DST]  = u4_a_DDA;                 /* DMAC Destination Address Register (DDAn)          */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DTC]  = u4_a_DTC;                 /* DMAC Transfer Count Register (DTCn)               */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DTCT] = u4_a_DTCT;                /* DMAC Transfer Control Register (DTCTn)            */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_RSRC] = u4_a_DRSA;                /* DMAC Reload Source Address Register (DRSAn)       */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_RDST] = u4_a_DRDA;                /* DMAC Reload Destination Address Register (DRDAn)  */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DRTC] = u4_a_DRTC;                /* DMAC Reload Transfer Count Register (DRTCn)       */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DTCC] = u4_a_DTCC;                /* DMAC Transfer Count Compare Register (DTCCn)      */

    /*vd_g_DmaDisCh(SOUND_CRI_DRV_DMA_CH);*/
    u4_t_stsbit = u4_g_DmaEnaCh((U1)SOUND_CRI_DRV_DMA_CH, &u4_sp_soundmiddle_dmadata[0U]);
    if((u4_t_stsbit & (U4)DMA_STSBIT_HLT) == (U4)DMA_STSBIT_HLT){
        (void)u4_g_DmaEnaCh((U1)SOUND_CRI_DRV_DMA_CH, &u4_sp_soundmiddle_dmadata[0U]); /* Retry(See. PCS-V)                          */
    }

    /*vd_g_DmaSwTrgrTx(SOUND_CRI_DRV_DMA_CH);*/
}

/*===================================================================================================================================*/
/*  DMAC interrupt process(IntHandler)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvDmacInterrupt(void)
{
    criAtomEx_ExecServerIntr_Rh850d1();
}

/*===================================================================================================================================*/
/*  DMAC interrupt process(CRI Library)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvDmacIntr(const CriUint32 u4_a_DRSA, const CriUint32 u4_a_DRDA, const CriUint32 u4_a_DRTC)
{
    volatile ST_SOUND_CRI_DRV_REGDMACCHANNEL *st_tp_reg_dmac_ch = SOUND_CRI_DRV_DMA_CHANNEL_HEAD;

    /* Clear all of transfer flags */
    st_tp_reg_dmac_ch[SOUND_CRI_DRV_DMA_CH].u4_dcstcn = (U4)0x000000B1U;

    /* Set reload registers */
    st_tp_reg_dmac_ch[SOUND_CRI_DRV_DMA_CH].u4_drsan  = u4_a_DRSA;
    st_tp_reg_dmac_ch[SOUND_CRI_DRV_DMA_CH].u4_drdan  = u4_a_DRDA;
    st_tp_reg_dmac_ch[SOUND_CRI_DRV_DMA_CH].u4_drtcn  = u4_a_DRTC;
}

/*===================================================================================================================================*/
/*  DMAC stop process                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvDmacStop(void)
{
    vd_g_DmaDisCh((U1)SOUND_CRI_DRV_DMA_CH);

    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_SRC]  = (U4)0U;                   /* DMAC Source Address Register (DSAn)               */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_DST]  = (U4)0U;                   /* DMAC Destination Address Register (DDAn)          */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DTC]  = (U4)0U;                   /* DMAC Transfer Count Register (DTCn)               */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DTCT] = (U4)0U;                   /* DMAC Transfer Control Register (DTCTn)            */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_RSRC] = (U4)0U;                   /* DMAC Reload Source Address Register (DRSAn)       */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_ADDR_RDST] = (U4)0U;                   /* DMAC Reload Destination Address Register (DRDAn)  */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DRTC] = (U4)0U;                   /* DMAC Reload Transfer Count Register (DRTCn)       */
    u4_sp_soundmiddle_dmadata[DMA_CFG_CH_CTRL_DTCC] = (U4)0U;                   /* DMAC Transfer Count Compare Register (DTCCn)      */
}

/*===================================================================================================================================*/
/*  PCMP initialize process                                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvPcmpInitialize(const CriUint32 u4_a_TPWM, const CriUint32 u4_a_CKSEL, const CriUint32 u4_a_OFFS)
{
    /* PCMP0 */
    SOUND_CRI_DRV_PCMP0->u4_ctl   = (U4)0x00000000U;                            /* PCMPnENAB = Conversion disabled                   */
    SOUND_CRI_DRV_PCMP0->u4_tpwm  = u4_a_TPWM;
    SOUND_CRI_DRV_PCMP0->u4_cksel = u4_a_CKSEL;
    SOUND_CRI_DRV_PCMP0->u4_sten  = (U4)0x00000000U;                            /* PCMPnSTEN[11:8][3:0] = PWM signal output enabled  */
    SOUND_CRI_DRV_PCMP0->u4_stlv  = (U4)0x00000000U;                            /* PCMPnSTLV[11:8][3:0] = Static inactive            */
    SOUND_CRI_DRV_PCMP0->u4_inv   = (U4)0x00000000U;                            /* PCMPnINV[11:8][3:0] = Active low                  */
    SOUND_CRI_DRV_PCMP0->u4_offs  = u4_a_OFFS;

}


/*===================================================================================================================================*/
/*  PCMP finalize process                                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvPcmpFinalize(void)
{
    SOUND_CRI_DRV_PCMP0->u4_ctl = (U4)0x00000000U;                              /* PCMPnENAB = Conversion disabled                   */
}

/*===================================================================================================================================*/
/*  PCMP start process                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvPcmpStart(const CriUint32 u4_a_AUSA, const CriUint32 u4_a_CTRL)
{
    SOUND_CRI_DRV_PCMP0->u4_stc  = (U4)0x00000003U;                             /* Clear FIFO buffer flag                            */
    SOUND_CRI_DRV_PCMP0->u4_ausa = u4_a_AUSA;
    SOUND_CRI_DRV_PCMP0->u4_ausa = u4_a_AUSA;
    SOUND_CRI_DRV_PCMP0->u4_ctl  = u4_a_CTRL;
}

/*===================================================================================================================================*/
/*  PCMP stop process                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvPcmpStop(void)
{
    SOUND_CRI_DRV_PCMP0->u4_ctl = (U4)0x00000000U;                              /* PCMPnENAB = Conversion disabled                   */
}

/*===================================================================================================================================*/
/*  Interrupt disable process                                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvIntrDisable(void)
{
    if(u1_s_soundmiddle_under_di != (U1)TRUE){
        u4_s_soundmiddle_gli      = u4_g_IRQ_DI();
        u1_s_soundmiddle_under_di = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  Interrupt enable process                                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SoundCriDrvIntrEnable(void)
{
    if(u1_s_soundmiddle_under_di == (U1)TRUE){
        vd_g_IRQ_EI(u4_s_soundmiddle_gli);
        u1_s_soundmiddle_under_di = (U1)FALSE;
    }
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
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * YK   = Yuuki Kato, Denso Techno                                                                                                */
/*  * TN   = Toshiharu Nagata, Denso Techno                                                                                          */
/*  * SK   = Sakae Kitamura, Denso Techno                                                                                            */
/*  * NK   = Naoki Kondo, Denso Techno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
