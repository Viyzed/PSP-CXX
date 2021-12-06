#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "gfx.h"

PSP_MODULE_INFO("First", 0, 1, 0);

int exitCallback(int arg1, int arg2, void* common) 
{
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp) 
{
    int cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}

void setupCallbacks()
{
    int thid = sceKernelCreateThread("update thread", callbackThread, 0x11, 0xFA0, 0, NULL);
    if(thid >= 0)
    {
        sceKernelStartThread(thid, 0, NULL);
    }
}

int main() 
{
    setupCallbacks();
    GFX_init();

    while(1) 
    {
        GFX_clear(0xFFFFCA82); //#82CAFFFF HTML RGBA -> 0xFFFFCA82 PSP equivalent

        GFX_draw_rect(10, 10, 30, 30, 0xFF00FFFF);

        GFX_swap_buffers();
        sceDisplayWaitVblankStart();
    }

}