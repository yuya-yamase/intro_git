// ==================================================
//         セクション定義 ( RH850/U2A )
// ==================================================

// ------------------------
// メモリマップ
// ------------------------
MEMORY {
// Address Space:Code flash (User Area 3) (Bank D)
    vector_core         : ORIGIN = 0x00600000, LENGTH = 0x000200                  //LENGTH:0.5KB
    rom_memory          : ORIGIN = 0x00600200, LENGTH = 0x1FFA00                  //LENGTH:2046.5KB(2MB-0.5KB-1KB)
// 0x007FFC00 - x007FFFFF: reserved for RRPG section.

// Address Space:Local RAM (CPU3)
// ORIGIN = 0xFD600000, LENGTH = 64K
//  Local RAM (self)    : ORIGIN = 0xFD600000, LENGTH = 0x4000                    //LENGTH:16KB
    ram_memory_core     : ORIGIN = 0xFD608000, LENGTH = 0x8000                    //LENGTH:32KB
    ram_end_core        : ORIGIN = 0xFD610000, LENGTH = 0

// Address Space:Cluster RAM (Cluster0)
    ram_memory_cluster0 : ORIGIN = 0xFE040000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster0    : ORIGIN = 0xFE050000, LENGTH = 0

// Address Space:Cluster RAM (Cluster1)
    ram_memory_cluster1 : ORIGIN = 0xFE140000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster1    : ORIGIN = 0xFE150000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2 share)
    ram_memory_cluster2_share : ORIGIN = 0xFE430000, LENGTH = 0x10000             //LENGTH:64KB
    ram_end_cluster2_share    : ORIGIN = 0xFE440000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2)
    ram_memory_cluster2 : ORIGIN = 0xFE540000, LENGTH = 0x40000                   //LENGTH:256KB
    ram_end_cluster2    : ORIGIN = 0xFE580000, LENGTH = 0

// Address Space:Cluster RAM (Cluster3) (Retention RAM)
    retention_ram       : ORIGIN = 0xFE820000, LENGTH = 0x8000                    //LENGTH:32KB
    retention_ram_end   : ORIGIN = 0xFE828000, LENGTH = 0
}

DEFAULTS {
//1byte (0xFE430000 - 0xFE430100)
    SHARE_IOHW_ADC_LV_RD_ADDR          = 0xFE430000
//2byte (0xFE430100 - 0xFE430300)
//4byte (0xFE430300 - 0xFE430700)
    SHARE_PORT_CONF_ADDR               = 0xFE430300
    SHARE_VEH_OPEMD_MDBIT_ADDR         = 0xFE430304    
    SHARE_COMPLEX_VEHOPEMD_SYSSTS_ADDR = 0xFE430308                              //LENGTH:4byte
    SHARE_OXCAN_NMSTS_ADDR             = 0xFE43030C
//Struct
    SHARE_IOHW_ADC_LV_ADDR             = 0xFE431000
    SHARE_IOHW_DIFLT_FLTRD_ADDR        = 0xFE431100
    SHARE_DMA_NOTICATION_ADDR          = 0xFE431200
    SHARE_SPI_MODEA_CHANNELDATA_ADDR   = 0xFE431300
    SHARE_SPI_MODEC_CHANNELDATA_ADDR   = 0xFE431400
}