MEMORY
{
    MEM_OPBT_CFG           : ORIGIN = 0xFF321380,  LENGTH = 128   /* <CSAb_base> = 0xff321000 + 0x380 */
    MEM_OPBT_SEC           : ORIGIN = 0xFF322700,  LENGTH = 32    /* <SSAb_base> = 0xff322000 + 0x700 */
}
SECTIONS
{
	.data                            :
	.bss                             :
	
	.secinfo                         :
	.rosdata                         :
	.tdata                           :
	.sdabase                         :
    .text                            :

	.rh850u2a16_opbt_cfg    align(4) : > MEM_OPBT_CFG
	.rh850u2a16_opbt_sec    align(4) : > MEM_OPBT_SEC
}
