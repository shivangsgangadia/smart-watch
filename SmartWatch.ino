#include "Module.h"

char serialInputBuffer[64];
bool buttonInterrupt, timeInterrupt;

int counter = 0;
uint8_t secondsCounter = 0;

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Begun execution");
  Wire.begin();
//  Wire.setClock(400000);  // HS mode
  delay(10);
  OLED::init();
  OLED::clearDisplay();

  pinMode(LED_BUILTIN, OUTPUT);

  delay(500);
  InternalRTC::init();

  InternalRTC::rtc.attachSecondsInterrupt(onSecondsInterrupt);

  for (uint8_t i = 0; i < State::overlayCount; i++)
  {
    State::overlays[i]->updateDisplay();
  }
  State::getCurrentApp()->updateDisplay();

}

void loop()
{
  if (Serial.available())
  {
    uint8_t l = Serial.readBytes(serialInputBuffer, 63);
    serialInputBuffer[63] = '\0';
    for (uint8_t i = 0; i < State::overlayCount; i++)
    {
      State::overlays[i]->onSerialInput(serialInputBuffer);
    }
    State::getCurrentApp()->onSerialInput(serialInputBuffer);
  }

  for (uint8_t i = 0; i < State::overlayCount; i++)
  {
    State::overlays[i]->onIteration();
  }
  State::getCurrentApp()->onIteration();

  // Servicing time events
  if (secondsCounter >= 60) {
    secondsCounter = 0;
    InternalRTC::readTime();

    for (uint8_t i = 0; i < State::overlayCount; i++)
    {
      State::overlays[i]->onMinutePassed();
    }

    State::getCurrentApp()->onMinutePassed();
    Serial.print("TI");
  }
}

void onSecondsInterrupt() {
  secondsCounter++;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
