// ==================================================
//         セクション定義 ( RH850/U2A )
// ==================================================

// ------------------------
// メモリマップ
// ------------------------
MEMORY {
// Address Space:Code flash (User Area 1) (Bank B)
    vector_core         : ORIGIN = 0x00200000, LENGTH = 0x000200                  //LENGTH:0.5KB
    rom_memory          : ORIGIN = 0x00200200, LENGTH = 0x1FFE00                  //LENGTH:2047.5KB(2MB-0.5KB)

// Address Space:Local RAM (CPU1)
// ORIGIN = 0xFDA00000, LENGTH = 64K
//  Local RAM (self)    : ORIGIN = 0xFDA00000, LENGTH = 0x4000                    //LENGTH:16KB
    ram_memory_core     : ORIGIN = 0xFDA08000, LENGTH = 0x8000                    //LENGTH:32KB
    ram_end_core        : ORIGIN = 0xFDA10000, LENGTH = 0

// Address Space:Cluster RAM (Cluster0)
    ram_memory_cluster0 : ORIGIN = 0xFE020000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster0    : ORIGIN = 0xFE030000, LENGTH = 0

// Address Space:Cluster RAM (Cluster1)
    ram_memory_cluster1 : ORIGIN = 0xFE120000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster1    : ORIGIN = 0xFE130000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2 share)
    ram_memory_cluster2_share : ORIGIN = 0xFE430000, LENGTH = 0x10000             //LENGTH:64KB
    ram_end_cluster2_share    : ORIGIN = 0xFE440000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2)
    ram_memory_cluster2 : ORIGIN = 0xFE4C0000, LENGTH = 0x40000                   //LENGTH:256KB
    ram_end_cluster2    : ORIGIN = 0xFE500000, LENGTH = 0

// Address Space:Cluster RAM (Cluster3) (Retention RAM)
    retention_ram       : ORIGIN = 0xFE810000, LENGTH = 0x8000                    //LENGTH:32KB
    retention_ram_end   : ORIGIN = 0xFE818000, LENGTH = 0
}

DEFAULTS {
//1byte (0xFE430000 - 0xFE430100)
    SHARE_IOHW_ADC_LV_RD_ADDR   = 0xFE430000
//2byte (0xFE430100 - 0xFE430300)
//4byte (0xFE430300 - 0xFE430700)
    SHARE_PORT_CONF_ADDR        = 0xFE430300
    SHARE_VEH_OPEMD_MDBIT_ADDR  = 0xFE430304    
//Struct
    SHARE_IOHW_ADC_LV_ADDR      = 0xFE431000
    SHARE_IOHW_DIFLT_FLTRD_ADDR = 0xFE431100
    SHARE_DMA_NOTICATION_ADDR   = 0xFE431200
    SHARE_SPI_MODEA_CHANNELDATA_ADDR   = 0xFE431300
    SHARE_SPI_MODEC_CHANNELDATA_ADDR   = 0xFE431400
}