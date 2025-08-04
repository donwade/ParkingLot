//https://docs.m5stack.com/en/arduino/m5station/wakeup

#include <M5Unified.h>

void setup(void) {
  auto cfg = M5.config();
  M5.begin(cfg);

  M5.Display.setTextDatum(middle_center);
  M5.Display.setTextFont(&fonts::FreeSerifBold9pt7b);
  M5.Display.setTextSize(1);

  M5.Display.drawString("Press BtnA to Sleep", M5.Display.width() / 2, M5.Display.height() / 2 - 20);
  Serial.begin(115200);
}

static constexpr const char* const wd[7] = { "Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat" };  

void showDateTime(void)
{
	//RTC chip																																										  
	m5::rtc_datetime_t now = M5.Rtc.getDateTime();
	
	Serial.printf("RTC	UTC  :%04d/%02d/%02d (%s)  %02d:%02d:%02d\r\n", 
					now.date.year, now.date.month, now.date.date,
					wd[now.date.weekDay], now.time.hours, now.time.minutes, now.time.seconds);
	
	M5.Display.setCursor(0, 10);
	
	M5.Display.printf("RTC	UTC  :%04d/%02d/%02d (%s)  %02d:%02d:%02d", 
					now.date.year, now.date.month, now.date.date,
					wd[now.date.weekDay], now.time.hours, now.time.minutes, now.time.seconds);
}

void loop(void) {

	static int cntr = 0;
	
  // cant really code a hard time cause i don't know the RTc time is.
	delay(10);

	if (!(cntr++ % 100))
	{
		showDateTime();
	}
	
	M5.update();

	if (M5.BtnA.wasPressed()) 
	{
		Serial.printf("I'm going to sleep\n");
		showDateTime();

		M5.Display.clear();


/*
	see also 
		void deepSleep(std::uint64_t micro_seconds = 0, bool touch_wakeup = true); 
		void lightSleep(std::uint64_t micro_seconds = 0, bool touch_wakeup = true); 
*/

#if 0
		// sleep for num seconds from this very moment
	    M5.Power.timerSleep(5);//sec
#else
		// awake at an absolute time and/or date
		m5::rtc_time_t absTime = {15, 20, 0};
	    m5::rtc_date_t absDate = {2025, 8 ,  4 , 1};

		#if 1
			// sleep until a specified time
			// as the RTC chip may not be up to date,
			// just take what it thinks is the current time
			// and advance 50 seconds to the future.
			// it's still usiing 'absolute' time as required.
			//

			// CAUTION: the wakeup always occurs at the
			//    top of the minute regardless of any
			//    user specified seconds.
			//    Maybe wakeup h/w only works on HH:MM
			//    and not HH:MM:SS
			// specifying a wakeup time that expires
			// within the current minute will be ignored.
			//
			
			m5::rtc_time_t nowT = M5.Rtc.getTime();
		
			nowT.seconds += 50;	// advance 50 seconds.
			nowT.minutes += nowT.seconds/60;
			nowT.seconds %= 60;

			nowT.hours   += nowT.minutes/60;
			nowT.minutes %= 60;
			nowT.hours   %= 24;

			Serial.printf("Reboot from sleep scheduled for ...\n");
			Serial.printf("CU @RTC %02d:%02d:%02d UTC\r\n", 
							nowT.hours,
							nowT.minutes,
							nowT.seconds);
			Serial.flush();
			
			M5.Power.timerSleep(nowT);
			//M5.Power.timerSleep(absTime);
		#else
			// sleep until a specified date and time
		    //M5.Power.timerSleep(absDate, absTime);
		#endif
		
	    M5.Power.powerOff(); 
#endif

  }
} 
