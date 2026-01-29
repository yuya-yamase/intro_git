// ==================================================
//     セクション定義 ( RH850/U2A )
// ==================================================

#define USER_ENTRY_ADDRESS    0x003C0200
#define EHVM_ENTRY_ADDRESS    0x003D0000

// ------------------------
// セクションテーブル
// ------------------------
SECTIONS {

// -- ROM -------------------
// TopAddress
// Vector
    .vectortable_fe0 ALIGN(4) : > vector_core0

    .user_text ALIGN(4) USER_ENTRY_ADDRESS:
    {
        *(.text.ehvm.usr)
        *(.text)
        . = . + 64;
        . = ALIGN(16);
    } >vector_core0 =0

    .text_hv ALIGN(4) EHVM_ENTRY_ADDRESS:
    {
        *(.reset.text.ehvm)
        *(.text.ehvm)
        . = . + 64;         /* プリフェッチ要求によるメモリ読み出しを考慮して、最終アドレスに64バイトを加算 */
        . = ALIGN(16);
    } >vector_core0 =0

    _etext = .;
    PROVIDE (etext = .);

    .call_table_data ALIGN (16) :
    {
        PROVIDE(__ctbp = .);
        *(.call_table_data)
        . = ALIGN(16);      /* .call_table_dataセクションと.call_table_textセクションは16バイト境界アドレスから開始する */
    } >vector_core0  = 0xff /* Fill gaps with 0xff.  */

    .call_table_text ALIGN (16) :
    {
        *(.call_table_text)
        . = ALIGN(16);      /* .call_table_dataセクションと.call_table_textセクションは16バイト境界アドレスから開始する */
        . = . + 64;         /* プリフェッチ要求によるメモリ読み出しを考慮して、最終アドレスに64バイトを加算 */
    } >vector_core0 = 0xff /* Fill gaps with 0xff.  */

// BSW
    .bsw_code_top           align(4)                                   : > .
    .bsw_code_bottom        align(4)                                   : > .

    .bsw_const_top          align(4)                                   : > .
    .bsw_const_bottom       align(4)                                   : > .

    .bsw_e_nvar_ival_top    align(4)  ROM(.bsw_e_nvar_withval_top)     : > .
    .bsw_e_nvar_ival_bottom align(4)  ROM(.bsw_e_nvar_withval_bottom)  : > .

    .bsw_e_rvar_ival_top    align(4)  ROM(.bsw_e_rvar_withval_top)     : > .
    .bsw_e_rvar_ival_bottom align(4)  ROM(.bsw_e_rvar_withval_bottom)  : > .

    .bsw_n_nvar_ival_top    align(4)  ROM(.bsw_n_nvar_withval_top)     : > .
    .bsw_n_nvar_ival_bottom align(4)  ROM(.bsw_n_nvar_withval_bottom)  : > .

    .bsw_n_rvar_ival_top    align(4)  ROM(.bsw_n_rvar_withval_top)     : > .
    .bsw_n_rvar_ival_bottom align(4)  ROM(.bsw_n_rvar_withval_bottom)  : > .

// SS
    .ss_code                align(4)                        : > .
    .ss_code_p              align(4)                        : > .
    .ss_const               align(4)                        : > .
    .ss_const_p             align(4)                        : > .
    .ecu_code               align(4)                        : > .
    .ecu_code_p             align(4)                        : > .
    .ecu_const              align(4)                        : > .
    .ecu_const_p            align(4)                        : > . 

// MCAL
    .mcal_rom_top           align(4)                        : > .
    .ADCDIAG_TEXT_CODE      align(4)                        : > .
    .ADCDIAG_TEXT_CODE_FAST align(4)                        : > .
    .ADC_TEXT_CODE          align(4)                        : > .
    .ADC_TEXT_CODE_FAST     align(4)                        : > .
    .DIO_TEXT_CODE          align(4)                        : > .
    .DMA_TEXT_CODE          align(4)                        : > .
    .DMA_DESC_TEXT_CODE     align(4)                        : > .
    .ERRH_TEXT_CODE         align(4)                        : > .
    .GPT_TEXT_CODE          align(4)                        : > .
    .ICU_TEXT_CODE          align(4)                        : > .
    .INTC_TEXT_CODE         align(4)                        : > .
    .MCALCOMMON_TEXT_CODE   align(4)                        : > .
    .MCU_TEXT_CODE          align(4)                        : > .
    .PORT_TEXT_CODE         align(4)                        : > .
    .TYPORT_TEXT_CODE       align(4)                        : > .
    .SPI_TEXT_CODE          align(4)                        : > .
    .ADCDIAG_RODATA_CONST   align(4)                        : > .
    .ADC_RODATA_CONST       align(4)                        : > .
    .DIO_RODATA_CONST       align(4)                        : > .
    .DMA_RODATA_CONST       align(4)                        : > .
    .DMA_DESC_RODATA_CONST  align(4)                        : > .
    .ERRH_RODATA_CONST      align(4)                        : > .
    .GPT_RODATA_CONST       align(4)                        : > .
    .ICU_RODATA_CONST       align(4)                        : > .
    .INTC_RODATA_CONST      align(4)                        : > .
    .MCU_RODATA_CONST       align(4)                        : > .
    .PORT_RODATA_CONST      align(4)                        : > .
    .TYPORT_RODATA_CONST    align(4)                        : > .
    .SPI_RODATA_CONST       align(4)                        : > .
    .mcal_rom_bottom        align(4)                        : > .
    _MCAL_ROM_SIZE = . - ADDR(.mcal_rom_top);

// APP
    .app_n_nvarLR0_ival     align(4)  ROM(.app_n_nvarLR0_withval)  : > .
    .app_n_nvarLR1_ival     align(4)  ROM(.app_n_nvarLR1_withval)  : > .
    .app_n_nvarLR2_ival     align(4)  ROM(.app_n_nvarLR2_withval)  : > .
    .app_n_nvarLR3_ival     align(4)  ROM(.app_n_nvarLR3_withval)  : > .

    .app_n_nvarCR0_ival     align(4)  ROM(.app_n_nvarCR0_withval)  : > .
    .app_n_nvarCR1_ival     align(4)  ROM(.app_n_nvarCR1_withval)  : > .

    .app_n_bvar_ival        align(4)  ROM(.app_n_bvar_withval)     : > .
    .app_n_rvar_ival        align(4)  ROM(.app_n_rvar_withval)     : > .

// ROM Config
    .rodata.ehvm.cfg ALIGN(4):
    {
        *(".rodata.ehvm.cfg")
        . = ALIGN(16);
    } > .

// InitData
    .rodata ALIGN(4):
    {
        *(.rodata)
        *(.rodata.ehvm)
        . = ALIGN(16);
    } > .

    .romdata                align(4) ROM(.data)             : > .
    .romdata_lram           align(4) ROM(.data_lram)        : > .
    .romdata_vcc            align(4) ROM(.data_vcc)         : > .

// SDA
    .rosda_start ALIGN (16) :
    .rosdata ALIGN(4):
    {
        *(.rosdata)
        *(.rosdata.ehvm)
        . = ALIGN(16);
    } > .
    .rosda_end :

// SecInfo
    .secinfo                    :

// SysCall
    .syscall                    :


// -- RAM -------------------
// TopAddress
    .ram_local0_top                                         : > ram_memory_core0

// MCAL Data
    .mcal_ram_top                align(4)                   : > .
    .ADCDIAG_BSS_VAR_NO_INIT     align(4)                   : > .
    .ADC_BSS_VAR_NO_INIT         align(4)                   : > .
    .DMA_BSS_VAR_NO_INIT         align(4)                   : > .
    .ERRH_BSS_VAR_NO_INIT        align(4)                   : > .
    .MCALCOMMON_BSS_VAR_NO_INIT  align(4)                   : > .
    .MCU_BSS_VAR_NO_INIT         align(4)                   : > .
    .PORT_BSS_VAR_NO_INIT        align(4)                   : > .
    .SPI_BSS_VAR_NO_INIT         align(4)                   : > .
    .mcal_ram_bottom             align(4)                   : > .
    _MCAL_RAM_SIZE = . - ADDR(.mcal_ram_top);

// APP
    .app_n_nvarLR0_withval       align(4)                   : > .
    _APP_N_NVARLR0_WITHVAL_SIZE = . - ADDR(.app_n_nvarLR0_withval);
    .ecu_n_nvarLR0_top           align(4)                   : > .
    .app_n_nvarLR0               align(4)                   : > .
    .ecu_n_nvarLR0_bottom        align(4)                   : > .
    _ECU_N_NVAR_LR0_SIZE = . - ADDR(.ecu_n_nvarLR0_top);

// Stack
    .ss_stack_top                align(4)                   : > .
    .ss_stack                    align(4)                   : > .
    .ss_stack_bottom             align(4)                   : > .

// EndAddress
    .ram_local0_end                                         : > ram_end_core0


// TopAddress
    .ram_local1_top                                         : > ram_memory_core1

// APP
    .app_n_nvarLR1_withval  align(4)                        : > .
    _APP_N_NVARLR1_WITHVAL_SIZE = . - ADDR(.app_n_nvarLR1_withval);
    .ecu_n_nvarLR1_top      align(4)                        : > .
    .app_n_nvarLR1          align(4)                        : > .
    .ecu_n_nvarLR1_bottom   align(4)                        : > .
    _ECU_N_NVAR_LR1_SIZE = . - ADDR(.ecu_n_nvarLR1_top);

// Stack
    .ss_stack1_top               align(4)                   : > .
    .ss_stack1                   align(4)                   : > .
    .ss_stack1_bottom            align(4)                   : > .

// EndAddress
    .ram_local1_end                                         : > ram_end_core1


// TopAddress
    .ram_local2_top                                         : > ram_memory_core2

// APP
    .app_n_nvarLR2_withval  align(4)                        : > .
    _APP_N_NVARLR2_WITHVAL_SIZE = . - ADDR(.app_n_nvarLR2_withval);
    .ecu_n_nvarLR2_top      align(4)                        : > .
    .app_n_nvarLR2          align(4)                        : > .
    .ecu_n_nvarLR2_bottom   align(4)                        : > .
    _ECU_N_NVAR_LR2_SIZE = . - ADDR(.ecu_n_nvarLR2_top);

// Stack
    .ss_stack2_top               align(4)                   : > .
    .ss_stack2                   align(4)                   : > .
    .ss_stack2_bottom            align(4)                   : > .

// EndAddress
    .ram_local2_end                                         : > ram_end_core2


// TopAddress
    .ram_local3_top                                         : > ram_memory_core3

// APP
    .app_n_nvarLR3_withval  align(4)                        : > .
    _APP_N_NVARLR3_WITHVAL_SIZE = . - ADDR(.app_n_nvarLR3_withval);
    .ecu_n_nvarLR3_top      align(4)                        : > .
    .app_n_nvarLR3          align(4)                        : > .
    .ecu_n_nvarLR3_bottom   align(4)                        : > .
    _ECU_N_NVAR_LR3_SIZE = . - ADDR(.ecu_n_nvarLR3_top);

// Stack
    .ss_stack3_top               align(4)                   : > .
    .ss_stack3                   align(4)                   : > .
    .ss_stack3_bottom            align(4)                   : > .

// EndAddress
    .ram_local3_end                                         : > ram_end_core3


// TopAddress
    .cluster0_ramtop                                        : > ram_memory_cluster0

// APP
    .app_n_nvarCR0_withval  align(4)                        : > .
    _APP_N_NVARCR0_WITHVAL_SIZE = . - ADDR(.app_n_nvarCR0_withval);
    .ecu_n_nvarCR0_top      align(4)                        : > .
    .app_n_nvarCR0          align(4)                        : > .
    .ecu_n_nvarCR0_bottom   align(4)                        : > .
    _ECU_N_NVAR_CR0_SIZE = . - ADDR(.ecu_n_nvarCR0_top);

// EndAddress
    .cluster0_ramend                                        : > ram_end_cluster0


// TopAddress
    .cluster1_ramtop                                        : > ram_memory_cluster1

// APP
    .app_n_nvarCR1_withval  align(4)                        : > .
    _APP_N_NVARCR1_WITHVAL_SIZE = . - ADDR(.app_n_nvarCR1_withval);
    .ecu_n_nvarCR1_top      align(4)                        : > .
    .app_n_nvarCR1          align(4)                        : > .
    .ecu_n_nvarCR1_bottom   align(4)                        : > .
    _ECU_N_NVAR_CR1_SIZE = . - ADDR(.ecu_n_nvarCR1_top);

// EndAddress
    .cluster1_ramend                                        : > ram_end_cluster1 


// TopAddress
    .cluster2_ramtop                                        : > ram_memory_cluster2

// BSW
    .ecu_nvar_top           align(4)                        : > .
    .bss                    align(4)                        : > .
    .noinit ALIGN (8) :
    {
        *(".noinit")
        . = ALIGN(8);
    } > .
    .ecu_nvar_bottom        align(4)                        : > .
    _ECU_NVAR_SIZE = . - ADDR(.ecu_nvar_top);

// Shared memory used for Internal VM Communication
    .ecu_nvar_global_top    align(4)                        : > .
    .bss.ehvm.cfg.global    align(8)                        : > .
    .bss.ehvm.global        align(8)                        : > .
    .ecu_nvar_global_bottom align(4)                        : > .
    _ECU_NVAR_GLOBAL_SIZE = . - ADDR(.ecu_nvar_global_top);

    .bsw_e_nvar_top         align(4)                        : > .
    .ecu_nvar_sw            align(4)                        : > .
    .bsw_e_nvar_bottom      align(4)                        : > .
    _BSW_E_NVAR_SIZE = . - ADDR(.bsw_e_nvar_top);
    
    .bsw_e_nvar_withval_top       align(4)                  : > .
    .bsw_e_nvar_withval_bottom    align(4)                  : > .
    _BSW_E_NVAR_WITHVAL_SIZE = . - ADDR(.bsw_e_nvar_withval_top);

    .bsw_n_nvar_top         align(4)                        : > .
    .bsw_n_nvar_bottom      align(4)                        : > .
    _BSW_N_NVAR_SIZE = . - ADDR(.bsw_n_nvar_top);

    .bsw_n_nvar_withval_top       align(4)                  : > .
    .bsw_n_nvar_withval_bottom    align(4)                  : > .
    _BSW_N_NVAR_WITHVAL_SIZE = . - ADDR(.bsw_n_nvar_withval_top);

// SS
    .ss_nvar_e_top          align(4)                        : > .
    .ss_nvar_sw             align(4)                        : > .
    .ss_nvar_e_bottom       align(4)                        : > .
    _SS_NVAR_E_SIZE = . - ADDR(.ss_nvar_e_top);

// data with initial values
    .data                   align(4)                        : > .
    .data_bottom            align(4)                        : > .
    _DATA_SIZE = . - ADDR(.data);

// shared data for configuration located in global ram
    .data_vcc ALIGN (4) :
    {
        *(.data.ehvm.cfg.global)
        . = ALIGN(8);
    } > .
    .data_vcc_bottom            align(4)                    : > .
    _DATA_VCC_SIZE = . - ADDR(.data_vcc);

// TDA
    .tdata                  align(4)                        : > .

// SDA
    .sda_start              align(4)                        : > .
    .sda_end                align(4)                        : > .

// EndAddress
    .cluster2_ramend                                        : > ram_end_cluster2 

    .cluster2_share_ramtop                                   : > ram_memory_cluster2_share

//1byte
//2byte
//4byte
//struct
    .bss_SHARE_DMA_NOTICATION   SHARE_DMA_NOTICATION_ADDR   ABS    : > .
    .bss_SHARE_SPI_MODEA_CHANNELDATA SHARE_SPI_MODEA_CHANNELDATA_ADDR ABS    : > .
    .bss_SHARE_SPI_MODEC_CHANNELDATA SHARE_SPI_MODEC_CHANNELDATA_ADDR ABS    : > .

    .cluster2_share_ramend                                   : > ram_end_cluster2_share 
    _BSW_SHARE_DATA_SIZE = . - ADDR(.cluster2_share_ramtop);

// TopAddress
    .lram_self_ramtop                                       : > ram_memory_lram_self
    .data_lram ALIGN (4) :
    {
        *(.data.ehvm)
        . = ALIGN(8);
    } > .
    .data_lram_bottom            align(4)                   : > .
    _DATA_LRAM_SIZE = . - ADDR(.data_lram);

    .ecu_nvar_lram_top      align(4)                        : > .
    .stack.ehvm             align(4)                        : > .
    .sbss.ehvm              align(4)                        : > .
    .bss.ehvm               align(8)                        : > .
    .bss.ehvm.cfg           align(8)                        : > .
    .noinit_ehvm ALIGN (8) :
    {
        *(".noinit.ehvm")
        . = ALIGN(8);
    } > .
    .ecu_nvar_lram_bottom        align(4)                   : > .
    _ECU_NVAR_LRAM_SIZE = . - ADDR(.ecu_nvar_lram_top);

// EndAddress
    .lram_self_ramend                                       : > ram_end_lram_self 


// -- RetentionRAM -------------
// TopAddress
    .retention_ramtop                                       : > retention_ram

//BSW
    .bsw_e_rvar_top         align(4)                        : > .
    .bsw_e_rvar_bottom      align(4)                        : > .
    _BSW_E_RVAR_SIZE = . - ADDR(.bsw_e_rvar_top);

    .bsw_e_rvar_withval_top       align(4)                  : > .
    .bsw_e_rvar_withval_bottom    align(4)                  : > .
    _BSW_E_RVAR_WITHVAL_SIZE = . - ADDR(.bsw_e_rvar_withval_top);

    .bsw_n_rvar_top         align(4)                        : > .
    .bsw_n_rvar_bottom      align(4)                        : > .
    _BSW_N_RVAR_SIZE = . - ADDR(.bsw_n_rvar_top);

    .bsw_n_rvar_withval_top       align(4)                  : > .
    .bsw_n_rvar_withval_bottom    align(4)                  : > .
    _BSW_N_RVAR_WITHVAL_SIZE = . - ADDR(.bsw_n_rvar_withval_top);

// SS
    .ss_rvar_e_top          align(4)                        : > .
    .ss_rvar_s              align(4)                        : > .
    .ss_rvar_e_bottom       align(4)                        : > .
    _SS_RVAR_E_SIZE = . - ADDR(.ss_rvar_e_top);

//APP
    .app_n_bvar_withval     align(4)                        : > .
    _APP_N_BVAR_WITHVAL_SIZE = . - ADDR(.app_n_bvar_withval);
    .app_n_rvar_withval     align(4)                        : > .
    _APP_N_RVAR_WITHVAL_SIZE = . - ADDR(.app_n_rvar_withval);

    .ecu_n_bvar_top         align(4)                        : > .
    .ecu_n_bvar             align(4)                        : > .
    .app_n_bvar             align(4)                        : > .
    .ecu_n_bvar_bottom      align(4)                        : > .
    _ECU_N_BVAR_SIZE = . - ADDR(.ecu_n_bvar_top);

    .ecu_n_rvar_top         align(4)                        : > .
    .app_n_rvar             align(4)                        : > .
    .ecu_n_rvar_bottom      align(4)                        : > .
    _ECU_N_RVAR_SIZE = . - ADDR(.ecu_n_rvar_top);

// EndAddress
    .retention_ramend                                       : > retention_ram_end


    _end = . ;
    PROVIDE (end = .);

    /* Stabs debugging sections.  */
    .stab USER_ENTRY_ADDRESS             : { *(.stab) }
    .stabstr USER_ENTRY_ADDRESS          : { *(.stabstr) }
    .stab.excl USER_ENTRY_ADDRESS        : { *(.stab.excl) }
    .stab.exclstr USER_ENTRY_ADDRESS     : { *(.stab.exclstr) }
    .stab.index USER_ENTRY_ADDRESS       : { *(.stab.index) }
    .stab.indexstr USER_ENTRY_ADDRESS    : { *(.stab.indexstr) }
    .comment USER_ENTRY_ADDRESS          : { *(.comment) }
    /* DWARF debug sections.
       Symbols in the DWARF debugging sections are relative to the beginning
       of the section so we begin them at 0.  */
    /* DWARF 1 */
    .debug          USER_ENTRY_ADDRESS   : { *(.debug) }
    .line           USER_ENTRY_ADDRESS   : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  USER_ENTRY_ADDRESS   : { *(.debug_srcinfo) }
    .debug_sfnames  USER_ENTRY_ADDRESS   : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  USER_ENTRY_ADDRESS   : { *(.debug_aranges) }
    .debug_pubnames USER_ENTRY_ADDRESS   : { *(.debug_pubnames) }
}
