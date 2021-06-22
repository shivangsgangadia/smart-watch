#include "Module.h"

RTClock InternalRTC::rtc(RTCSEL_LSE);

// Public methods
void InternalRTC::init() {
  InternalRTC::rtc.setTime(0);
  InternalRTC::readTime();
}

void InternalRTC::readTime() {
  InternalRTC::rtc.getTime(State::timeBuffer);
}

void InternalRTC::setTime() {
  InternalRTC::rtc.setTime(State::timeBuffer);
}

// TODO : after implementing Flash
void InternalRTC::setUserAlarm(bool repeating, uint8_t hours, uint8_t mins) {

}
