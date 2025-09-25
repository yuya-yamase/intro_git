// ==================================================
//         セクション定義 ( RH850/U2A )
// ==================================================

// ------------------------
// メモリマップ
// ------------------------
MEMORY {
// Address Space:Code flash (User Area 0) (Bank A)
    vector_core         : ORIGIN = 0x00210000, LENGTH = 0x000200                  //LENGTH:0.5KB
    rom_memory          : ORIGIN = 0x00210200, LENGTH = 0x1AFC00                  //LENGTH:1727KB(1728KB-0.5KB-0.5KB)
    rom_memory_share    : ORIGIN = 0x003BFE00, LENGTH = 0x000200                  //LENGTH:0.5KB

// Address Space:Local RAM (CPU0)
// ORIGIN = 0xFDC00000, LENGTH = 64K
//  Local RAM (self)    : ORIGIN = 0xFDC00000, LENGTH = 0x4000                    //LENGTH:16KB
    ram_memory_core     : ORIGIN = 0xFDC08000, LENGTH = 0x8000                    //LENGTH:32KB
    ram_end_core        : ORIGIN = 0xFDC10000, LENGTH = 0

// Address Space:Cluster RAM (Cluster0)
    ram_memory_cluster0 : ORIGIN = 0xFE010000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster0    : ORIGIN = 0xFE020000, LENGTH = 0

// Address Space:Cluster RAM (Cluster1)
    ram_memory_cluster1 : ORIGIN = 0xFE110000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster1    : ORIGIN = 0xFE120000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2 share)
    ram_memory_cluster2_share : ORIGIN = 0xFE430000, LENGTH = 0x10000             //LENGTH:64KB
    ram_end_cluster2_share    : ORIGIN = 0xFE440000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2)
    ram_memory_cluster2 : ORIGIN = 0xFE440000, LENGTH = 0x80000                   //LENGTH:512KB
    ram_end_cluster2    : ORIGIN = 0xFE4C0000, LENGTH = 0

// Address Space:Cluster RAM (Cluster3) (Retention RAM)
    retention_ram       : ORIGIN = 0xFE808000, LENGTH = 0x8000                    //LENGTH:32KB
    retention_ram_end   : ORIGIN = 0xFE810000, LENGTH = 0
}

DEFAULTS {
//1byte (0xFE430000 - 0xFE430100)
//2byte (0xFE430100 - 0xFE430300)
//4byte (0xFE430300 - 0xFE430700)
    SHARE_PORT_CONF_ADDR        = 0xFE430300
//Struct
    SHARE_DMA_NOTICATION_ADDR   = 0xFE431200
    SHARE_SPI_MODEA_CHANNELDATA_ADDR   = 0xFE431300
    SHARE_SPI_MODEC_CHANNELDATA_ADDR   = 0xFE431400

//ROM_data_share(0x003BFE00-0x003C0000)
    SHARE_ROM_VM0_RIM_KEYWORD0  = 0x003BFE00
    SHARE_ROM_VM0_RIM_KEYWORD1  = 0x003BFE04
    SHARE_ROM_VM0_RIM_KEYWORD2  = 0x003BFE08
    SHARE_ROM_VM1_RIM_KEYWORD0  = 0x003BFE0C
    SHARE_ROM_VM1_RIM_KEYWORD1  = 0x003BFE10
    SHARE_ROM_VM1_RIM_KEYWORD2  = 0x003BFE14
    SHARE_ROM_VM2_RIM_KEYWORD0  = 0x003BFE18
    SHARE_ROM_VM2_RIM_KEYWORD1  = 0x003BFE1C
    SHARE_ROM_VM2_RIM_KEYWORD2  = 0x003BFE20
    SHARE_ROM_VM3_RIM_KEYWORD0  = 0x003BFE24
    SHARE_ROM_VM3_RIM_KEYWORD1  = 0x003BFE28
    SHARE_ROM_VM3_RIM_KEYWORD2  = 0x003BFE2C
}
