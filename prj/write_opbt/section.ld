CONSTANTS
{
	CSA_START = 0xFF321380
	CSA_SIZE = 0x80
}
MEMORY
{
    /* memory map */
    flash(rx)          : ORIGIN = 0x00000000, LENGTH = 2M-64K  /* Code Flash              */
    flash2(r)          : ORIGIN = 0x001F0000, LENGTH = 64K     /* Code Flash (Config)     */
    lram(rwx)          : ORIGIN = 0xfde00000, LENGTH = 24K     /* Local RAM (self)        */
    cram2_data(rwx)    : ORIGIN = 0xfe400000, LENGTH = 1500K   /* Cluster RAM (Cluster2)  */
	CSA : ORIGIN = CSA_START, LENGTH = CSA_SIZE
}
SECTIONS
{
	.data :> lram
	.bss :
	
	.secinfo:
	.rosdata :
	.tdata :
	.sdabase :
    .text :
	
	CSA_SECTION align(4) :>CSA
}
