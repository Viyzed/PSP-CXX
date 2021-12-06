#include "gfx.hpp"
#include <pspge.h>
#include <pspdisplay.h>
#include <psputils.h>

namespace GFX 
{

    uint32_t* drawBuffer;
    uint32_t* dispBuffer;

    void init() 
    {
        drawBuffer = static_cast<uint32_t*>(sceGeEdramGetAddr());
        dispBuffer = static_cast<uint32_t*>(sceGeEdramGetAddr()) + (272 * 512 * sizeof(uint32_t));

        sceDisplaySetMode(0, 480, 272);
        sceDisplaySetFrameBuf(dispBuffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
    }

    void clear(uint32_t colour)
    {
        for(int i = 0; i < 512 * 272; i++) 
        {
            drawBuffer[i] = colour;
        }
    }

    void swapBuffers()
    {
        uint32_t* temp = dispBuffer;
        dispBuffer = drawBuffer;
        drawBuffer = temp;

        sceKernelDcacheWritebackInvalidateAll();
        sceDisplaySetFrameBuf(dispBuffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_NEXTFRAME);
    }

    void drawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint32_t colour)
    {
        if(x > 480)
        {
            x = 480;
        }
        if(y > 480) 
        {
            y = 480;
        }

        if(x + w > 480) 
        {
            w = 480 - x;
        }
        if(y + h > 272)
        {
            h = 272 - y;
        }

        int off = x + (y * 512);
        for(int y1 = 0; y1 < h; y1++) 
        {
            for(int x1 = 0; x1 < w; x1++) 
            {
                drawBuffer[x1 + off + y1 * 512] = colour;
            }
        }
    }

}