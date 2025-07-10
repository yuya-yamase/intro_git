// ==================================================
//     セクション定義 ( RH850/U2A )
// ==================================================

// ------------------------
// セクションテーブル
// ------------------------
SECTIONS {

// -- ROM -------------------
// TopAddress
// Vector
    .vectortable_fe0                                        : > vector_core     // OS起動前ベクタ領域(FE用)トップ


// TopAddress
// Data
    .rodata                 align(4)                        : > rom_memory

// BSW
    .bsw_code_top           align(4)                        : > .
    .osCode ALIGN(16):
    {
        *(".osCode*")
    } > .
    .bsw_dcm_text           align(16)                       : > .
    .bsw_cs_text            align(16)                       : > .
    .bsw_can_text           align(16)                       : > .
    .bsw_e2e_text           align(16)                       : > .
    .bsw_code_bottom        align(4)                        : > .

    .bsw_const_top          align(4)                        : > .
    .osConst ALIGN(4):
    {
        *(".osConst*")
    } > .
    .bsw_dcm_rodata         align(4)                        : > .
    .bsw_cs_const           align(4)                        : > .
    .bsw_can_const          align(4)                        : > .
    .bsw_const_bottom       align(4)                        : > .

    .bsw_e_nvar_ival_top    align(4)  ROM(.bsw_e_nvar_withval_top)     : > .
    .bsw_e_nvar_ival_bottom align(4)  ROM(.bsw_e_nvar_withval_bottom)  : > .

    .bsw_e_rvar_ival_top    align(4)  ROM(.bsw_e_rvar_withval_top)     : > .
    .bsw_e_rvar_ival_bottom align(4)  ROM(.bsw_e_rvar_withval_bottom)  : > .

    .bsw_n_nvar_ival_top    align(4)  ROM(.bsw_n_nvar_withval_top)     : > .
    .bsw_n_nvar_ival_bottom align(4)  ROM(.bsw_n_nvar_withval_bottom)  : > .

    .bsw_n_rvar_ival_top    align(4)  ROM(.bsw_n_rvar_withval_top)     : > .
    .bsw_n_rvar_ival_bottom align(4)  ROM(.bsw_n_rvar_withval_bottom)  : > .

// SS
    .ss_code                align(4)                        : > .               // SSコード領域(QM)
    .ss_code_p              align(4)                        : > .               // SSコード領域(ASIL)
    .ss_const               align(4)                        : > .               // SSの定数領域(QM)
    .ss_const_p             align(4)                        : > .               // SSの定数領域(ASIL)
    .ecu_code               align(4)                        : > .               // ユーザコード領域(QM)
    .ecu_code_p             align(4)                        : > .               // ユーザコード領域(ASIL)
    .ecu_const              align(4)                        : > .               // ユーザの定数領域(QM)
    .ecu_const_p            align(4)                        : > .               // ユーザの定数領域(ASIL)
    .text                   align(4)                        : > .               // コンパイラのデフォルト領域

// MCAL
    .mcal_rom_top           align(4)                        : > .
    .DIO_TEXT_CODE          align(4)                        : > .
    .DMA_TEXT_CODE          align(4)                        : > .
    .GPT_TEXT_CODE          align(4)                        : > .
    .ICU_TEXT_CODE          align(4)                        : > .
    .INTC_TEXT_CODE         align(4)                        : > .
    .I2C_TEXT_CODE          align(4)                        : > .
    .MCALCOMMON_TEXT_CODE   align(4)                        : > .
    .PORT_TEXT_CODE         align(4)                        : > .
    .PWM_TEXT_CODE          align(4)                        : > .
    .SPI_TEXT_CODE          align(4)                        : > .
    .WDG_TEXT_CODE          align(4)                        : > .
    .ADC_RODATA_CONST       align(4)                        : > .
    .DIO_RODATA_CONST       align(4)                        : > .
    .DMA_RODATA_CONST       align(4)                        : > .
    .GPT_RODATA_CONST       align(4)                        : > .
    .ICU_RODATA_CONST       align(4)                        : > .
    .INTC_RODATA_CONST      align(4)                        : > .
    .I2C_RODATA_CONST       align(4)                        : > .
    .PORT_RODATA_CONST      align(4)                        : > .
    .PWM_RODATA_CONST       align(4)                        : > .
    .SPI_RODATA_CONST       align(4)                        : > .
    .WDG_RODATA_CONST       align(4)                        : > .
    .mcal_rom_bottom        align(4)                        : > .
    _MCAL_ROM_SIZE = . - ADDR(.mcal_rom_top);

// IOHW
    .iohw_rom_top           align(4)                        : > .
    .IOHW_ADC_TEXT_CODE     align(4)                        : > .
    .IOHW_DIFLT_TEXT_CODE   align(4)                        : > .
    .IOHW_ADC_RODATA_CONST  align(4)                        : > .
    .IOHW_DIFLT_RODATA_CONST align(4)                       : > .
    .iohw_rom_bottom        align(4)                        : > .
    _IOHW_ROM_SIZE = . - ADDR(.iohw_rom_top);

// APP
    .app_n_nvarLR_ival      align(4)  ROM(.app_n_nvarLR_withval)  : > .
    .app_n_nvarCR0_ival     align(4)  ROM(.app_n_nvarCR0_withval)  : > .
    .app_n_nvarCR1_ival     align(4)  ROM(.app_n_nvarCR1_withval)  : > .

    .app_n_bvar_ival        align(4)  ROM(.app_n_bvar_withval)     : > .
    .app_n_rvar_ival        align(4)  ROM(.app_n_rvar_withval)     : > .

// InitData
    .romdata                align(4)  ROM(.data)            : > .

// SDA
    .rosda_start            align(4)                        : > .
    .rosdata                align(4)                        : > .
    .rosda_end              align(4)                        : > .

// SecInfo
    .secinfo                align(4)                        : > .               // セクションデータ領域


// -- RAM -------------------
// TopAddress
    .ram_local_top                                          : > ram_memory_core

// Stack
    .ss_stack_top           align(4)
        : {__StackArea_start=.;}                              > .               // スタックトップチェック用
    .os_stack_top           align(4)                        : > .               // スタック領域(OS)
    .osVarStack             ALIGN(4):
    {
        *(".osVar_stack*")
    } > .
    .os_stack_bottom        align(4)                        : > .               // スタック領域ボトム(OS)
    _OS_STACK_SIZE = . - ADDR(.os_stack_top);
    .ss_stack               align(4)                        : > .               // スタック領域(OS起動前)
    .ss_stack_bottom        align(4)
        : {*(.ss_stack_bottom).=ALIGN(4); __StackArea_end=.;} > .               // スタックボトムチェック用

// APP
    .app_n_nvarLR_withval        align(4)                  : > .
    _APP_N_NVARLR_WITHVAL_SIZE = . - ADDR(.app_n_nvarLR_withval);
    .ecu_n_nvarLR_top            align(4)                  : > .
    .app_n_nvarLR                align(4)                  : > .
    .bss_GPI2C                   align(4)                  : > .
    .ecu_n_nvarLR_bottom         align(4)                  : > .
    _ECU_N_NVAR_LR_SIZE = . - ADDR(.ecu_n_nvarLR_top);

// TDA
    .tdata                  align(4)                        : > .               // TDA変数領域

// EndAddress
    .ram_local_end                                          : > ram_end_core


// TopAddress
    .cluster0_ramtop                                        : > ram_memory_cluster0

// SS
    .ss_nvar_e_top          align(4)                        : > .
    .ss_nvar_sw             align(4)                        : > .
    .ss_nvar_e_bottom       align(4)                        : > .
    _SS_NVAR_E_SIZE = . - ADDR(.ss_nvar_e_top);

// APP
    .app_n_nvarCR0_withval  align(4)                        : > .
    _APP_N_NVARCR0_WITHVAL_SIZE = . - ADDR(.app_n_nvarCR0_withval);
    .ecu_n_nvarCR0_top      align(4)                        : > .
    .app_n_nvarCR0          align(4)                        : > .
    .ecu_n_nvarCR0_bottom   align(4)                        : > .
    _ECU_N_NVAR_CR0_SIZE = . - ADDR(.ecu_n_nvarCR0_top);

// SDA
    .sda_start              align(4)                        : > .
    .sda_end                align(4)                        : > .

// Rim Data
    .MEM_SEC_STA_RAM_LOC_APPL    ALIGN(8)                             : > .
    .bss_RIM1                    ALIGN(8)                             : > .
    .bss_RIM2                    ALIGN(8)                             : > .
    .bss_RIM3                    ALIGN(8)                             : > .
    .MEM_SEC_END_RAM_LOC_APPL    ALIGN(8)                             : > .
    _LOC_RAM_SIZE = . - ADDR(.MEM_SEC_STA_RAM_LOC_APPL);

// MCAL Data
    .DMA_BSS_VAR_NO_INIT         align(4)                  : > .
    .SPI_BSS_VAR_NO_INIT         align(4)                  : > .

// IOHW Data
    .iohw_ram_top                align(4)                  : > .
    .IOHW_ADC_BSS_VAR_NO_INIT    align(4)                  : > .
    .IOHW_DIFLT_BSS_VAR_NO_INIT  align(4)                  : > .
    .iohw_ram_bottom             align(4)                  : > .
    _IOHW_RAM_SIZE = . - ADDR(.iohw_ram_top);

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
    .cluster1_ramend                                         : > ram_end_cluster1 

    .cluster2_share_ramtop                                   : > ram_memory_cluster2_share

//1byte
    .bss_SHARE_IOHW_ADC_LV_RD   SHARE_IOHW_ADC_LV_RD_ADDR   ABS    : > .
//2byte
//4byte
    .bss_SHARE_PORT_CONF        SHARE_PORT_CONF_ADDR        ABS    : > .
    .bss_SHARE_VEH_OPEMD_MDBIT  SHARE_VEH_OPEMD_MDBIT_ADDR  ABS    : > .
//struct
    .bss_SHARE_IOHW_ADC_LV      SHARE_IOHW_ADC_LV_ADDR      ABS    : > .
    .bss_SHARE_IOHW_DIFLT_FLTRD SHARE_IOHW_DIFLT_FLTRD_ADDR ABS    : > .
    .bss_SHARE_DMA_NOTICATION   SHARE_DMA_NOTICATION_ADDR   ABS    : > .
    .bss_SHARE_SPI_MODEA_CHANNELDATA SHARE_SPI_MODEA_CHANNELDATA_ADDR ABS    : > .
    .bss_SHARE_SPI_MODEC_CHANNELDATA SHARE_SPI_MODEC_CHANNELDATA_ADDR ABS    : > .

    .cluster2_share_ramend                                   : > ram_end_cluster2_share 

// TopAddress
    .cluster2_ramtop                                         : > ram_memory_cluster2

// BSW
    .bsw_e_nvar_top         align(4)                        : > .
    .ecu_nvar_sw            align(4)                        : > .
    .bsw_cs_data            align(4)                        : > .
    .bsw_can_data           align(4)                        : > .
    .bsw_dcm_bss            align(4)                        : > .
    .os_var_top             align(4)                        : > .
    .osVarCleared ALIGN(4):
    {
        *(".osVar_Global_Cleared*")
        *(".osVar_Local0_Cleared*")
    } > .
    
    .osVarNoInit ALIGN(4):
    {
        *(".osVar_Global_NoInit*")
        *(".osVar_Local0_NoInit*")
        *(".osVarSpinlock_Global_NoInit*")
        *(".osVar_Local0_Mkmsg_Buffers")
    } > .
    .os_var_bottom          align(4)                        : > .
    .bsw_e_nvar_bottom      align(4)                        : > .
    _BSW_E_NVAR_SIZE = . - ADDR(.bsw_e_nvar_top);

    .bsw_e_nvar_withval_top       align(4)                        : > .
    .bsw_e_nvar_withval_bottom    align(4)                        : > .
    _BSW_E_NVAR_WITHVAL_SIZE = . - ADDR(.bsw_e_nvar_withval_top);

    .bsw_n_nvar_top         align(4)                        : > .
    .bsw_n_nvar_bottom      align(4)                        : > .
    _BSW_N_NVAR_SIZE = . - ADDR(.bsw_n_nvar_top);

    .bsw_n_nvar_withval_top       align(4)                        : > .
    .bsw_n_nvar_withval_bottom    align(4)                        : > .
    _BSW_N_NVAR_WITHVAL_SIZE = . - ADDR(.bsw_n_nvar_withval_top);

// Default Data
    .data                   align(4)                        : > .               // コンパイラのデフォルト領域
    .data_bottom            align(4)                        : > .
    _DATA_SIZE = . - ADDR(.data);

    .ecu_nvar_top           align(4)                        : > .
    .bss                    align(4)                        : > .               // コンパイラのデフォルト領域
    .ecu_nvar_bottom        align(4)                        : > .
    _ECU_NVAR_SIZE = . - ADDR(.ecu_nvar_top);

    .ecu_nvar_p_top         align(4)                        : > .
    .ecu_nvar_sw_p          align(4)                        : > .
    .ecu_nvar_p_bottom      align(4)                        : > .
    _ECU_NVAR_P_SIZE = . - ADDR(.ecu_nvar_p_top);

// EndAddress
    .cluster2_ramend                                         : > ram_end_cluster2


// -- RetentionRAM -------------
// TopAddress
    .retention_ramtop                                       : > retention_ram

    .MEM_SEC_STA_BACK_BSW        ALIGN(8)                             : > .
    .bss_BACK_BSW                ALIGN(8)                             : > .
    .bss_BACK_BSW_space          PAD((8-(sizeof(.bss_BACK_BSW)%8))%8) : > .  /* To prevent GAIO UT Error */
    .MEM_SEC_END_BACK_BSW        ALIGN(8)                             : > .
    _BSS_BACK_BSW_SIZE = . - ADDR(.bss_BACK_BSW);

//Rim
    .MEM_SEC_STA_BACK_APPL       ALIGN(8)                             : > .
    .bss_BACK_KEYWORD0           ALIGN(8)                             : > .
    .bss_BACK                    ALIGN(8)                             : > .
    .bss_BACK_KEYWORD1           ALIGN(8)                             : > .
    .bss_BACK_RIM1               ALIGN(8)                             : > .
    .bss_BACK_RIM2               ALIGN(8)                             : > .
    .bss_BACK_RIM3               ALIGN(8)                             : > .
    .bss_BACK_KEYWORD2           ALIGN(8)                             : > .
    .MEM_SEC_END_BACK_APPL       ALIGN(8)                             : > .
    .MEM_SEC_END_BACK_USD        ALIGN(8)                             : > .
    _BSS_BACK_SIZE = . - ADDR(.MEM_SEC_STA_BACK_APPL);


//BSW
    .bsw_e_rvar_top         align(4)                        : > .
    .bsw_e_rvar_bottom      align(4)                        : > .
    _BSW_E_RVAR_SIZE = . - ADDR(.bsw_e_rvar_top);

    .bsw_e_rvar_withval_top       align(4)                        : > .
    .bsw_e_rvar_withval_bottom    align(4)                        : > .
    _BSW_E_RVAR_WITHVAL_SIZE = . - ADDR(.bsw_e_rvar_withval_top);

    .bsw_n_rvar_top         align(4)                        : > .
    .bsw_n_rvar_bottom      align(4)                        : > .
    _BSW_N_RVAR_SIZE = . - ADDR(.bsw_n_rvar_top);

    .bsw_n_rvar_withval_top       align(4)                        : > .
    .bsw_n_rvar_withval_bottom    align(4)                        : > .
    _BSW_N_RVAR_WITHVAL_SIZE = . - ADDR(.bsw_n_rvar_withval_top);

//SS
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

    .ss_ram_bottom        ADDR(retention_ram_end) - ( (sizeof(.ss_ram_bottom) + 3) / 4 ) * 4 : > . // RAM領域ボトム（ラベル）
   
// EndAddress
    .retention_ramend                                       : > retention_ram_end // リテンションRAMボトム（ラベル）


}
