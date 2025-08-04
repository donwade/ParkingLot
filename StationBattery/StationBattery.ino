//#https://docs.m5stack.com/en/arduino/m5station/battery

#include "M5Unified.h"

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Display.setTextDatum(middle_center);
    M5.Display.setTextColor(TFT_BLACK);
    M5.Display.setTextFont(&fonts::FreeSansOblique12pt7b);
    M5.Display.setTextSize(1);
}

void loop()
{
    M5.Display.clear(TFT_WHITE);
    
    bool isCharging = M5.Power.isCharging();
    int vol_per = M5.Power.getBatteryLevel();
    int vol = M5.Power.getBatteryVoltage();
    int cur = M5.Power.getBatteryCurrent();

    M5.Display.setCursor(0, 30);
    M5.Display.printf("Charging: %s \n\n", isCharging ? "Yes" : "No");
    M5.Display.setCursor(0, 60);
    M5.Display.printf("Bat_level: %d%%", vol_per);
    M5.Display.setCursor(0, 90);
    M5.Display.printf("Bat_voltage: %d%mV", vol);
    M5.Display.setCursor(0, 120);
    M5.Display.printf("Bat_current: %d%mA", cur);
    delay(2000);
}                                                
