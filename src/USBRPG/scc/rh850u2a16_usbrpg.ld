MEMORY
{
    MEM_USBRPG_CFG           : ORIGIN = 0x00000000,  LENGTH = 512   /* Header */
    MEM_DUMMY                : ORIGIN = 0x00000200,  LENGTH = 4     /* For .sdabase */
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

	.rh850u2a16_usbrpg_cfg    align(4) : > MEM_USBRPG_CFG
}
