#include "Module.h"

bool State::is12Hour = true;
tm_t State::timeBuffer;

// Add all overlays
Module* State::overlays[2] = {
  new BatteryOverlay( 0, 100),
  new TimeOverlay(0, 0)
};

// Add all apps
Module* State::apps[1] = {
  new StandardWatch( 2, 10)
};

uint8_t State::currentAppIndex = 0;
uint8_t State::overlayCount = 2;
uint8_t State::totalAppCount = 1;


void State::nextApp() {
  State::currentAppIndex++;
  if (State::currentAppIndex >= State::totalAppCount) {
    State::currentAppIndex = 0;
  }
}

void State::previousApp() {
  State::currentAppIndex--;
  if (State::currentAppIndex < 0) {
    State::currentAppIndex = State::totalAppCount - 1;
  }
}

Module* State::getCurrentApp() {
  return State::apps[State::currentAppIndex];
}
