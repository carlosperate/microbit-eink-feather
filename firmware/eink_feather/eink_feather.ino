/* 
 * This test file has been modified from Adafruit's EDP library
 * ThinkInk_tricolor.ino example.
 */
/***************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include "Adafruit_ThinkInk.h"

#define EPD_DC      12  // eInk Data/Command pin
#define EPD_CS       9  // eInk Chip Select
#define EPD_BUSY    -1  // eInk Busy signa, not wired, set to -1 (waits a fixed delay)
#define SRAM_CS     -1  // 8 // SRAM Chip Select, can be set to -1 store buffer in uC RAM 
#define EPD_RESET   -1  // can set to -1 and share with chip Reset (can't deep sleep)

// 2.9" Grayscale Featherwing
ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

#define DELAY_BETWEEN_TESTS (5000)

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Serial.println("Adafruit EPD full update test in mono & grayscale");
}

bool gray = true;
void loop() {
  gray = !gray;

  // alternate modes!
  if (gray) {
    display.begin(THINKINK_GRAYSCALE4);
    Serial.println("Grayscale!");
  } else {
    display.begin(THINKINK_MONO);
    Serial.println("Monochrome!");
  }

  // Show the mode in the eInk Display
  display.clearBuffer();
  display.setTextSize(3);
  display.setTextColor(EPD_BLACK);
  display.setCursor(20, 40);
  display.print(gray ? "Grayscale": "Monochrome");
  display.display();

  delay(DELAY_BETWEEN_TESTS);

  // Draw squares with each of the available colours
  display.clearBuffer();
  display.fillRect((display.width() * 1) / 4, 0, display.width() / 4, display.height(), EPD_LIGHT);
  display.fillRect((display.width() * 2) / 4, 0, display.width() / 4, display.height(), EPD_DARK);
  display.fillRect((display.width() * 3) / 4, 0, display.width() / 4, display.height(), EPD_BLACK);
  display.display();

  delay(DELAY_BETWEEN_TESTS);

  // Large block of text
  Serial.println("Text demo");
  display.clearBuffer();
  display.setTextSize(2);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
               "Curabitur adipiscing ante sed nibh tincidunt feugiat. "
               "Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis.", EPD_BLACK);
  display.display();

  delay(DELAY_BETWEEN_TESTS);

  // Rotating lines in half a sqaure and solid colours in the other half
  display.clearBuffer();
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, EPD_BLACK);
  }
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(display.width() - 1, 0, 0, i, EPD_LIGHT); // on grayscale this will be mid-gray
  }
  display.display();
  
  delay(DELAY_BETWEEN_TESTS);
}

void testdrawtext(const char *text, uint16_t color) {
  display.setCursor(0, 0);
  display.setTextColor(color);
  display.setTextWrap(true);
  display.print(text);
}
