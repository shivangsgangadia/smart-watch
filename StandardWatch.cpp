#include "Module.h"

/* ###################################################################################
    Standard Watch
  ################################################################################### */

StandardWatch::StandardWatch(uint8_t row, uint8_t column): Module(row, column) {
}

StandardWatch::~StandardWatch() {

}

void StandardWatch::onSerialInput(char *inp) {

}

void StandardWatch::onMinutePassed() {
  StandardWatch::updateDisplay();
}

uint8_t extractedMonth;

void StandardWatch::updateDisplay() {
  uint8_t processedHour;

  if (State::is12Hour) {
    StandardWatch::timePrintOffset = 0;

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
    StandardWatch::timePrintOffset = 17;
    this->displayBufferTime[5] = '\0';
  }

  
  this->displayBufferTime[0] = (processedHour / 10) + NUM_PRINT_OFFSET;
  this->displayBufferTime[1] = (processedHour % 10) + NUM_PRINT_OFFSET;

  this->displayBufferTime[2] = ':';

  this->displayBufferTime[3] = (State::timeBuffer.minute / 10) + NUM_PRINT_OFFSET;
  this->displayBufferTime[4] = (State::timeBuffer.minute % 10) + NUM_PRINT_OFFSET;

  
  // Set date string
  this->displayBufferDate[0] = (State::timeBuffer.day / 10) + NUM_PRINT_OFFSET;
  this->displayBufferDate[1] = (State::timeBuffer.day % 10) + NUM_PRINT_OFFSET;

  this->displayBufferDate[2] = ' ';

  for (uint8_t i = 0; i < 3; i++) {
    this->displayBufferDate[3 + i] = monthNames[State::timeBuffer.month - 1][i];
  }

  this->displayBufferDate[6] = ' ';

  for (uint8_t i = 0; i < 3; i++) {
    this->displayBufferDate[7 + i] = weekdays[State::timeBuffer.weekday][i];
  }
  
  this->displayBufferDate[10] = '\0';

  OLED::writeString(this->displayBufferTime, 2, this->startRow, this->startColumn + timePrintOffset);
//  Serial.println(this->displayBufferTime);
  OLED::writeString(this->displayBufferDate, 1, this->startRow + 3, this->startColumn + 20);
//  Serial.println(this->displayBufferDate);
}

void StandardWatch::onIteration() {

}
