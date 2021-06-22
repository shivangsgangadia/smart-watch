#include "Module.h"

/* ################################################################################### 
 *  Battery Overlay
 ################################################################################### */
// Set to occupy row 0, column 114 onwards - implemented to consume 7 columns - 1 start, 1 end, 5 levels

BatteryOverlay::BatteryOverlay(uint8_t row, uint8_t column):Module(row, column) {
  this->batteryLevel = readBatteryLevel(); // read level
}

BatteryOverlay::~BatteryOverlay() {

}

void BatteryOverlay::onSerialInput(char *inp) {

}

void BatteryOverlay::onMinutePassed() {
}

/**
 * Forms display buffer (an array of chars) to represent a battery.
 */
void BatteryOverlay::updateDisplay() {
  
//  OLED::clearDisplayAt(this->startRow, this->startColumn, 2);

  // Tail of battery
  BatteryOverlay::displayBuffer[0] = pgm_read_word_near(battery + 0);
  BatteryOverlay::displayBuffer[1] = pgm_read_word_near(battery + 2);

  // Head of battery
  BatteryOverlay::displayBuffer[18 - 1] = '\0';
  BatteryOverlay::displayBuffer[18 - 2] = pgm_read_word_near(battery + 3);
  BatteryOverlay::displayBuffer[18 - 3] = pgm_read_word_near(battery + 3);
  BatteryOverlay::displayBuffer[18 - 4] = pgm_read_word_near(battery + 3);
  BatteryOverlay::displayBuffer[18 - 5] = pgm_read_word_near(battery + 0);
  BatteryOverlay::displayBuffer[18 - 6] = pgm_read_word_near(battery + 2);
  
  
  
  // Filled out bars
  for (uint8_t i = 1; i <= (this-> batteryLevel * 2); i += 2) {
    BatteryOverlay::displayBuffer[i + 1] = pgm_read_word_near(battery + 1);
    BatteryOverlay::displayBuffer[i + 2] = pgm_read_word_near(battery + 1);
  }

  // Un filled bars
  for (uint8_t i = (this->batteryLevel * 2) + 1; i < (this-> maxBatteryLevel * 2); i += 2) {
    BatteryOverlay::displayBuffer[i + 1] = pgm_read_word_near(battery + 2);
    BatteryOverlay::displayBuffer[i + 2] = pgm_read_word_near(battery + 2);
  }

  OLED::writeDisplayByte(BatteryOverlay::displayBuffer, 1, this->startRow, this->startColumn);
  
}

void BatteryOverlay::onIteration() {
    
}

/**
 * Reads voltage using ADC. Return battery level after consulting Battery's datasheet
 */
uint8_t BatteryOverlay::readBatteryLevel() {
  return 3;
}
