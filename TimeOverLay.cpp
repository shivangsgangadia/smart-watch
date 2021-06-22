#include <Arduino.h>
#include "Module.h"

/* ###################################################################################
    Time Overlay
  ################################################################################### */

TimeOverlay::TimeOverlay(uint8_t row, uint8_t column): Module(row, column) {
}

TimeOverlay::~TimeOverlay() {

}

void TimeOverlay::onSerialInput(char *inp) {

}

void TimeOverlay::onMinutePassed() {
  TimeOverlay::updateDisplay();
}

void TimeOverlay::updateDisplay() {
  uint8_t processedHour;

  if (State::is12Hour) {

    if (State::timeBuffer.hour > 12) {
      processedHour = State::timeBuffer.hour - 12;
    }
    else if (State::timeBuffer.hour == 0) {
      processedHour = 12;
    }
    else if (State::timeBuffer.hour <= 12) {
      processedHour = State::timeBuffer.hour;

    }

    if (InternalRTC::rtc.isPM()) {
      this->displayBufferTime[5] = 'p';
    }
    else {
      this->displayBufferTime[5] = 'a';
    }

    this->displayBufferTime[6] = 'm';

    this->displayBufferTime[7] = '\0';
    
  }
  
  else {
    processedHour = State::timeBuffer.hour;
    this->displayBufferTime[5] = '\0';
  }

  
  this->displayBufferTime[0] = (processedHour / 10) + NUM_PRINT_OFFSET;
  this->displayBufferTime[1] = (processedHour % 10) + NUM_PRINT_OFFSET;

  this->displayBufferTime[2] = ':';

  this->displayBufferTime[3] = (State::timeBuffer.minute / 10) + NUM_PRINT_OFFSET;
  this->displayBufferTime[4] = (State::timeBuffer.minute % 10) + NUM_PRINT_OFFSET;

  OLED::writeString(this->displayBufferTime, 1, this->startRow, this->startColumn);
//  Serial.print("Printed TimeOverlay: ");
//  Serial.println(this->displayBufferTime);
}

void TimeOverlay::onIteration() {

}
