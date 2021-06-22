#include <RTClock.h>
class InternalRTC {

  public:

    static RTClock rtc;

    static void init();

    /**
       Reads time from hardware directly into the State class
    */
    static void readTime();

    /**
       Writes current time from state module to the hardware
    */
    static void setTime();

    /**
       Sets user defined alarm. To be implemented after flash memory is added.
    */
    static void setUserAlarm(bool repeating, uint8_t hours, uint8_t mins);
};
