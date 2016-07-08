
#define  MAIN_GLOBAL
#define SERIAL_DEBUG

#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "serial_debug\serial_debug.h"
#include "stm32f10x.h"
#include "main.h"
#include "Power\Power.h"


/*******************************************************************************
** @Brief  : At this stage the microcontroller clock setting is already 
**           configured to 
XX MHz, this is done through SystemInit() function
**           which is called from startup file (startup_stm32f10x_md.s) before to
**           branch to application main. To reconfigure the default setting of 
**           SystemInit() function, refer to system_stm32f10x.c file
*******************************************************************************/  
const char g_rc_version[] = "EF01_11_1.0.1_20160630_T";

int main(void)
{        
	Power_Init();
	Power_On();

#ifdef SERIAL_DEBUG
    DebugComPort_Init();

    mprint("\n÷–Œƒœ‘ æRemote Control start ...\n\n");
    DEBUG("%s\n", g_rc_version);
    mprint("------------------------\n");
#endif
    
    while(1)
    {

    }
}
