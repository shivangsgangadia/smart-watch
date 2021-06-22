#include <Arduino.h>
#include "OLED.h"
#include <stdint.h>
#include "InternalRTC.h"

// Pin definitions
#define BUTTON_INTERRUPT_PIN 3
#define TIME_INTERRUPT_PIN PA5

// Ids of apps if any
#define STANDARD_WATCH_APP 1

class Module;
class State;

/**
   Keeps track of the system's state as a whole.
   Also provides API for setting overlays and apps.
*/
class State
{
  public:
    static uint8_t currentAppIndex;
    static uint8_t overlayCount, totalAppCount;

    static Module *apps[];
    static Module *overlays[];

    // Time variables
    static tm_t timeBuffer;
    static bool is12Hour;

    /**
       Initializes state's memory requirements for apps and overlays
    */
    static void init(uint8_t oc, uint8_t currentAppId);

    /**
       Increments currentApp pointer keeping it within range
    */
    static void nextApp();

    /**
       Increments currentApp pointer keeping it within range
    */
    static void previousApp();

    /**
       returns pointer to current app from apps array
    */
    static Module* getCurrentApp();

};

/**
   This class is a pure abstract class which must be overriden by any new
   module (app or overlay) that is to be added to the SmartWatch
*/
class Module
{
  public:
    const char *icon;
    uint8_t startRow, startColumn;
    Module(uint8_t row, uint8_t column)
    {
      this->startRow = row;
      this->startColumn = column;
    }

    // Required to ensure that the destructor of derived class is called when delete is called on base class pointer,
    // specially in this case where base class in abstract and hence at runtime, you must tell the system that the
    // derived class has a deallocator.
    virtual ~Module() {

    }

    /**
       Called when some data has been collected on the serial interface from the main system loop.
       You can call new Serial functions from here.
       @param inp input string from Serial port
    */
    virtual void onSerialInput(char *inp) = 0;

    /**
       Called when minute interrupt has been received. You probably want to update your UI based on time.
    */
    virtual void onMinutePassed() = 0;

    /**
       Makes changes to the display by actually drawing elements
    */
    virtual void updateDisplay() = 0;

    /**
       I/O or other operations that must be done repeatedly should be specified here.
       This function is called in the Arduino loop() method.
    */
    virtual void onIteration() = 0;
};

/**
   Declare the headers for you app here in the form of a class.
   Remember, it must override the {@link Module} abstract class.
 * */

/**
   Shows time in top left corner always, regardless of the app in focus.
*/
class TimeOverlay : public Module {
  public:
    char displayBufferTime[8];
    TimeOverlay(uint8_t row, uint8_t column);
    ~TimeOverlay();
    void onSerialInput(char *inp);
    void onMinutePassed();
    void updateDisplay();
    void onIteration();
};

/**
   Shows battery bar in top right corner always, regardless of the app in focus.
*/
class BatteryOverlay : public Module {
  public:
    const uint8_t maxBatteryLevel = 5;
    uint8_t batteryLevel;
    char displayBuffer[18];
    BatteryOverlay(uint8_t row, uint8_t column);
    ~BatteryOverlay();
    void onSerialInput(char *inp);
    void onMinutePassed();
    void updateDisplay();
    void onIteration();
    uint8_t readBatteryLevel();
};

/**
   Shows time as a standard watch
*/
class StandardWatch : public Module {
  public:
    char displayBufferTime[8];
    char displayBufferDate[11];
    uint8_t timePrintOffset;
    StandardWatch(uint8_t row, uint8_t column);
    ~StandardWatch();
    void onSerialInput(char *inp);
    void onMinutePassed();
    void updateDisplay();
    void onIteration();
};
