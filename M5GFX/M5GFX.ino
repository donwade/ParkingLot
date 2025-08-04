
//https://docs.m5stack.com/en/arduino/m5station/display
// Station uses the M5GFX library as the screen driver. 
// Refer to the API & examples below for simple display implementation. 
// For more API details, refer to the M5GFX source code.

#include "M5Unified.h"

void draw_function(LovyanGFX* gfx)
{
    int x      = rand() % gfx->width();
    int y      = rand() % gfx->height();
    int r      = (gfx->width() >> 4) + 2;
    uint16_t c = rand();
    gfx->fillRect(x - r, y - r, r * 2, r * 2, c);
}

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);
    int textsize = M5.Display.height() / 60;
    if (textsize == 0) {
        textsize = 1;
    }
    M5.Display.setTextSize(textsize);
    M5.Display.clear(TFT_WHITE);
}

void loop()
{
    int x      = rand() % M5.Display.width();
    int y      = rand() % M5.Display.height();
    int r      = (M5.Display.width() >> 4) + 2;
    uint16_t c = rand();
    M5.Display.fillCircle(x, y, r, c);
    draw_function(&M5.Display);
    delay(1000);
}   
