/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_Int.c
 * [Module]			Int
 * [Function]		Int
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
/* #include <v800_ghs.h> */
#include <Std_Types.h>
#include <SS.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Int.h>

#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/

// typedef struct
// {
//     uint32 LRECCCTL;       /* 0x00 */
//     uint32 dummy04[3];     /* */
//     uint32 LRECCTSTCTL;    /* 0x10 */
//     uint32 dummy14[3];     /* */
//     uint32 LRAFINV;        /* 0x20 */
//     uint32 dummy24[3];     /* */
//     uint32 dummy30[4 * 3]; /* */
//     uint32 LRTDATBFECCF;   /* 0x60 */
//     uint32 dummy64[3];     /* */
//     uint32 dummy70[4];     /* */
// } REG_ST_ECCCNT_LR;

// typedef struct
// {
//     uint32 ERRINT;         /* 0x00 */
//     uint32 dummy04[3];     /* */
//     uint32 SSTCLR;         /* 0x10 */
//     uint32 DSTCLR;         /* 0x14 */
//     uint32 OVFCLR;         /* 0x18 */
//     uint32 dummy1c;        /* */
//     uint32 SERSTR;         /* 0x20 */
//     uint32 DERSTR;         /* 0x24 */
//     uint32 OVFSTR;         /* 0x28 */
//     uint32 dummy2c;        /* */
//     uint32 SERINF;         /* 0x30 */
//     uint32 dummy34[3];     /* */
//     uint32 dummy40[4 * 3]; /* */
//     uint32 _00SEADR;       /* 0x70 */
//     uint32 _01SEADR;       /* 0x74 */
//     uint32 _02SEADR;       /* 0x78 */
//     uint32 _03SEADR;       /* 0x7C */
//     uint32 dummy80[4 * 7]; /* */
//     uint32 _00DEADR;       /* 0xF0 */
//     uint32 dummyF4[3];     /* */
// } REG_ST_MECCCAP;

// typedef struct
// {
//     uint32 ERRINT;         /* 0x00 */
//     uint32 dummy04[3];     /* */
//     uint32 SSTCLR;         /* 0x10 */
//     uint32 DSTCLR;         /* 0x14 */
//     uint32 OVFCLR;         /* 0x18 */
//     uint32 dummy1c;        /* */
//     uint32 SERSTR;         /* 0x20 */
//     uint32 DERSTR;         /* 0x24 */
//     uint32 OVFSTR;         /* 0x28 */
//     uint32 dummy2c;        /* */
//     uint32 SERINF;         /* 0x30 */
//     uint32 dummy34[3];     /* */
//     uint32 dummy40[4 * 3]; /* */
//     uint32 _00SEADR;       /* 0x70 */
//     uint32 dummy74[3];     /* */
//     uint32 dummy80[4 * 7]; /* */
//     uint32 _00DEADR;       /* 0xF0 */
//     uint32 dummyF4[3];     /* */
// } REG_ST_MECCCAP_IC;

// typedef struct
// {
//     uint32 CRCAFCTL;       /* 0x00 */
//     uint32 dummy04[3];     /* */
//     uint32 CRCECCTSTCTL;   /* 0x10 */
//     uint32 dummy14[3];     /* */
//     uint32 CRCAFINV;       /* 0x20 */
//     uint32 dummy24[3];     /* */
//     uint32 dummy30[4 * 3]; /* */
//     uint32 CRCTDATBFECCF;  /* 0x60 */
//     uint32 dummy64[3];     /* */
//     uint32 dummy70[4];     /* */
// } REG_ST_ECCCNT_CR;

// typedef struct
// {
//     uint32 ERRINT;         /* 0x00 */
//     uint32 dummy04[3];     /* */
//     uint32 SSTCLR;         /* 0x10 */
//     uint32 DSTCLR;         /* 0x14 */
//     uint32 OVFCLR;         /* 0x18 */
//     uint32 dummy1c;        /* */
//     uint32 SERSTR;         /* 0x20 */
//     uint32 DERSTR;         /* 0x24 */
//     uint32 OVFSTR;         /* 0x28 */
//     uint32 dummy2c;        /* */
//     uint32 SERINF;         /* 0x30 */
//     uint32 dummy34[3];     /* */
//     uint32 dummy40[4 * 3]; /* */
//     uint32 _00SEADR;       /* 0x70 */
//     uint32 _01SEADR;       /* 0x74 */
//     uint32 _02SEADR;       /* 0x78 */
//     uint32 _03SEADR;       /* 0x7C */
//     uint32 _04SEADR;       /* 0x80 */
//     uint32 _05SEADR;       /* 0x84 */
//     uint32 _06SEADR;       /* 0x88 */
//     uint32 _07SEADR;       /* 0x8C */
//     uint32 dummy90[4 * 6]; /* */
//     uint32 _00DEADR;       /* 0xF0 */
//     uint32 dummyF4[3];     /* */
// } REG_ST_MECCCAP_CR;

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
// #define REG_u4CFPECCCTL(n) (*(volatile uint32 *)(0xFFC48000UL + ((n)*0x80UL)))
/* 例えば、ECCCNT_CFP_PE2CL1 なら、"REG_u4CFPECCCTL(2)"でアクセスする */

// #define REG_u4CFCECCCTL0 (*(volatile uint32 *)(0xFFC48800UL))
// #define REG_u4CFCECCCTL1 (*(volatile uint32 *)(0xFFC48880UL))
// #define REG_u4CFSECCCTL  (*(volatile uint32 *)(0xFFC48A00UL))

// #define REG_ptECCCNT_LR_PE ((volatile REG_ST_ECCCNT_LR *)(0xFFC49800UL))
/* 例えば、ECCCNT_LR_PE2CL1.LRECCCTL  なら、"REG_ptECCCNT_LR[2].LRECCCTL"でアクセスする */

// #define REG_ptMECCCAP_CFL ((volatile REG_ST_MECCCAP *)(0xFFC52400UL))
// #define REG_ptMECCCAP_LR0 ((volatile REG_ST_MECCCAP *)(0xFFC50000UL))
/* 例えば、MECCCAP_LR_PE2CL1.LR0_ERRINTなら、"REG_ptMECCCAP_LR[2].ERRINT"でアクセスする */

// #define REG_u4FEINTMSK(n) (*(volatile uint32 *)(0xFF9A3B04UL + ((n)*0x100UL)))

// #define REG_u4ECCKCPROT (*(volatile uint32 *)(0xFFFB2800UL))

// #define REG_u4ITECCCTL(n) (*(volatile uint32 *)(0xFFC49000UL + ((n)*0x80UL)))
// #define REG_u4IDECCCTL(n) (*(volatile uint32 *)(0xFFC49400UL + ((n)*0x80UL)))

// #define REG_ptMECCCAP_IT ((volatile REG_ST_MECCCAP_IC *)(0xFFC51000UL))
// #define REG_ptMECCCAP_ID ((volatile REG_ST_MECCCAP_IC *)(0xFFC51800UL))

/* for Code Flash */
// #define VAL_u4CFCECCCTL_B_AP_SECDED (0x00000000UL)
// #define VAL_u4ECCCTL_SECDED         (0x00000000UL)
// #define VAL_u4CF_ERRINT_OV_AF_DE    (0x00000086UL)

/* for Local RAM */
// #define VAL_u4ECCCTL_AF_SECDED    (0x00000000UL)
// #define VAL_u4LR0_ERRINT_OV_AF_DE (0x0000008AUL)

/* for ICache */
// #define VAL_u4ECCCTL_AF_ECC   (0x00000000UL)
// #define VAL_u4IT_ERRINT_AF_DE (0x0000000AUL)
// #define VAL_u4ID_ERRINT_AF_DE (0x0000000AUL)

/* for ClusterRAM */
// #define REG_u4CRAECCCTL    (*(volatile uint32 *)(0xFFC49E00UL))
// #define REG_ptECCCNT_CRCCL ((volatile REG_ST_ECCCNT_CR *)(0xFFC49C00UL))
// #define REG_ptMECCCAP_CRAM       ((volatile REG_ST_MECCCAP_CR *)(0xFFC52000UL))
// #define VAL_u4CR_ERRINT_OV_AF_DE (0x0000008AUL)

/* for common */
// #define VAL_u4LDSTCLR          (0x00000001UL)
// #define VAL_u4LOVFCLR_01       (0x00000003UL)
#define VAL_u4PEGKCPROT_UNLOCK (0xA5A5A501UL)
#define VAL_u4KCPROT_LOCK      (0xA5A5A500UL)

/* for FEINTMSK common */
// #define VAL_u4FEINTMSK_ENABLE_ECM (0x00000003UL)

/* for ECM common */
// #define BA_u4ECM (0xFFD38000UL)

/*
#define REG_u4ECMEPCFG (*(volatile uint32 *)(BA_u4ECM + 0UL))
*/
// #define REG_u4ECMISCFGj(j)      (*(volatile uint32 *)(BA_u4ECM + (j)*4UL + 4UL))
// #define REG_u4ECMINCFGi_j(i, j) (*(volatile uint32 *)(BA_u4ECM + (i)*0x3CUL + (j)*4UL + 0x40UL))
/*
#define REG_u4ECMIRCFGj(j)
#define REG_u4ECMEMKj(j)
#define REG_u4ECMETMKn_j(n, j)
*/
// #define REG_u4ECMESSTCj(j) (*(volatile uint32 *)(BA_u4ECM + (j)*4UL + 0x478UL))
// #define REG_u4ECMKCPROT    (*(volatile uint32 *)(BA_u4ECM + 0x4B4UL))
/*
#define REG_u4ECMPEj(j)
#define REG_u4ECMDTMCTL
#define REG_u4ECMDTMR
#define REG_u4ECMDTMCMP
#define REG_u4ECMDTMCFGj(j)
#define REG_u4ECMEOCCFG
#define REG_u4ECMETCCFGn(n)
#define REG_u4ECMPEM
*/

#define REG_u4PSW_regID ((int)5)
#define REG_u4PSW_selID ((int)0)

#define REG_u4PLMR_regID  ((int)14)
#define REG_u4PLMR_selID  ((int)2)
#define VAL_u4PLMR_CAT2DI ((unsigned int)1)

#define REG_u4PEGKCPROT_PE0 (*(volatile uint32 *)(0xFFC6C000UL + 0x00UL))
#define REG_u4PEGKCPROT_PE1 (*(volatile uint32 *)(0xFFC6C100UL + 0x00UL))
#define REG_u4PEGKCPROT_PE2 (*(volatile uint32 *)(0xFFC6C200UL + 0x00UL))
#define REG_u4PEGKCPROT_PE3 (*(volatile uint32 *)(0xFFC6C300UL + 0x00UL))

#define REG_u4PEGSPID_PE0 (*(volatile uint32 *)(0xFFC6C000UL + 0x44UL + (0UL * 0x10UL)))
#define REG_u4PEGSPID_PE1 (*(volatile uint32 *)(0xFFC6C100UL + 0x44UL + (0UL * 0x10UL)))
#define REG_u4PEGSPID_PE2 (*(volatile uint32 *)(0xFFC6C200UL + 0x44UL + (0UL * 0x10UL)))
#define REG_u4PEGSPID_PE3 (*(volatile uint32 *)(0xFFC6C300UL + 0x44UL + (0UL * 0x10UL)))

#define REG_u4PEGBAD_PE0 (*(volatile uint32 *)(0xFFC6C000UL + 0x48UL + (0UL * 0x10UL)))
#define REG_u4PEGBAD_PE1 (*(volatile uint32 *)(0xFFC6C100UL + 0x48UL + (0UL * 0x10UL)))
#define REG_u4PEGBAD_PE2 (*(volatile uint32 *)(0xFFC6C200UL + 0x48UL + (0UL * 0x10UL)))
#define REG_u4PEGBAD_PE3 (*(volatile uint32 *)(0xFFC6C300UL + 0x48UL + (0UL * 0x10UL)))

#define REG_u4PEGADV_PE0 (*(volatile uint32 *)(0xFFC6C000UL + 0x4CUL + (0UL * 0x10UL)))
#define REG_u4PEGADV_PE1 (*(volatile uint32 *)(0xFFC6C100UL + 0x4CUL + (0UL * 0x10UL)))
#define REG_u4PEGADV_PE2 (*(volatile uint32 *)(0xFFC6C200UL + 0x4CUL + (0UL * 0x10UL)))
#define REG_u4PEGADV_PE3 (*(volatile uint32 *)(0xFFC6C300UL + 0x4CUL + (0UL * 0x10UL)))

#define REG_u4PEGPROT_PE0 (*(volatile uint32 *)(0xFFC6C000UL + 0x40UL + (0UL * 0x10UL)))
#define REG_u4PEGPROT_PE1 (*(volatile uint32 *)(0xFFC6C100UL + 0x40UL + (0UL * 0x10UL)))
#define REG_u4PEGPROT_PE2 (*(volatile uint32 *)(0xFFC6C200UL + 0x40UL + (0UL * 0x10UL)))
#define REG_u4PEGPROT_PE3 (*(volatile uint32 *)(0xFFC6C300UL + 0x40UL + (0UL * 0x10UL)))

#define VAL_u4PEGSPID_PE0 (0x00000001UL) /* value of SPID:0 Bus master:CPU0 Register location:CPU0 */
#define VAL_u4PEGSPID_PE1 (0x00000002UL) /* value of SPID:1 Bus master:CPU1 Register location:CPU1 */
#define VAL_u4PEGSPID_PE2 (0x00000004UL) /* value of SPID:2 Bus master:CPU2 Register location:CPU2 */
#define VAL_u4PEGSPID_PE3 (0x00000008UL) /* value of SPID:3 Bus master:CPU3 Register location:CPU3 */

/* PegBaseAddress */
#define VAL_u4PEGBAD_LR0 (0xFDC00000UL)
#define VAL_u4PEGBAD_LR1 (0xFDA00000UL)
#define VAL_u4PEGBAD_LR2 (0xFD800000UL)
#define VAL_u4PEGBAD_LR3 (0xFD600000UL)

/* PegAddressValidBit */
#define VAL_u4PEGADV_LR0 (0x03FF0000UL)
#define VAL_u4PEGADV_LR1 (0x03FF0000UL)
#define VAL_u4PEGADV_LR2 (0x03FF0000UL)
#define VAL_u4PEGADV_LR3 (0x03FF0000UL)

/* PegProtectionControl */
#define VAL_u4PEGPROT_LR0 (0x00000140UL)
#define VAL_u4PEGPROT_LR1 (0x00000140UL)
#define VAL_u4PEGPROT_LR2 (0x00000140UL)
#define VAL_u4PEGPROT_LR3 (0x00000140UL)

// static inline void Ecu_Int_activateECMchAsFEINT(uint32 u4PE, uint32 u4Ch);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		static inline void Ecu_Int_activateECMchAsFEINT(uint32 u4PE, uint32 u4Ch)
 * [Function]	Error SourceをFEINT要因として有効化
 * [Arguments]	None
 * [Return]		None
 * [Notes]		第一引数の最大値はSS_USE_CORE_COUNT, 第二引数はHWMのTable 45.11 List of Error Inputsでサポートしているもののみとすること
 *--------------------------------------------------------------------------*/
// static inline void Ecu_Int_activateECMchAsFEINT(uint32 u4PE, uint32 u4Ch)
// {
//     uint32 u4_J;
//     uint32 u4BitPos;

//     u4_J     = u4Ch / 32UL;
//     u4BitPos = u4Ch % 32UL;

//     /* clear error status */
//     REG_u4ECMESSTCj(u4_J) = 1UL << u4BitPos; /* EDET_INT30 */

//     /* select FEINT */
//     REG_u4ECMISCFGj(u4_J) = 1UL << u4BitPos; /* EDET_INT30 */

//     /* enable notification */
//     REG_u4ECMINCFGi_j(u4PE, u4_J) = 1UL << u4BitPos; /* EDET_INT30 */

//     return;
// }

/**---------------------------------------------------------------------------
 * [Format]		void Ecu_Int_performReset(void)
 * [Function]	noUseInt or uC Exception caused, then reset uC
 * [Arguments]	None
 * [Return]		None
 * [Notes]		外部WDTでリセットしたいユースケースでは無限ループに変更すること
 *--------------------------------------------------------------------------*/
void Ecu_Int_performReset(void)
{
    SS_CpuCore_performReset();
}

// void Ecu_Int_destroyRamEcc(void)
// {
//     return;
// }

// void Ecu_Int_enableEcc(void)
// {
// uint32          u4PE;
// volatile uint32 u4Dummy;

// /* Unlock registers */
// REG_u4ECCKCPROT = VAL_u4KCPROT_UNLOCK;

/*
     * Code Flash
     */
/* clear error status */
// REG_ptMECCCAP_CFL[0].DSTCLR = VAL_u4LDSTCLR;
// REG_ptMECCCAP_CFL[0].OVFCLR = VAL_u4LOVFCLR_01;

/* Enable ECC Enc/Dec, parity Check */
// for (u4PE = 0; u4PE < SS_USE_CORE_COUNT; u4PE++)
// {
//     REG_u4CFPECCCTL(u4PE) = VAL_u4ECCCTL_SECDED; /* EDET_INT30 */
// }
// REG_u4CFCECCCTL0 = VAL_u4CFCECCCTL_B_AP_SECDED;
// REG_u4CFCECCCTL1 = VAL_u4CFCECCCTL_B_AP_SECDED;
// REG_u4CFSECCCTL  = VAL_u4ECCCTL_SECDED;

/* Enable ECC Err and parity Err Reporitng */
// REG_ptMECCCAP_CFL[0].ERRINT = VAL_u4CF_ERRINT_OV_AF_DE;

/*
     * Local RAM
     */
// for (u4PE = 0; u4PE < SS_USE_CORE_COUNT; u4PE++)
// {
//     /* clear error status */
//     REG_ptMECCCAP_LR0[u4PE].DSTCLR = VAL_u4LDSTCLR;
//     REG_ptMECCCAP_LR0[u4PE].OVFCLR = VAL_u4LOVFCLR_01;

//     /* Enable ECC Enc/Dec, parity Check */
//     REG_ptECCCNT_LR_PE[u4PE].LRECCCTL = VAL_u4ECCCTL_AF_SECDED;

//     /* disable test mode */
//     REG_ptECCCNT_LR_PE[u4PE].LRECCTSTCTL = 0UL;

//     /* Enable ECC Err and parity Err Reporitng */
//     REG_ptMECCCAP_LR0[u4PE].ERRINT = VAL_u4LR0_ERRINT_OV_AF_DE;
// }

/*
     * ICache TAG
     */
// for (u4PE = 0; u4PE < SS_USE_CORE_COUNT; u4PE++)
// {
//     /* clear error status */
//     REG_ptMECCCAP_IT[u4PE].DSTCLR = VAL_u4LDSTCLR;
//     REG_ptMECCCAP_IT[u4PE].OVFCLR = VAL_u4LOVFCLR_01;

//     /* Enable ECC Enc/Dec, parity Check */
//     REG_u4ITECCCTL(u4PE) = VAL_u4ECCCTL_AF_ECC; /* EDET_INT30 */

//     /* Enable ECC Err and parity Err Reporitng */
//     REG_ptMECCCAP_IT[u4PE].ERRINT = VAL_u4IT_ERRINT_AF_DE;
// }

/*
     * ICache DATA
     */
// for (u4PE = 0; u4PE < SS_USE_CORE_COUNT; u4PE++)
// {
/* clear error status */
// REG_ptMECCCAP_ID[u4PE].DSTCLR = VAL_u4LDSTCLR;
// REG_ptMECCCAP_ID[u4PE].OVFCLR = VAL_u4LOVFCLR_01;

/* Enable ECC Enc/Dec, parity Check */
// REG_u4IDECCCTL(u4PE) = VAL_u4ECCCTL_AF_ECC; /* EDET_INT30 */

/* Enable ECC Err and parity Err Reporitng */
// REG_ptMECCCAP_ID[u4PE].ERRINT = VAL_u4ID_ERRINT_AF_DE;
// }

/*
     * ClusterRAM
     */
/* clear error status */
// REG_ptMECCCAP_CRAM[0].DSTCLR = VAL_u4LDSTCLR;
// REG_ptMECCCAP_CRAM[0].OVFCLR = VAL_u4LOVFCLR_01;

/* Enable ECC Enc/Dec, parity Check */
// REG_u4CRAECCCTL = VAL_u4ECCCTL_SECDED;

/* enable AF & disable test mode */
// REG_ptECCCNT_CRCCL[0UL].CRCAFCTL     = 0UL;
// REG_ptECCCNT_CRCCL[0UL].CRCECCTSTCTL = 0UL;

// REG_ptECCCNT_CRCCL[3UL].CRCAFCTL     = 0UL;
// REG_ptECCCNT_CRCCL[3UL].CRCECCTSTCTL = 0UL;

// #if (ECU_TARGETDEVICE == ECU_U2A16)
//     REG_ptECCCNT_CRCCL[1UL].CRCAFCTL     = 0UL;
//     REG_ptECCCNT_CRCCL[1UL].CRCECCTSTCTL = 0UL;
// #endif
// #if ((ECU_TARGETDEVICE == ECU_U2A16) || (ECU_TARGETDEVICE == ECU_U2A8))
//     REG_ptECCCNT_CRCCL[2UL].CRCAFCTL     = 0UL;
//     REG_ptECCCNT_CRCCL[2UL].CRCECCTSTCTL = 0UL;
// #endif

/* Enable ECC Err and parity Err Reporitng */
// REG_ptMECCCAP_CRAM[0].ERRINT = VAL_u4CR_ERRINT_OV_AF_DE;

// /* Lock Registers */
// REG_u4ECCKCPROT = VAL_u4KCPROT_LOCK;

// /* synchronization for P-Bus Group0 */
// u4Dummy = REG_u4ECCKCPROT;

// return;
// }

// void Ecu_Int_initPeri(void)
// {
//     volatile uint32 u4Dummy;
/*
        ■1bitエラー以外をPE0でキャッチ
        80: Code Flash - Address parity error
        81: Code Flash - Data ECC 2-bit error
        82: Code Flash - Data ECC 1-bit error
        83: Code Flash - ECC overflow error
        160: Data transfer path - Address EDC error
        161: Data transfer path - Data ECC 2 - bit error
        162: Data transfer path - Data  ECC 1-bit  error

        ■PE毎に処理するので、キャッチしない。
        96: Local RAM - Data ECC 2-bit error
        97: Local RAM - Data ECC 1-bit error
        98: Local RAM - ECC overflow error

        38: BUS Bridge compare error
        43: CRAM Bus routing error
        104 Cluster RAM - Address feedback
            compare error - Data ECC 2-bit error
        105 Cluster RAM - Data ECC 1-bit error
        106 Cluster RAM- ECC overflow error

        ■1bitエラー以外をPE0でキャッチ
        232: Local RAM (PE0) - Address  feedback
             compare error - Data ECC 2-bit error
        233: Local RAM (PE0) - Data ECC 1-bit error
        234: Local RAM (PE0) - ECC overflow error
        236: Instruction cache RAM(PE0) - Address  feedback
             compare error - Data EDC error

        ■1bitエラー以外をPE1でキャッチ
        264: Local RAM (PE1) - Address  feedback
             compare error - Data ECC 2-bit error
        265: Local RAM (PE1) - Data ECC 1-bit error
        266: Local RAM (PE1) - ECC overflow error
        268: Instruction cache RAM(PE1) - Address  feedback
             compare error - Data EDC error

        ■1bitエラー以外をPE2でキャッチ
        296: Local RAM (PE2) - Address  feedback
             compare error - Data ECC 2-bit error
        297: Local RAM (PE2) - Data ECC 1-bit error
        298: Local RAM (PE2) - ECC overflow error
        330: Instruction cache RAM(PE2) - Address  feedback
             compare error - Data EDC error

        ■1bitエラー以外をPE3でキャッチ
        328: Local RAM (PE3) - Address  feedback
             compare error - Data ECC 2-bit error
        329: Local RAM (PE3) - Data ECC 1-bit error
        330: Local RAM (PE3) - ECC overflow error
        332: Instruction cache RAM(PE3) - Address  feedback
             compare error - Data EDC error


    */

// uint32 u4PE;

/* Unlock Registers */
// REG_u4ECMKCPROT = VAL_u4KCPROT_UNLOCK;

// Ecu_Int_activateECMchAsFEINT(0UL, 80UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 81UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 83UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 160UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 161UL);

// Ecu_Int_activateECMchAsFEINT(0UL, 38UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 43UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 104UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 105UL);
// Ecu_Int_activateECMchAsFEINT(0UL, 106UL);

// for (u4PE = 0; u4PE < SS_USE_CORE_COUNT; u4PE++)
// {
//     Ecu_Int_activateECMchAsFEINT(u4PE, 232UL + (u4PE * 32UL)); /* EDET_INT30 */
//     Ecu_Int_activateECMchAsFEINT(u4PE, 234UL + (u4PE * 32UL)); /* EDET_INT30 */
//     Ecu_Int_activateECMchAsFEINT(u4PE, 236UL + (u4PE * 32UL)); /* EDET_INT30 */
// }

/* Lock Registers */
// REG_u4ECMKCPROT = VAL_u4KCPROT_LOCK;

/* synchronization for P-Bus Group3 */
// u4Dummy = REG_u4ECMKCPROT;

// for (u4PE = 0; u4PE < SS_USE_CORE_COUNT; u4PE++)
// {
//     REG_u4FEINTMSK(u4PE) = VAL_u4FEINTMSK_ENABLE_ECM; /* EDET_INT30 */
// }
// /* synchronization for P-Bus Group 2L */
// u4Dummy = REG_u4FEINTMSK(0UL);

// return;
// }

/**---------------------------------------------------------------------------
 * [Format]	void _Ecu_Int_enableCAT1ISR(void)
 * [Function]	Set Enable Category1 Interrupt
 * [Arguments]	None
 * [Return]	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
#if 0u
void Ecu_Int_enableCAT1ISR(void)
{
    __DI();

    __LDSR(REG_u4PLMR_regID, REG_u4PLMR_selID, VAL_u4PLMR_CAT2DI);
    Ecu_Int_syncp();

    __EI();
    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format]	void Ecu_int_InitGuard(void)
 * [Function]	enable PEG
 * [Arguments]	None
 * [Return]	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
void Ecu_Int_initGuard(void)
{
    /* Unlock registers */
    REG_u4PEGKCPROT_PE0 = VAL_u4PEGKCPROT_UNLOCK;

    REG_u4PEGSPID_PE0 = VAL_u4PEGSPID_PE0;

    REG_u4PEGBAD_PE0  = VAL_u4PEGBAD_LR0;
    REG_u4PEGADV_PE0  = VAL_u4PEGADV_LR0;
    REG_u4PEGPROT_PE0 = VAL_u4PEGPROT_LR0;

    /* Lock Registers */
    REG_u4PEGKCPROT_PE0 = VAL_u4KCPROT_LOCK;

#if (SS_USE_CORE_COUNT >= 2u)
    /* Unlock registers */
    REG_u4PEGKCPROT_PE1 = VAL_u4PEGKCPROT_UNLOCK;

    REG_u4PEGSPID_PE1 = VAL_u4PEGSPID_PE1;

    REG_u4PEGBAD_PE1  = VAL_u4PEGBAD_LR1;
    REG_u4PEGADV_PE1  = VAL_u4PEGADV_LR1;
    REG_u4PEGPROT_PE1 = VAL_u4PEGPROT_LR1;

    /* Lock Registers */
    REG_u4PEGKCPROT_PE1 = VAL_u4KCPROT_LOCK;
#endif

#if (SS_USE_CORE_COUNT >= 3u)
    /* Unlock registers */
    REG_u4PEGKCPROT_PE2 = VAL_u4PEGKCPROT_UNLOCK;

    REG_u4PEGSPID_PE2 = VAL_u4PEGSPID_PE2;

    REG_u4PEGBAD_PE2  = VAL_u4PEGBAD_LR2;
    REG_u4PEGADV_PE2  = VAL_u4PEGADV_LR2;
    REG_u4PEGPROT_PE2 = VAL_u4PEGPROT_LR2;

    /* Unlock registers */
    REG_u4PEGKCPROT_PE2 = VAL_u4KCPROT_LOCK;
#endif

#if (SS_USE_CORE_COUNT >= 4u)
    /* Unlock registers */
    REG_u4PEGKCPROT_PE3 = VAL_u4PEGKCPROT_UNLOCK;

    REG_u4PEGSPID_PE3 = VAL_u4PEGSPID_PE3;

    REG_u4PEGBAD_PE3  = VAL_u4PEGBAD_LR3;
    REG_u4PEGADV_PE3  = VAL_u4PEGADV_LR3;
    REG_u4PEGPROT_PE3 = VAL_u4PEGPROT_LR3;

    /* Unlock registers */
    REG_u4PEGKCPROT_PE3 = VAL_u4KCPROT_LOCK;
#endif

    return;
}
