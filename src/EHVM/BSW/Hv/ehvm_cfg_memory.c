/*
    Copyright (C) 2022 eSOL Co.,Ltd. All rights reserved.

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/
/****************************************************************************
 [ ehvm_cfg_memory.c ] - Memory Protection module's configuration data file
****************************************************************************/

#include "ehvm_cfg_memory.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mPBusGuardConfig                                                                  */
/****************************************************************************************/
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_00[7] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_01[4] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_10[3] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_20[16] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_14, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_15, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_21[16] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_14, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_15, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_22[14] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_30[16] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_14, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_15, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_31[14] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_32[16] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_14, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_15, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_33[6] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_40[8] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_50[16] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00004000U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00000002U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00000010U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_14, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_15, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00001000U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_51[16] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_14, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_15, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_52[16] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_11, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_12, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_13, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_14, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_15, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_53[7] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_6L0[7] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_6L1[4] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_6H0[3] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_70[5] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_80[11] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_8, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_9, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_10, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};
static EhvmConst ehvm_pbg_channel_t s_Pbg_ChannelData_90[8] = {
    {
        PBG_CHANNEL_0, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_1, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_2, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_3, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_4, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_5, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_6, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    },
    {
        PBG_CHANNEL_7, /* PBG_ChannelNumber */
        0x00000043U,    /* PBGPROT0 */
        0x00005013U     /* PBGPROT1 */
    }
};

static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_00[2] = {
    {
        PBG_MODULE_00,            /* PBG_ModuleNumber */
        7U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_00[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_01,            /* PBG_ModuleNumber */
        4U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_01[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_10[1] = {
    {
        PBG_MODULE_10,            /* PBG_ModuleNumber */
        3U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_10[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_20[3] = {
    {
        PBG_MODULE_20,            /* PBG_ModuleNumber */
        16U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_20[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_21,            /* PBG_ModuleNumber */
        16U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_21[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_22,            /* PBG_ModuleNumber */
        14U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_22[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_30[4] = {
    {
        PBG_MODULE_30,            /* PBG_ModuleNumber */
        16U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_30[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_31,            /* PBG_ModuleNumber */
        14U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_31[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_32,            /* PBG_ModuleNumber */
        16U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_32[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_33,            /* PBG_ModuleNumber */
        6U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_33[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_40[1] = {
    {
        PBG_MODULE_40,            /* PBG_ModuleNumber */
        8U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_40[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_50[4] = {
    {
        PBG_MODULE_50,            /* PBG_ModuleNumber */
        16U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_50[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_51,            /* PBG_ModuleNumber */
        16U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_51[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_52,            /* PBG_ModuleNumber */
        16U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_52[0]   /* PbgChannelPtr */
    },
    {
        PBG_MODULE_53,            /* PBG_ModuleNumber */
        7U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_53[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_6L0[1] = {
    {
        PBG_MODULE_6L0,            /* PBG_ModuleNumber */
        7U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_6L0[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_6L1[1] = {
    {
        PBG_MODULE_6L1,            /* PBG_ModuleNumber */
        4U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_6L1[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_6H0[1] = {
    {
        PBG_MODULE_6H0,            /* PBG_ModuleNumber */
        3U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_6H0[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_70[1] = {
    {
        PBG_MODULE_70,            /* PBG_ModuleNumber */
        5U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_70[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_80[1] = {
    {
        PBG_MODULE_80,            /* PBG_ModuleNumber */
        11U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_80[0]   /* PbgChannelPtr */
    }
};
static EhvmConst ehvm_pbg_module_t s_Pbg_ModuleData_90[1] = {
    {
        PBG_MODULE_90,            /* PBG_ModuleNumber */
        8U,                       /* NumOfPbgChannel */
        &s_Pbg_ChannelData_90[0]   /* PbgChannelPtr */
    }
};

static EhvmConst ehvm_pbg_group_t s_Pbg_GroupData[12] = {
    {
        PBG_GROUP_00,           /* PBG_GroupNumber */
        2U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_00[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_10,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_10[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_20,           /* PBG_GroupNumber */
        3U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_20[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_30,           /* PBG_GroupNumber */
        4U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_30[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_40,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_40[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_50,           /* PBG_GroupNumber */
        4U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_50[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_6L0,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_6L0[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_6L1,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_6L1[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_6H0,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_6H0[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_70,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_70[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_80,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_80[0]   /* PbgModulePtr */
    },
    {
        PBG_GROUP_90,           /* PBG_GroupNumber */
        1U,                     /* NumOfPbgModule */
        &s_Pbg_ModuleData_90[0]   /* PbgModulePtr */
    }
};

EhvmConst ehvm_pbg_config_t ehvmPbgConfigData = {
    12U,  /* PbgNumOfGroup */
    &s_Pbg_GroupData[0]   /* PbgGroupPtr */
};

/****************************************************************************************/
/* Hv4mHBusGuardConfig                                                                  */
/****************************************************************************************/
static EhvmConst ehvm_hbg_prot_t s_Hbg_ProtData[4] = {
    {
        91U,          /* HbgChannelNumber */
        0x00000043U,  /* HbgProt_0 */
        0x00000000U   /* HbgProt_1 */
    },
    {
        92U,          /* HbgChannelNumber */
        0x00000043U,  /* HbgProt_0 */
        0x00000000U   /* HbgProt_1 */
    },
    {
        93U,          /* HbgChannelNumber */
        0x00000043U,  /* HbgProt_0 */
        0x00000000U   /* HbgProt_1 */
    },
    {
        96U,          /* HbgChannelNumber */
        0x00000043U,  /* HbgProt_0 */
        0x00000000U   /* HbgProt_1 */
    }
};

EhvmConst ehvm_hbg_config_t ehvmHbgConfigData = {
    4U,  /* Hbg_NumOfHBGProt */
    &s_Hbg_ProtData[0]   /* Hbg_HBGProtPtr */
};

/****************************************************************************************/
/* Hv4mIBusGuardConfig                                                                  */
/****************************************************************************************/
static EhvmConst ehvm_ibg_prot_t s_Ibg_Tptm_N_Data[4] = {
    {
        0x00000043U,  /* IBGTPTM_PROT0 */
        0x00000001U   /* IBGTPTM_PROT1 */
    },
    {
        0x00000043U,  /* IBGTPTM_PROT0 */
        0x00000001U   /* IBGTPTM_PROT1 */
    },
    {
        0x00000043U,  /* IBGTPTM_PROT0 */
        0x00000001U   /* IBGTPTM_PROT1 */
    },
    {
        0x00000043U,  /* IBGTPTM_PROT0 */
        0x00000001U   /* IBGTPTM_PROT1 */
    }
};

static EhvmConst ehvm_ibg_prot_t s_Ibg_Tptm_8_Data[1] = {
    {
        0x00000043U,  /* IBGTPTM_8_PROT0 */
        0x00000000U   /* IBGTPTM_8_PROT0 */
    }
};

static EhvmConst ehvm_ibg_prot_t s_Ibg_Tptm_9_Data[1] = {
    {
        0x00000043U,  /* IBGTPTM_9_PROT0 */
        0x00000000U   /* IBGTPTM_9_PROT0 */
    }
};

static EhvmConst ehvm_ibg_tptm_t s_Ibg_TptmData[1] = {
    {
        4U,                     /* Ibg_NumOfTptm_n */
        &s_Ibg_Tptm_N_Data[0],  /* Ibg_Tptm_n_Ptr */
        1U,                     /* Ibg_NumOfTptm_8 */
        &s_Ibg_Tptm_8_Data[0],  /* Ibg_Tptm_8_Ptr */
        1U,                     /* Ibg_NumOfTptm_9 */
        &s_Ibg_Tptm_9_Data[0]   /* Ibg_Tptm_9_Ptr */
    }
};

static EhvmConst ehvm_ibg_prot_t s_Ibg_Barr_Data[16] = {
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000000U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000001U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000001U   /* IBGBARR_PROT1 */
    },
    {
        0x00000043U,  /* IBGBARR_PROT0 */
        0x00000001U   /* IBGBARR_PROT1 */
    }
};

static EhvmConst ehvm_ibg_prot_t s_Ibg_Barr_16_Data[1] = {
    {
        0x00000043U,  /* IBGBARR_16_PROT0 */
        0x00000000U   /* IBGBARR_16_PROT1 */
    }
};

static EhvmConst ehvm_ibg_barr_t s_Ibg_BarrData[1] = {
    {
        16U,                      /* Ibg_NumOfBarr */
        &s_Ibg_Barr_Data[0],     /* Ibg_BarrPtr */
        1U,                      /* Ibg_NumOfBarr16 */
        &s_Ibg_Barr_16_Data[0]   /* Ibg_Barr16Ptr */
    }
};

static EhvmConst ehvm_ibg_prot_t s_Ibg_Ipir_Rn_Data[4] = {
    {
        0x00000043U,  /* IBGIPIR_RnPROT0 */
        0x00000001U   /* IBGIPIR_RnPROT1 */
    },
    {
        0x00000043U,  /* IBGIPIR_RnPROT0 */
        0x00000001U   /* IBGIPIR_RnPROT1 */
    },
    {
        0x00000043U,  /* IBGIPIR_RnPROT0 */
        0x00000001U   /* IBGIPIR_RnPROT1 */
    },
    {
        0x00000043U,  /* IBGIPIR_RnPROT0 */
        0x00000001U   /* IBGIPIR_RnPROT1 */
    }
};

static EhvmConst ehvm_ibg_prot_t s_Ibg_Ipir_Tn_Data[4] = {
    {
        0x00000043U,  /* IBGIPIR_TnPROT0 */
        0x00000001U   /* IBGIPIR_TnPROT1 */
    },
    {
        0x00000043U,  /* IBGIPIR_TnPROT0 */
        0x00000000U   /* IBGIPIR_TnPROT1 */
    },
    {
        0x00000043U,  /* IBGIPIR_TnPROT0 */
        0x00000000U   /* IBGIPIR_TnPROT1 */
    },
    {
        0x00000043U,  /* IBGIPIR_TnPROT0 */
        0x00000000U   /* IBGIPIR_TnPROT1 */
    }
};

static EhvmConst ehvm_ibg_prot_t s_Ibg_Ipir_4_Data[1] = {
    {
        0x00000043U,  /* IBGIPIR_4PROT0 */
        0x00000000U   /* IBGIPIR_4PROT1 */
    }
};

static EhvmConst ehvm_ibg_ipir_t s_Ibg_IpirData[1] = {
    {
        4U,                      /* Ibg_NumOfRn */
        &s_Ibg_Ipir_Rn_Data[0],  /* Ibg_RnPtr */
        4U,                      /* Ibg_NumOfTn */
        &s_Ibg_Ipir_Tn_Data[0],  /* Ibg_TnPtr */
        1U,                      /* Ibg_NumOf4 */
        &s_Ibg_Ipir_4_Data[0]    /* Ibg_4Ptr */
    }
};

EhvmConst ehvm_ibg_config_t ehvmIbgConfigData = {
    1U,                  /* Ibg_NumOfIPIR */
    &s_Ibg_IpirData[0],  /* Ibg_IPIRPtr */
    1U,                  /* Ibg_NumOfBARR */
    &s_Ibg_BarrData[0],  /* Ibg_BARRPtr */
    1U,                  /* Ibg_NumOfTPTM */
    &s_Ibg_TptmData[0]   /* Ibg_TPTMPtr */
};

/****************************************************************************************/
/* Hv4mDmaControllerGuardConfig                                                         */
/****************************************************************************************/
static EhvmConst ehvm_dmag_spid_t s_Dmag_SpidData_CL0[5] = {
    {
        0x00000000U  /* sDMACGMPIDn */
    },
    {
        0x00000001U  /* sDMACGMPIDn */
    },
    {
        0x00000004U  /* sDMACGMPIDn */
    },
    {
        0x0000000CU  /* sDMACGMPIDn */
    },
    {
        0x0000000EU  /* sDMACGMPIDn */
    }
};
static EhvmConst ehvm_dmag_spid_t s_Dmag_SpidData_CL1[1] = {
    {
        0x00000000U  /* sDMACGMPIDn */
    }
};

static EhvmConst ehvm_dmag_n_channel_t s_Dmag_ChannelData_CL0[16] = {
    {
        0U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        1U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        2U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        3U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        4U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        5U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        6U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        7U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        8U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        9U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        10U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        11U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        12U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        13U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        14U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        15U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    }
};
static EhvmConst ehvm_dmag_n_channel_t s_Dmag_ChannelData_CL1[16] = {
    {
        0U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        1U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        2U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        3U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        4U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        5U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        6U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        7U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        8U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        9U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        10U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        11U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        12U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        13U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        14U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    },
    {
        15U,           /* sDMACG_ChannelNumber */
        0x00000043U   /* sDMACG_n_PROTm */
    }
};

static EhvmConst ehvm_dmag_channel_t s_Dmag_GRData_CL0[1] = {
    {
        0x00000043U  /* sDMACG_GR_PROTm */
    }
};
static EhvmConst ehvm_dmag_channel_t s_Dmag_GRData_CL1[1] = {
    {
        0x00000043U  /* sDMACG_GR_PROTm */
    }
};

static EhvmConst ehvm_dmag_channel_t s_Dmag_DPData_CL0[1] = {
    {
        0x00000043U  /* sDMACG_DP_PROTm */
    }
};
static EhvmConst ehvm_dmag_channel_t s_Dmag_DPData_CL1[1] = {
    {
        0x00000043U  /* sDMACG_DP_PROTm */
    }
};

static EhvmConst ehvm_dmag_group_t s_Dmag_groupData[2] = {
    {
        0U,                          /* Dmag_GroupNumber */
        5U,                          /* Dmag_NumOfSPID */
        &s_Dmag_SpidData_CL0[0],     /* Dmag_SPIDPtr */
        16U,                          /* Dmag_NumOfDMAG_n */
        &s_Dmag_ChannelData_CL0[0],  /* Dmag_DMAG_n_Ptr */
        1U,                          /* Dmag_NumOfDMAG_GR */
        &s_Dmag_GRData_CL0[0],       /* Dmag_DMAG_GR_Ptr */
        1U,                          /* Dmag_NumOfDMAG_DP */
        &s_Dmag_DPData_CL0[0]        /* Dmag_DMAG_DP_Ptr */
    },
    {
        1U,                          /* Dmag_GroupNumber */
        1U,                          /* Dmag_NumOfSPID */
        &s_Dmag_SpidData_CL1[0],     /* Dmag_SPIDPtr */
        16U,                          /* Dmag_NumOfDMAG_n */
        &s_Dmag_ChannelData_CL1[0],  /* Dmag_DMAG_n_Ptr */
        1U,                          /* Dmag_NumOfDMAG_GR */
        &s_Dmag_GRData_CL1[0],       /* Dmag_DMAG_GR_Ptr */
        1U,                          /* Dmag_NumOfDMAG_DP */
        &s_Dmag_DPData_CL1[0]        /* Dmag_DMAG_DP_Ptr */
    }
};

EhvmConst ehvm_dmag_config_t ehvmDmagConfigData = {
    2U,                    /* Dmag_NumOfGroup */
    &s_Dmag_groupData[0]   /* Dmag_GroupPtr */
};

/****************************************************************************************/
/* Hv4mDtsControllerGuardConfig                                                         */
/****************************************************************************************/
static EhvmConst ehvm_dtsg_spid_t s_Dtsg_SpidData[5] = {
    {
        0x00000000U  /* DTSGMPIDn */
    },
    {
        0x00000001U  /* DTSGMPIDn */
    },
    {
        0x00000004U  /* DTSGMPIDn */
    },
    {
        0x0000000CU  /* DTSGMPIDn */
    },
    {
        0x0000000EU  /* DTSGMPIDn */
    }
};

static EhvmConst ehvm_dtsg_n_channel_t s_Dtsg_ChannelData[128] = {
    {
        0U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        1U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        2U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        3U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        4U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        5U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        6U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        7U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        8U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        9U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        10U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        11U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        12U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        13U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        14U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        15U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        16U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        17U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        18U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        19U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        20U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        21U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        22U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        23U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        24U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        25U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        26U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        27U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        28U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        29U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        30U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        31U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        32U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        33U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        34U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        35U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        36U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        37U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        38U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        39U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        40U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        41U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        42U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        43U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        44U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        45U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        46U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        47U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        48U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        49U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        50U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        51U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        52U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        53U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        54U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        55U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        56U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        57U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        58U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        59U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        60U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        61U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        62U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        63U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        64U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        65U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        66U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        67U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        68U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        69U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        70U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        71U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        72U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        73U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        74U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        75U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        76U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        77U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        78U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        79U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        80U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        81U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        82U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        83U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        84U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        85U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        86U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        87U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        88U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        89U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        90U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        91U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        92U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        93U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        94U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        95U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        96U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        97U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        98U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        99U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        100U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        101U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        102U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        103U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        104U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        105U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        106U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        107U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        108U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        109U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        110U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        111U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        112U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        113U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        114U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        115U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        116U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        117U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        118U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        119U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        120U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        121U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        122U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        123U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        124U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        125U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        126U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    },
    {
        127U,         /* DTSG_ChannelNumber */
        0x00000043U /* DTSGPROT_nnn */
    }
};

static EhvmConst ehvm_dtsg_channel_t s_Dtsg_GRData[1] = {
    {
        0x00000043U /* DTSGPROT_GR */
    }
};

EhvmConst ehvm_dtsg_config_t ehvmDtsgConfigData = {
    5U,                      /* DtsgNumOfSPID */
    &s_Dtsg_SpidData[0],     /* DtsgSPIDPtr */
    128U,                    /* DtsgNumOfDTSG_n */
    &s_Dtsg_ChannelData[0],  /* DtsgDTSG_n_Ptr */
    1U,                      /* DtsgNumOfDTSG_GR */
    &s_Dtsg_GRData[0]        /* DtsgDTSG_GR_Ptr */
};

/****************************************************************************************/
/* Hv4mCommonInterruptControllerGuardConfig                                             */
/****************************************************************************************/
static EhvmConst ehvm_intc2g_spid_t s_Intc2g_SpidData[4] = {
    {
        0x00000000U    /* INTC2GMPIDn */
    },
    {
        0x00000000U    /* INTC2GMPIDn */
    },
    {
        0x00000000U    /* INTC2GMPIDn */
    },
    {
        0x00000000U    /* INTC2GMPIDn */
    }
};

static EhvmConst ehvm_intc2g_n_channel_t s_Intc2g_ChannelData[736] = {
    {
        32U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        33U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        34U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        35U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        36U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        37U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        38U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        39U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        40U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        41U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        42U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        43U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        44U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        45U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        46U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        47U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        48U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        49U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        50U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        51U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        52U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        53U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        54U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        55U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        56U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        57U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        58U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        59U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        60U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        61U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        62U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        63U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        64U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        65U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        66U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        67U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        68U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        69U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        70U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        71U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        72U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        73U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        74U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        75U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        76U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        77U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        78U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        79U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        80U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        81U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        82U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        83U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        84U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        85U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        86U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        87U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        88U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        89U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        90U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        91U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        92U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        93U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        94U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        95U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        96U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        97U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        98U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        99U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        100U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        101U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        102U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        103U,           /* INTC2G_ChannelNumber */
        0x00010043U    /* INTC2G_n_PROTm */
    },
    {
        104U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        105U,           /* INTC2G_ChannelNumber */
        0x00020043U    /* INTC2G_n_PROTm */
    },
    {
        106U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        107U,           /* INTC2G_ChannelNumber */
        0x00040043U    /* INTC2G_n_PROTm */
    },
    {
        108U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        109U,           /* INTC2G_ChannelNumber */
        0x00080043U    /* INTC2G_n_PROTm */
    },
    {
        110U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        111U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        112U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        113U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        114U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        115U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        116U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        117U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        118U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        119U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        120U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        121U,           /* INTC2G_ChannelNumber */
        0x00010043U    /* INTC2G_n_PROTm */
    },
    {
        122U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        123U,           /* INTC2G_ChannelNumber */
        0x00020043U    /* INTC2G_n_PROTm */
    },
    {
        124U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        125U,           /* INTC2G_ChannelNumber */
        0x00040043U    /* INTC2G_n_PROTm */
    },
    {
        126U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        127U,           /* INTC2G_ChannelNumber */
        0x00080043U    /* INTC2G_n_PROTm */
    },
    {
        128U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        129U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        130U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        131U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        132U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        133U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        134U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        135U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        136U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        137U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        138U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        139U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        140U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        141U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        142U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        143U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        144U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        145U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        146U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        147U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        148U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        149U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        150U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        151U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        152U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        153U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        154U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        155U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        156U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        157U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        158U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        159U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        160U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        161U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        162U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        163U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        164U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        165U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        166U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        167U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        168U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        169U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        170U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        171U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        172U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        173U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        174U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        175U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        176U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        177U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        178U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        179U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        180U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        181U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        182U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        183U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        184U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        185U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        186U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        187U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        188U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        189U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        190U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        191U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        192U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        193U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        194U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        195U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        196U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        197U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        198U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        199U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        200U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        201U,           /* INTC2G_ChannelNumber */
        0x00080043U    /* INTC2G_n_PROTm */
    },
    {
        202U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        203U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        204U,           /* INTC2G_ChannelNumber */
        0x00010043U    /* INTC2G_n_PROTm */
    },
    {
        205U,           /* INTC2G_ChannelNumber */
        0x00020043U    /* INTC2G_n_PROTm */
    },
    {
        206U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        207U,           /* INTC2G_ChannelNumber */
        0x00040043U    /* INTC2G_n_PROTm */
    },
    {
        208U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        209U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        210U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        211U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        212U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        213U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        214U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        215U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        216U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        217U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        218U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        219U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        220U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        221U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        222U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        223U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        224U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        225U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        226U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        227U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        228U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        229U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        230U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        231U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        232U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        233U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        234U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        235U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        236U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        237U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        238U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        239U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        240U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        241U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        242U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        243U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        244U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        245U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        246U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        247U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        248U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        249U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        250U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        251U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        252U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        253U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        254U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        255U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        256U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        257U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        258U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        259U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        260U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        261U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        262U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        263U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        264U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        265U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        266U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        267U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        268U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        269U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        270U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        271U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        272U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        273U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        274U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        275U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        276U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        277U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        278U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        279U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        280U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        281U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        282U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        283U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        284U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        285U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        286U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        287U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        288U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        289U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        290U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        291U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        292U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        293U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        294U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        295U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        296U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        297U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        298U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        299U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        300U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        301U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        302U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        303U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        304U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        305U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        306U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        307U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        308U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        309U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        310U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        311U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        312U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        313U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        314U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        315U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        316U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        317U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        318U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        319U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        320U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        321U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        322U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        323U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        324U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        325U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        326U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        327U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        328U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        329U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        330U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        331U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        332U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        333U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        334U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        335U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        336U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        337U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        338U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        339U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        340U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        341U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        342U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        343U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        344U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        345U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        346U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        347U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        348U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        349U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        350U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        351U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        352U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        353U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        354U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        355U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        356U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        357U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        358U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        359U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        360U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        361U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        362U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        363U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        364U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        365U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        366U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        367U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        368U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        369U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        370U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        371U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        372U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        373U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        374U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        375U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        376U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        377U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        378U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        379U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        380U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        381U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        382U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        383U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        384U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        385U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        386U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        387U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        388U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        389U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        390U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        391U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        392U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        393U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        394U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        395U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        396U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        397U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        398U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        399U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        400U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        401U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        402U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        403U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        404U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        405U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        406U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        407U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        408U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        409U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        410U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        411U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        412U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        413U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        414U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        415U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        416U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        417U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        418U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        419U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        420U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        421U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        422U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        423U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        424U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        425U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        426U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        427U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        428U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        429U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        430U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        431U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        432U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        433U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        434U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        435U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        436U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        437U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        438U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        439U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        440U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        441U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        442U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        443U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        444U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        445U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        446U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        447U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        448U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        449U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        450U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        451U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        452U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        453U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        454U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        455U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        456U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        457U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        458U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        459U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        460U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        461U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        462U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        463U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        464U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        465U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        466U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        467U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        468U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        469U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        470U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        471U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        472U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        473U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        474U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        475U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        476U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        477U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        478U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        479U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        480U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        481U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        482U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        483U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        484U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        485U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        486U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        487U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        488U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        489U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        490U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        491U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        492U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        493U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        494U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        495U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        496U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        497U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        498U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        499U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        500U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        501U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        502U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        503U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        504U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        505U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        506U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        507U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        508U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        509U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        510U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        511U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        512U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        513U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        514U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        515U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        516U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        517U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        518U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        519U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        520U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        521U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        522U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        523U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        524U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        525U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        526U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        527U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        528U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        529U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        530U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        531U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        532U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        533U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        534U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        535U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        536U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        537U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        538U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        539U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        540U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        541U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        542U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        543U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        544U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        545U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        546U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        547U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        548U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        549U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        550U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        551U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        552U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        553U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        554U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        555U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        556U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        557U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        558U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        559U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        560U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        561U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        562U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        563U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        564U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        565U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        566U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        567U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        568U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        569U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        570U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        571U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        572U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        573U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        574U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        575U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        576U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        577U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        578U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        579U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        580U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        581U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        582U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        583U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        584U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        585U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        586U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        587U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        588U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        589U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        590U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        591U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        592U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        593U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        594U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        595U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        596U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        597U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        598U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        599U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        600U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        601U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        602U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        603U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        604U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        605U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        606U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        607U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        608U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        609U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        610U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        611U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        612U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        613U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        614U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        615U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        616U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        617U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        618U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        619U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        620U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        621U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        622U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        623U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        624U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        625U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        626U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        627U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        628U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        629U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        630U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        631U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        632U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        633U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        634U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        635U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        636U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        637U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        638U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        639U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        640U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        641U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        642U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        643U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        644U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        645U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        646U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        647U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        648U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        649U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        650U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        651U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        652U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        653U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        654U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        655U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        656U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        657U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        658U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        659U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        660U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        661U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        662U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        663U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        664U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        665U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        666U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        667U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        668U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        669U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        670U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        671U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        672U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        673U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        674U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        675U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        676U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        677U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        678U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        679U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        680U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        681U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        682U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        683U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        684U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        685U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        686U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        687U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        688U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        689U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        690U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        691U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        692U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        693U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        694U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        695U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        696U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        697U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        698U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        699U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        700U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        701U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        702U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        703U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        704U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        705U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        706U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        707U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        708U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        709U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        710U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        711U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        712U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        713U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        714U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        715U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        716U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        717U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        718U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        719U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        720U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        721U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        722U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        723U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        724U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        725U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        726U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        727U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        728U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        729U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        730U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        731U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        732U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        733U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        734U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        735U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        736U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        737U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        738U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        739U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        740U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        741U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        742U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        743U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        744U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        745U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        746U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        747U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        748U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        749U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        750U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        751U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        752U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        753U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        754U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        755U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        756U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        757U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        758U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        759U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        760U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        761U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        762U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        763U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        764U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        765U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        766U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    },
    {
        767U,           /* INTC2G_ChannelNumber */
        0x00000043U    /* INTC2G_n_PROTm */
    }
};

static EhvmConst ehvm_intc2g_channel_t s_Intc2g_GRData[1] = {
    {
        0x00010043U    /* INTC2G_GR_PROTm */
    }
};

static EhvmConst ehvm_intc2g_channel_t s_Intc2g_IMRData[1] = {
    {
        0x00000043U    /* INTC2G_IMR_PROTm */
    }
};

EhvmConst ehvm_intc2g_config_t ehvmIntc2gConfigData = {
    4U,                        /* Intc2gNumOfSPID */
    &s_Intc2g_SpidData[0],     /* Intc2gSPIDPtr */
    736U,                       /* Intc2gNumOfINTC2G_n */
    &s_Intc2g_ChannelData[0],  /* Intc2gINTC2G_n_Ptr */
    1U,                        /* Intc2gNumOfINTC2G_GR */
    &s_Intc2g_GRData[0],       /* Intc2gINTC2G_GR_Ptr */
    1U,                        /* Intc2gNumOfINTC2G_IMR */
    &s_Intc2g_IMRData[0]       /* Intc2gINTC2G_IMR_Ptr */
};

/****************************************************************************************/
/* Hv4mClusterRamGuardConfig                                                            */
/****************************************************************************************/
static EhvmConst ehvm_crg_spid_t s_Crg_CrgSpidData_CH0[5] = {
    {
        0x00000001U  /* CRGSPID */
    },
    {
        0x00000002U  /* CRGSPID */
    },
    {
        0x00000010U  /* CRGSPID */
    },
    {
        0x00001000U  /* CRGSPID */
    },
    {
        0x00004000U  /* CRGSPID */
    }
};
static EhvmConst ehvm_crg_spid_t s_Crg_CrgSpidData_CH1[5] = {
    {
        0x00000001U  /* CRGSPID */
    },
    {
        0x00000002U  /* CRGSPID */
    },
    {
        0x00000010U  /* CRGSPID */
    },
    {
        0x00001000U  /* CRGSPID */
    },
    {
        0x00004000U  /* CRGSPID */
    }
};
static EhvmConst ehvm_crg_spid_t s_Crg_CrgSpidData_CH2[5] = {
    {
        0x00000001U  /* CRGSPID */
    },
    {
        0x00000003U  /* CRGSPID */
    },
    {
        0x00000011U  /* CRGSPID */
    },
    {
        0x00001001U  /* CRGSPID */
    },
    {
        0x00004001U  /* CRGSPID */
    }
};
static EhvmConst ehvm_crg_spid_t s_Crg_CrgSpidData_CH3[5] = {
    {
        0x00000001U  /* CRGSPID */
    },
    {
        0x00000002U  /* CRGSPID */
    },
    {
        0x00000010U  /* CRGSPID */
    },
    {
        0x00001000U  /* CRGSPID */
    },
    {
        0x00004000U  /* CRGSPID */
    }
};

static EhvmConst ehvm_crg_prot_t s_Crg_CrgProtData_CH0[5] = {
    {
        0x00000000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00010000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00020000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00030000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00040000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    }
};
static EhvmConst ehvm_crg_prot_t s_Crg_CrgProtData_CH1[5] = {
    {
        0x00000000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00010000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00020000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00030000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00040000U, /* CRGBAD */
        0x00070000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    }
};
static EhvmConst ehvm_crg_prot_t s_Crg_CrgProtData_CH2[5] = {
    {
        0x00000000U, /* CRGBAD */
        0x001C0000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00040000U, /* CRGBAD */
        0x001C0000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00080000U, /* CRGBAD */
        0x001C0000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x000C0000U, /* CRGBAD */
        0x001C0000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00100000U, /* CRGBAD */
        0x001C0000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    }
};
static EhvmConst ehvm_crg_prot_t s_Crg_CrgProtData_CH3[5] = {
    {
        0x00000000U, /* CRGBAD */
        0x00038000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00008000U, /* CRGBAD */
        0x00038000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00010000U, /* CRGBAD */
        0x00038000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00018000U, /* CRGBAD */
        0x00038000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    },
    {
        0x00020000U, /* CRGBAD */
        0x00038000U, /* CRGADV */
        0x00000043U  /* CRGPROT */
    }
};

static EhvmConst ehvm_crg_info_t s_Crg_CrgData[4] = {
    {
        0U,                         /* CrgChannelNumber */
        5U,                         /* CrgNumOfCRGSpid */
        &s_Crg_CrgSpidData_CH0[0],  /* CrgCRGSpidPtr */
        5U,                         /* CrgNumOfProt */
        &s_Crg_CrgProtData_CH0[0]   /* CrgProtPtr */
    },
    {
        1U,                         /* CrgChannelNumber */
        5U,                         /* CrgNumOfCRGSpid */
        &s_Crg_CrgSpidData_CH1[0],  /* CrgCRGSpidPtr */
        5U,                         /* CrgNumOfProt */
        &s_Crg_CrgProtData_CH1[0]   /* CrgProtPtr */
    },
    {
        2U,                         /* CrgChannelNumber */
        5U,                         /* CrgNumOfCRGSpid */
        &s_Crg_CrgSpidData_CH2[0],  /* CrgCRGSpidPtr */
        5U,                         /* CrgNumOfProt */
        &s_Crg_CrgProtData_CH2[0]   /* CrgProtPtr */
    },
    {
        3U,                         /* CrgChannelNumber */
        5U,                         /* CrgNumOfCRGSpid */
        &s_Crg_CrgSpidData_CH3[0],  /* CrgCRGSpidPtr */
        5U,                         /* CrgNumOfProt */
        &s_Crg_CrgProtData_CH3[0]   /* CrgProtPtr */
    }
};


EhvmConst ehvm_crg_config_t ehvmCrgConfigData = {
    4U,                 /* CrgNumOfCRG */
    &s_Crg_CrgData[0],  /* CrgCRGPtr */
    0U,                 /* CrgNumOfCSG */
    NULL_PTR            /* CrgCSGPtr */
};

/****************************************************************************************/
/* Hv4mHwSpidConfig                                                                     */
/****************************************************************************************/
static EhvmConst ehvm_spid_bm_spidmsk_t s_BMSpidMsk[4] = {
    {
        SPID_BM_SPIDMSK_CPU00,  /* SpidBMNumber */
        0x00000003U   /*SpidBMSpidMsk */
    },
    {
        SPID_BM_SPIDMSK_CPU01,  /* SpidBMNumber */
        0x00000011U   /*SpidBMSpidMsk */
    },
    {
        SPID_BM_SPIDMSK_CPU02,  /* SpidBMNumber */
        0x00001001U   /*SpidBMSpidMsk */
    },
    {
        SPID_BM_SPIDMSK_CPU03,  /* SpidBMNumber */
        0x00004001U   /*SpidBMSpidMsk */
    }
};


EhvmConst ehvm_spid_config_t ehvmSpidConfigData = {
    4U,               /* SpidNumOfSpidMsk */
    &s_BMSpidMsk[0],  /* SpidBMSpidMskPtr */
    0U,               /* SpidNumOfBMSpid */
    NULL_PTR          /* SpidBMSpidPtr */
};

#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

