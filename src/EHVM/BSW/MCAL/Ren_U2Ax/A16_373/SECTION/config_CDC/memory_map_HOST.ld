// ==================================================
//         セクション定義 ( RH850/U2A )
// ==================================================

// ------------------------
// メモリマップ
// ------------------------
MEMORY {
// Address Space:Code flash (User Area 0) (Bank A)
    vector_core0            : ORIGIN = 0x003C0000, LENGTH = 0x40000                 //LENGTH:256KB

// Address Space:Local RAM (CPU3)
    ram_memory_core3        : ORIGIN = 0xFD604000, LENGTH = 0x4000                  //LENGTH:16KB
    ram_end_core3           : ORIGIN = 0xFD608000, LENGTH = 0K

// Address Space:Local RAM (CPU2)
    ram_memory_core2        : ORIGIN = 0xFD804000, LENGTH = 0x4000                  //LENGTH:16KB
    ram_end_core2           : ORIGIN = 0xFD808000, LENGTH = 0K

// Address Space:Local RAM (CPU1)
    ram_memory_core1        : ORIGIN = 0xFDA04000, LENGTH = 0x4000                  //LENGTH:16KB
    ram_end_core1           : ORIGIN = 0xFDA08000, LENGTH = 0

// Address Space:Local RAM (CPU0)
    ram_memory_core0        : ORIGIN = 0xFDC04000, LENGTH = 0x4000                  //LENGTH:16KB
    ram_end_core0           : ORIGIN = 0xFDC08000, LENGTH = 0

// Address Space:Local RAM (self)
    ram_memory_lram_self    : ORIGIN = 0xFDE00000, LENGTH = 0x4000                  //LENGTH:16KB
    ram_end_lram_self       : ORIGIN = 0xFDE04000, LENGTH = 0

// Address Space:Cluster RAM (Cluster0)
    ram_memory_cluster0    : ORIGIN = 0xFE000000, LENGTH = 0x10000                  //LENGTH:64KB
    ram_end_cluster0       : ORIGIN = 0xFE010000, LENGTH = 0

// Address Space:Cluster RAM (Cluster1)
    ram_memory_cluster1    : ORIGIN = 0xFE100000, LENGTH = 0x10000                  //LENGTH:64KB
    ram_end_cluster1       : ORIGIN = 0xFE110000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2)
    ram_memory_cluster2    : ORIGIN = 0xFE400000, LENGTH = 0x30000                  //LENGTH:192KB
    ram_end_cluster2       : ORIGIN = 0xFE430000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2 share)
    ram_memory_cluster2_share : ORIGIN = 0xFE430000, LENGTH = 0x10000               //LENGTH:64KB
    ram_end_cluster2_share    : ORIGIN = 0xFE440000, LENGTH = 0

// Address Space:Cluster RAM (Cluster3) (Retention RAM)
// 0xFE800000 - 0xFE801000: reserved for RRPG.
    retention_ram           : ORIGIN = 0xFE801000, LENGTH = 0x7000                  //LENGTH:28KB
    retention_ram_end       : ORIGIN = 0xFE808000, LENGTH = 0

// Address Space:Data Flash (Hardware Property Area)
 	CSA_OPTBYTE             : ORIGIN = 0xFF321300, LENGTH = 0x100

}

DEFAULTS {
//1byte (0xFE430000 - 0xFE430100)
//2byte (0xFE430100 - 0xFE430300)
//4byte (0xFE430300 - 0xFE430700)
//Struct, array
}