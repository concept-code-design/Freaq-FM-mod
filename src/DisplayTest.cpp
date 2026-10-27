/*----------------------------------------------------------------------------------------------------------
 * DisplayTest.cpp
 *
 * Hardware test for the 8x8 LED matrix.  Cycles through four ways of driving the MAX7219, 4 seconds each,
 * blinking the first N columns for method N.  Only methods that work will blink - a method that fails
 * leaves the display frozen.  The current method is also printed to the serial port (115200 baud).
 *
 *   1  bit-banged SPI, D10 input with pull-up      (current synth firmware)
 *   2  bit-banged SPI, D10 output high
 *   3  hardware SPI,   D10 output high             (original Meebleeps firmware)
 *   4  bit-banged SPI, D10 output low
 *
 * Only built in the [env:displaytest] PlatformIO environment:  pio run -e displaytest -t upload
*-----------------------------------------------------------------------------------------------------------
*/
#ifdef DISPLAY_TEST

#include <Arduino.h>
#include <SPI.h>
#include "LedMatrix.h"

#define DISPLAY_TEST_METHODS 4

uint8_t method;


void sendByte(uint8_t value)
{
  if (method == 3)
  {
    SPI.transfer(value);
    return;
  }

  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(PIN_LEDMATRIX_DIN, (value & mask) ? HIGH : LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_LEDMATRIX_CLK, HIGH);
    delayMicroseconds(2);
    digitalWrite(PIN_LEDMATRIX_CLK, LOW);
  }
}


void writeRegister(uint8_t address, uint8_t value)
{
  digitalWrite(PIN_LEDMATRIX_CS, LOW);
  sendByte(address);
  sendByte(value);
  digitalWrite(PIN_LEDMATRIX_CS, HIGH);
}


void setupMethod()
{
  SPCR = 0;   // hardware SPI off
  pinMode(PIN_LEDMATRIX_DIN, OUTPUT);
  pinMode(PIN_LEDMATRIX_CLK, OUTPUT);
  pinMode(PIN_LEDMATRIX_CS,  OUTPUT);
  digitalWrite(PIN_LEDMATRIX_CLK, LOW);
  digitalWrite(PIN_LEDMATRIX_CS, HIGH);

  switch (method)
  {
    case 1:
      pinMode(10, INPUT_PULLUP);
      break;
    case 2:
      pinMode(10, OUTPUT);
      digitalWrite(10, HIGH);
      break;
    case 3:
      SPI.setBitOrder(MSBFIRST);
      SPI.begin();                // drives D10 high
      break;
    case 4:
      digitalWrite(10, LOW);
      pinMode(10, OUTPUT);
      break;
  }

  writeRegister(LED_DISPLAYTEST, 0x00);
  writeRegister(LED_DECODE_MODE, 0x00);
  writeRegister(LED_SCAN_LIMIT, 0x07);
  writeRegister(LED_INTENSITY, 0x04);
  writeRegister(LED_SHUTDOWN, 0x01);
}


void setup()
{
  Serial.begin(115200);
  Serial.println(F("\n\nFreaq display test - methods 1-4"));
}


void loop()
{
  for (method = 1; method <= DISPLAY_TEST_METHODS; method++)
  {
    Serial.print(F("method "));
    Serial.println(method);
    setupMethod();

    // blink the first <method> columns: every row gets the same bit pattern
    uint8_t pattern = 0xFF << (8 - method);
    for (uint8_t blink = 0; blink < 4; blink++)
    {
      for (uint8_t row = 1; row <= 8; row++) writeRegister(row, pattern);
      delay(500);
      for (uint8_t row = 1; row <= 8; row++) writeRegister(row, 0);
      delay(500);
    }
  }
}

#endif
